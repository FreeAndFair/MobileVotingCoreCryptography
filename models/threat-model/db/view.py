#!/usr/bin/env python

# This script provides human-readable views of various aspects of the threat
# model database.
#
# Usage: view.py [-h] [-a [ATTACK]] [-p [PROPERTY]] [-m] [-l] [-o] [-i] [db_file]
# Full usage details are available in the help text.
#
# David Ruescas and Daniel M. Zimmerman, January 2025
# Copyright (C) 2025 Free & Fair

import argparse
import sys
from tabulate import tabulate
from anytree import Node, RenderTree

# our shared database functions
from read_database import build_data_structures

OUT_OF_SCOPE = "Out of scope"
OUTSTANDING = "*Outstanding*"

def get_attack_mitigation_tree(attack, oos=False, abstract=False, outstanding=False):
    self = {}
    self['mitigations'] = []
    self['children'] = []
    found = False

    if not attack:
        return None

    context = attack['context']
    if context:
        self['name'] = f"{attack['name']} ({context['identifier']})"
    else:
        self['name'] = attack['name']

    if attack['is_abstract'] and not abstract:
        return None
    elif attack['is_abstract']:
        self['name'] = f"{self['name']} (A)"

    for mit in attack['mitigations']:
        if mit['mitigation']:
            self['mitigations'].append(mit['mitigation']['name'])
        elif oos:
            rationale = truncate_text(sanitize_text(mit['rationale']))
            self['mitigations'].append(f"{OUT_OF_SCOPE}: {rationale}")
        found = True

    if attack['instance_of']:
        c = get_attack_mitigation_tree(attack['instance_of'], oos, abstract, outstanding)
        if c is not None:
            self['children'].append(c)
            found = True

    for child in attack['children']:
        c = get_attack_mitigation_tree(child, oos, abstract, outstanding)
        if c is not None:
            self['children'].append(c)
            found = True

    if outstanding:
        if len(attack['mitigations']) == 0:
            if len(attack['children']) == 0 and not attack['instance_of']:
                self['name'] = f"{self['name']} {OUTSTANDING}"
                return self

            if found:
                return self

        return None
    else:
        return self if found else None

def get_attack_mitigation_lines(attacks, ret=None, lineage=None, oos=False, abstract=False):
    if ret is None:
        ret = list()

    for atk in attacks:
        if not atk:
            continue

        if atk['is_abstract'] and not abstract:
            continue

        context = atk['context']
        if context:
            name = f"{atk['name']} ({context['identifier']})"
        else:
            name = atk['name']

        if lineage is None:
            lineage = [name]
        elif not atk['is_abstract']:
            lineage.append(name)

        for mit in atk['mitigations']:
            if mit['mitigation']:
                complete = lineage.copy()
                complete.append(mit['mitigation']['name'])
                ret.append(complete)
            elif oos:
                complete = lineage.copy()
                complete.append(OUT_OF_SCOPE)
                ret.append(complete)

        if atk['instance_of']:
             get_attack_mitigation_lines([atk['instance_of']], ret, lineage.copy(), oos, abstract)

        for child in atk['children']:
            get_attack_mitigation_lines([child], ret, lineage.copy(), oos, abstract)

    return ret

def get_outstanding_lines(atk, ret=None, lineage=None, oos=False, abstract=False):
    if ret is None:
        ret = list()

    if not atk:
        return ret

    if atk['is_abstract'] and not abstract:
        return ret

    context = atk['context']
    if context:
        name = f"{atk['name']} ({context['identifier']})"
    else:
        name = atk['name']

    if lineage is None:
        lineage = [name]
    else:
        lineage.append(name)

    if not atk['mitigations'] and not atk['instance_of'] and not atk['children']:
        lineage.append(OUTSTANDING)
        ret.append(lineage)
        return ret

    for child in atk['children']:
        get_outstanding_lines(child, ret, lineage.copy(), oos, abstract)

    # If an attack has mitigations, we do not care if its abstract form does not
    if atk['instance_of'] and not atk['mitigations']:
        get_outstanding_lines(atk['instance_of'], ret, lineage.copy(), oos, abstract)

    return ret

