# Threat Model Database Reader
# Copyright (C) 2025 Free & Fair
# Last Revised 15 January 2025 by Daniel Zimmerman

# This file contains utility functions shared among the various threat
# model scripts that read the threat model database into native Python
# data structures for processing.

from natsort import natsorted
import sqlite3

def fetch_data(db_file_path, query):
    """ Fetch data from the SQLite database.

        :param db_file_path: The filesystem path to the database.
        :param query: The SQL query to execute on the database.
        :returns: The rows returned by the SQL query.
    """
    conn = sqlite3.connect(db_file_path)
    cursor = conn.cursor()
    cursor.execute(query)
    rows = cursor.fetchall()
    conn.close()
    return rows

def build_data_structures(db_file_path):
    """ Build native Python data structures from the threat model data
        stored in the database.

        :param db_file_path: The filesystem path to the database.
        :returns: The tuple of four dictionaries (properties, contexts, mitigations,
                  and attacks) generated from the threat model data.
    """
    # Fetch data from the database
    properties = fetch_data(db_file_path, "SELECT id, name, description, kind, parent_fk, identifier FROM PROPERTY")
    contexts = fetch_data(db_file_path, "SELECT id, name, kind, description, identifier FROM CONTEXT")
    mitigations = fetch_data(db_file_path, "SELECT id, name, description, identifier, scope FROM MITIGATION")
    attacks = fetch_data(db_file_path, "SELECT id, identifier, name, description, is_abstract, instanceof_fk, context_fk, likelihood, impact FROM ATTACK")
    attack_properties = fetch_data(db_file_path, "SELECT attack_fk, property_fk FROM ATTACK_PROPERTY")
    attack_mitigations = fetch_data(db_file_path, "SELECT attack_fk, mitigation_fk, rationale FROM ATTACK_MITIGATION")
    attack_children = fetch_data(db_file_path, "SELECT parent_fk, child_fk FROM ATTACK_CHILDREN")
    property_relations = fetch_data(db_file_path, "SELECT left_fk, right_fk FROM PROPERTY_RELATION")

    # Build dictionaries for each entity
    property_dict = {prop[0]: {'id': prop[0], 'name': prop[1], 'description': prop[2], 'kind': prop[3], 'identifier': prop[5], 'parent': None, 'children': [], 'related_properties': [], 'attacks': []} for prop in properties}
    context_dict = {ctx[0]: {'id': ctx[0], 'name': ctx[1], 'kind': ctx[2], 'description': ctx[3], 'identifier': ctx[4]} for ctx in contexts}
    mitigation_dict = {mit[0]: {'id': mit[0], 'name': mit[1], 'description': mit[2], 'identifier': mit[3], 'scope': mit[4], 'attacks': []} for mit in mitigations}
    attack_dict = {atk[0]: {'id': atk[0], 'identifier': atk[1], 'name': atk[2], 'description': atk[3], 'is_abstract': atk[4], 'instance_of': None, 'context': None, 'likelihood': atk[7], 'impact': atk[8], 'properties': [], 'mitigations': [], 'children': [], 'parents': []} for atk in attacks}

    # Link related entities
    for prop in properties:
        if prop[4] is not None:
            property_dict[prop[0]]['parent'] = property_dict[prop[4]]
            property_dict[prop[4]]['children'].append(property_dict[prop[0]])

    for atk in attacks:
        if atk[5] is not None:
            attack_dict[atk[0]]['instance_of'] = attack_dict[atk[5]]
        if atk[6] is not None:
            attack_dict[atk[0]]['context'] = context_dict[atk[6]]

    for ap in attack_properties:
        attack_dict[ap[0]]['properties'].append(property_dict[ap[1]])
        property_dict[ap[1]]['attacks'].append(attack_dict[ap[0]])

    for am in attack_mitigations:
        mitigation = mitigation_dict.get(am[1], None)
        if mitigation:
            attack_dict[am[0]]['mitigations'].append({'mitigation': mitigation, 'rationale': am[2]})
            mitigation_dict[am[1]]['attacks'].append(attack_dict[am[0]])
        else:
            attack_dict[am[0]]['mitigations'].append({'mitigation': None, 'rationale': am[2], 'attacks': [attack_dict[am[0]]]})

    for ac in attack_children:
        attack_dict[ac[0]]['children'].append(attack_dict[ac[1]])
        attack_dict[ac[1]]['parents'].append(attack_dict[ac[0]])

    for pr in property_relations:
        property_dict[pr[0]]['related_properties'].append(property_dict[pr[1]])

    # Automatically generate identifiers and place them in the 'auto_identifier' column for
    # each entity. These functions will modify the supplied dictionaries.
    attack_roots = [a for a in attack_dict.values() if a['parents'] is None or len(a['parents']) == 0]
    gen_attack_ids(attack_roots)

    property_roots = [p for p in property_dict.values() if p['parent'] is None]
    gen_property_ids(property_roots, top=True)

    gen_context_ids(context_dict.values(), 'CX')

    gen_mitigation_ids(mitigation_dict.values(), 'M')

    return property_dict, context_dict, mitigation_dict, attack_dict

