import argparse
import yaml
import json

SETTINGS_JSON = ".vscode/settings.json"
OUT_OF_SCOPE = "Out of scope"

def read_yaml(file_path):
    with open(file_path, 'r') as file:
        data = yaml.safe_load(file)
        return data

def read_json(file_path):
    with open(file_path) as f:
        d = json.load(f)
        return d

def write_json(file_path, data):
    with open(file_path, 'w', encoding='utf-8') as f:
        json.dump(data, f, ensure_ascii=False, indent=4)

def get_properties(yaml_data):
    ret = []
    for identifier, values in yaml_data.items():
        if isinstance(values, str):
            ret.append(identifier)
        elif isinstance(values, list):
            ret.append(identifier)
            ret = ret + get_properties(values[1])

    return ret

def get_abstract_attacks(yaml_data, parent=None):
    ret = []
    for item in yaml_data:
        keys = list(item.keys())
        children = None
        if 'children' in keys:
            children = item['children']
            keys.remove('children')

        attack = item[keys[0]]
        if 'kind' not in attack:
            continue

        if attack['kind'] != 'A':
            continue

        # name
        name = attack['name']
        if parent is not None:
            reference = f"{parent}.{name}"
        else:
            reference = f"{name}"

        ret.append(reference)

        if children is not None:
            ret = ret + get_abstract_attacks(children, name)

    return ret

def main():
    try:
        parser = argparse.ArgumentParser(description='Parse YAML file')
        parser.add_argument('yaml_file', type=str, help='Path to the YAML file')
        args = parser.parse_args()

        yaml_file_path = args.yaml_file
        yaml_data = read_yaml(yaml_file_path)
        keywords = []
        keywords.append({'text': f'{OUT_OF_SCOPE}', 'color': '#090', "backgroundColor": "rgba(0,0,0,0)"})

        mitigations = yaml_data.get('mitigations', [])
        mitigation_keys = sorted(mitigations.keys(), reverse=True)
        for key in mitigation_keys:
            next = {'text': f'{mitigations[key][0]}', 'color': '#090', "backgroundColor": "rgba(0,0,0,0)"}
            keywords.append(next)

        properties = yaml_data.get('properties', [])
        properties = get_properties(properties)
        properties = sorted(properties, key = lambda p: len(p), reverse=True)
        for value in properties:
            next = {'text': f'{value}', 'regex': {'pattern': f'\\b{value}\\b'}, 'color': '#0bb', "backgroundColor": "rgba(0,0,0,0)"}
            keywords.append(next)

        contexts = yaml_data.get('contexts', [])
        for value in contexts:
            next = {'text': f'{value}', 'regex': {'pattern': f'\\b{value}\\b'}, 'color': '#999', "backgroundColor": "rgba(0,0,0,0)"}
            keywords.append(next)

        attacks = yaml_data.get('attacks', [])

        attacks = get_abstract_attacks(attacks)
        attacks = sorted(attacks, key = lambda a: len(a), reverse=True)

        for value in attacks:
            # Use this for italic but not red color on abstract attacks
            # next = {'text': f'{value}', 'color': "editor.color", "fontStyle": "italic", "backgroundColor": "rgba(0,0,0,0)"}
            next = {'text': f'{value}', 'color': "#a00", "fontStyle": "italic", "backgroundColor": "rgba(0,0,0,0)"}
            keywords.append(next)

        json = read_json(SETTINGS_JSON)

        json['todohighlight.keywords'] = keywords
        write_json(SETTINGS_JSON, json)

    except Exception as e:
        print(f"highlight_yaml.py: {e}")
        exit(1)

if __name__ == "__main__":
    main()