# build attack rows recursively
def build_attack_rows(attack, level=0, prefix='', abstract=False):
    rows = []

    if attack['is_abstract'] and not abstract:
        return rows

    name = prefix + (attack['name'] + ' (A)' if attack['is_abstract'] else attack['name'])
    description = truncate_text(sanitize_text(attack['description'] or ''))
    context = attack['context']['identifier'] if attack['context'] else 'None'
    properties = ', '.join([prop['name'] for prop in attack['properties']])
    rows.append((name, description, context, properties))
    for i, child in enumerate(attack['children']):
        if level == 0:
            if i == len(attack['children']) - 1:
                child_prefix = '└─'
            else:
                child_prefix = '├─'
        else:
            child_prefix = prefix + '─'

        rows.extend(build_attack_rows(child, level + 1, child_prefix, abstract=abstract))
    return rows

# build property rows recursively
def build_property_rows(property, level=0, prefix=''):
    rows = []
    name = prefix + property['name']
    description = truncate_text(sanitize_text(property['description'] or ''))
    attacks = '\n'.join([atk['identifier'] for atk in property['attacks']])

    mitigations = get_unique_attack_mitigations(attacks=property['attacks'], abstract=True)
    mitigations = '\n'.join(m['name'] for m in mitigations)

    rows.append((name, description, attacks, mitigations))
    children = sorted(property['children'], key = lambda value: value['identifier'])
    for i, child in enumerate(children):
        if level == 0:
            child_prefix = '└─'
        else:
            child_prefix = prefix + '─'

        rows.extend(build_property_rows(child, level + 1, child_prefix))
    return rows

# Used when building property rows to include related mitigations
def get_unique_attack_mitigations(attacks, ret=None, abstract=False, oos=False):
    if ret is None:
        ret = dict()

    for atk in attacks:
        if not atk:
            continue
        for mit in atk['mitigations']:
            if mit['mitigation']:
                ret[mit['mitigation']['id']] = mit['mitigation']
            elif oos:
                mit['description'] = mit['rationale']
                mit['name'] = OUT_OF_SCOPE
                # hacky
                ret[mit['description']] = mit

        if abstract and atk['instance_of']:
             get_unique_attack_mitigations([atk['instance_of']], ret, abstract, oos)

        for child in atk['children']:
            get_unique_attack_mitigations([child], ret, abstract, oos)

    return ret.values()

def build_mitigation_tree(attack, parent_node):

    children = sorted(attack['children'], key = lambda value: value['name'])
    for child in children:
        if child:
            child_node = Node(child['name'], parent=parent_node)
            build_mitigation_tree(child, child_node)

    mitigations = sorted(attack['mitigations'])
    for mitigation in mitigations:
        if mitigation:
            child_node = Node(mitigation, parent=parent_node)

def build_property_tree(property, parent_node):
    children = sorted(property['children'], key = lambda value: value['identifier'])
    for child in children:
        if child['kind'] == 'Model':
            description = truncate_text(child['description'])
            child_node = Node(child['name'], parent=parent_node, description=description)
            build_property_tree(child, child_node)

def build_attack_tree(attack, parent_node, abstract=False):
    children = sorted(attack['children'], key = lambda value: value['name'])
    for child in children:
        if child['is_abstract'] == 1 and not abstract:
            continue
        if child['context']:
            child['name'] = f"{child['name']} ({child['context']['identifier']})"
        child_node = Node(child['name'], parent=parent_node)
        build_attack_tree(child, child_node)