PROPERTY_PREFIX = {
    "CONFIDENTIALITY": "P",
    "CORRECTNESS": "C",
    "VERIFIABILITY": "V",
    "DISPUTE_FREENESS": "D",
    "AVAILABILITY": "A"
}

# To determine the prefix to use for certain special top-level properties
def get_property_prefix(identifier):
    """ Determine the prefix to use for certain special top-level properties

        :param identifier: The property for which we check the prefix
        :returns: The single letter prefix to use when auto generating identifiers, or
        None if there is no defined mapping.
    """
    return PROPERTY_PREFIX[identifier] if identifier in PROPERTY_PREFIX else None

#
def gen_attack_ids(roots, prefix=None):
    """ Autogenerate and set attack identifiers. The autogenerated identifiers will be set
        in the 'auto_identifier' key.

        :param roots: The root attacks, as a list of dictionaries.
        :returns: Nothing, modifies the passed in attacks and all their descendants
    """

    # alphabetical order from name is not deterministic (duplicates), we use identifiers
    roots = natsorted(roots, key=lambda value: value['identifier'])

    # track separate indexes for abstract and concrete attacks
    index = 1
    abs_index = 1

    for i, root in enumerate(roots):
        if root['is_abstract']:
          effective_index = abs_index
          abs_index = abs_index + 1
        else:
          effective_index = index
          index = index + 1

        if prefix is None:
            attack_prefix = 'AATK' if root['is_abstract'] == 1 else 'ATK'
            root['auto_identifier'] = f"{attack_prefix}{effective_index}"
        else:
            root['auto_identifier'] = f"{prefix}.{effective_index}"

        if len(root['children']) > 0:
            gen_attack_ids(root['children'], root['auto_identifier'])

def gen_property_ids(roots, prefix=None, top=False):
    """ Autogenerate and set property identifiers. The autogenerated identifiers will be set
        in the 'auto_identifier' key.

        :param roots: The root properties, as a list of dictionaries.
        :returns: Nothing, modifies the passed in properties and all their descendants.
    """

    # alphabetical order from name is no good here, we use identifiers
    roots = natsorted(roots, key=lambda value: value['identifier'])

    for index, root in enumerate(roots):
        identifier = root['identifier']

        property_prefix = None
        if prefix is None and root['kind'] == 'Model':
            property_prefix = prefix if prefix is not None else get_property_prefix(identifier)

        if property_prefix is None or top:
            root['auto_identifier'] = identifier
        else:
            root['auto_identifier'] = f"{property_prefix}.{(index + 1)}"

        if len(root['children']) > 0:
            gen_property_ids(root['children'], root['auto_identifier'])

def gen_context_ids(ctxs, prefix):
    """ Autogenerate and set context identifiers. The autogenerated identifiers will be set
        in the 'auto_identifier' key.

        :param ctx: All context dictionaries.
        :returns: Nothing, modifies the passed in contexts.
    """

    ctxs = natsorted(ctxs, key=lambda value: value['name'])

    for index, ctx in enumerate(ctxs):
        ctx['auto_identifier'] = f"{prefix}{(index + 1)}"

# Autogenerate and set mitigation ids
def gen_mitigation_ids(mitigations, prefix):
    """ Autogenerate and set mitigation identifiers. The autogenerated identifiers will be set
        in the 'auto_identifier' key.

        :param ctx: All mitigation dictionaries.
        :returns: Nothing, modifies the passed in mitigations.
    """
    mitigations = natsorted(mitigations, key=lambda value: value['name'])

    for index, mit in enumerate(mitigations):
        mit['auto_identifier'] = f"{prefix}{(index + 1)}"