def main():
    example_text = '''Examples:
    ./view.py -e property                       # prints all properties table
    ./view.py -e property -t                    # prints all properties tree
    ./view.py -e property -t -r my_property     # prints properties tree, starting at my_property
    ./view.py -e attack                         # prints all attacks table
    ./view.py -e attack -t                      # prints all attacks tree
    ./view.py -e attack -r my_attack            # prints attacks table, starting at my_attack
    ./view.py -e mitigation                     # prints all mitigations table
    ./view.py -e mitigation -r my_attack        # prints mitigations table applied to my_attack
    ./view.py -e mitigation -r my_attack -t     # prints mitigations tree applied to my_attack (-o for oos)
    ./view.py -e context                        # prints all contexts
    ./view.py -e outstanding                    # prints all outstanding attacks
    ./view.py -e outstanding -r my_attack       # prints outstanding attacks starting at my_attack
    ./view.py -e mitigation -t -r my_attack     # prints mitigation path for attack my_attack
    '''
    parser = argparse.ArgumentParser(description='Display data in table or tree format.', epilog=example_text, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('-d', '--database', type=str, help='Path to the SQLite database file',  nargs='?', default="./db.sqlite3")
    parser.add_argument('-t', '--tree', action='store_true', help='Display data in tree format')
    parser.add_argument('-e', '--entity', type=str, choices=['property', 'context', 'mitigation', 'attack', 'outstanding'], help='Specify the entity to display')
    parser.add_argument('-r', '--root', type=str, help='Specify the root entity by name')
    parser.add_argument('-o', '--oos', action='store_true', help='Show Out of scope "mitigations", for applicable views')
    parser.add_argument('-a', '--abstract', action='store_true', help='Show abstract attacks, for applicable views')

    args = parser.parse_args(args=None if sys.argv[1:] else ['--help'])

    db_file_path = args.database

    # Build data structures
    property_dict, context_dict, mitigation_dict, attack_dict = build_data_structures(db_file_path)

    # Create a mapping from mitigation names to mitigations in the dictionary
    mitigations_by_name = {}
    for key, m in mitigation_dict.items():
        mitigations_by_name[m['name']] = m

    match args.entity:
        case 'property':
            show_properties(args, property_dict)
        case 'context':
            show_contexts(args, context_dict)
        case 'mitigation':
            show_mitigations(args, mitigations_by_name, attack_dict)
        case 'attack':
            show_attacks(args, attack_dict)
        case 'outstanding':
            show_outstanding(args, attack_dict)


def show_property_tree(args, property_dict):
    if args.root:
        root_properties = [prop for prop in property_dict.values() if prop['name'] == args.root and prop['kind'] == 'Model']
    else:
        root_properties = [prop for prop in property_dict.values() if prop['parent'] is None and prop['kind'] == 'Model']

    properties = sorted(root_properties, key = lambda value: value['identifier'])
    for root in properties:
        root_node = Node(root['name'], description=root['description'])
        build_property_tree(root, root_node)
        for pre, fill, node in RenderTree(root_node):
            print("%s%s %s" % (pre, node.name, node.description))

def show_property_table(args, property_dict):
    data = []
    if args.root:
        root_properties = [prop for prop in property_dict.values() if prop['name'] == args.root and prop['kind'] == 'Model']
    else:
        root_properties = [prop for prop in property_dict.values() if prop['parent'] is None and prop['kind'] == 'Model']

    properties = sorted(root_properties, key = lambda value: value['identifier'])
    for root in properties:
        data.extend(build_property_rows(root))
    headers = ["Name", "Description", "Attacks", "Mitigations"]
    display_table(data, headers)

def show_attack_tree(args, attack_dict):
    if args.root:
        root_attacks = [atk for atk in attack_dict.values() if atk['identifier'] == args.root]
    else:
        root_attacks = [atk for atk in attack_dict.values() if not atk['parents']]

    root_attacks = sorted(root_attacks, key = lambda value: value['identifier'])
    for root in root_attacks:

        root_node = Node(root['name'])
        if root['is_abstract'] == 1 and not args.abstract:
            continue
        build_attack_tree(root, root_node, abstract=args.abstract)
        for pre, fill, node in RenderTree(root_node):
            print("%s%s" % (pre, node.name))

def show_attack_table(args, attack_dict):
    data = []
    if args.root:
        root_attacks = [atk for atk in attack_dict.values() if atk['identifier'] == args.root]
    else:
        root_attacks = [atk for atk in attack_dict.values() if not atk['parents']]

    root_attacks = sorted(root_attacks, key = lambda value: value['identifier'])
    for root in root_attacks:
        data.extend(build_attack_rows(root, abstract=args.abstract))
    headers = ["Attack", "Description", "Context", "Properties"]
    display_table(data, headers)

def show_mitigation_tree(args, attack_dict):
    root_attack = [atk for atk in attack_dict.values() if atk['identifier'] == args.root]
    if len(root_attack) != 1:
        print(f"Expected one attack, found {len(root_attack)}")
        return

    root_attack = root_attack[0]
    if root_attack:
        root_node = Node(root_attack['name'])
        root_attack = get_attack_mitigation_tree(root_attack, oos=args.oos, abstract=args.abstract, outstanding=False)

        build_mitigation_tree(root_attack, root_node)
        for pre, fill, node in RenderTree(root_node):
            print("%s%s" % (pre, node.name))
    else:
        print(f"Root attack not found or not supplied (-r {args.root if args.root is not None else '<attack>'})")

def show_mitigation_table(args, mitigations_by_name, attack_dict):
    data = []
    attacks = []

    if args.oos:
        print("Flag '-o' not supported here")
        return

    if args.root:
        root_attack = next((atk for atk in attack_dict.values() if atk['identifier'] == args.root), None)
        if root_attack:
            attacks = [root_attack]
    else:
        attacks = attack_dict.values()
        # prune
        attacks = [atk for atk in attacks if atk['parents'] is None or len(atk['parents']) == 0]

    keys = {}
    for atk in attacks:
        if atk['is_abstract'] and not args.abstract:
            continue
        lines = get_attack_mitigation_lines([atk], oos=args.oos, abstract=args.abstract)

        # Group by mitigation
        mitigations = {}
        for line in lines:
            mitigation = line[-1]
            if mitigation in mitigations:
                mitigations[mitigation].append(line)
            else:
                mitigations[mitigation] = [line]

        # Stringify lines
        for key, value in mitigations.items():
            description = mitigations_by_name[key]['description']
            description = truncate_text(sanitize_text(description or ''))
            value = [for_column(' > '.join(row)) for row in value]
            if key in keys:
                keys[key][1] = keys[key][1] + value
            else:
                keys[key] = [description, value]

    for key, value in sorted(keys.items()):
        data.append([key, value[0], '\n'.join(sorted(value[1]))])
    headers = ["Mitigation", "Description", "Attack line"]

    display_table(data, headers)

def show_contexts(args, context_dict):
    ctxs = sorted(context_dict.values(), key = lambda value: value['name'])
    data = [(ctx['name'], ctx['kind'], truncate_text(sanitize_text(ctx['description'] or ''))) for ctx in ctxs]
    headers = ["Name", "Kind", "Description"]
    display_table(data, headers)

def show_outstanding(args, attack_dict):
    data = []
    attacks = []
    if args.root:
        root_attack = next((atk for atk in attack_dict.values() if atk['identifier'] == args.root), None)
        if root_attack:
            attacks = [root_attack]
    else:
        attacks = attack_dict.values()
        # prune
        attacks = [atk for atk in attacks if len(atk['parents']) == 0]

    for atk in attacks:
        if atk['is_abstract']:
            continue
        lines = get_outstanding_lines(atk, oos=args.oos, abstract=args.abstract)

        if len(lines) > 0:
            value = [for_column(' > '.join(line)) for line in lines]
            data.append(['\n'.join(sorted(value))])

    headers = ["Attack outstanding"]

    display_table(data, headers)

def show_properties(args, property_dict):
    if args.tree:
        show_property_tree(args, property_dict)
    else:
        show_property_table(args, property_dict)

def show_attacks(args, attack_dict):
    if args.tree:
        show_attack_tree(args, attack_dict)
    else:
        show_attack_table(args, attack_dict)

def show_mitigations(args, mitigations_by_name, attack_dict):
    if args.tree:
        show_mitigation_tree(args, attack_dict)
    else:
        show_mitigation_table(args, mitigations_by_name, attack_dict)

# truncate text with ellipsis
def truncate_text(text, max_length=50):
    if len(text) > max_length:
        return text[:max_length] + '..'
    return text

# wrap around text for use in table columns
def for_column(text, max_row=90):
    if len(text) > max_row:
        return f"{text[:max_row]}\n{for_column(text[max_row:])}"
    return text

# sanitize text by replacing newlines with spaces
def sanitize_text(text):
    return text.replace('\n', ' ')

def display_table(data, headers):
    print(tabulate(data, headers=headers, tablefmt="grid"))

if __name__ == "__main__":
    main()
