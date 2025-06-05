import json

# Charger les données depuis les fichiers JSON
with open('flags.json', 'r', encoding='utf-8') as f:
    flags_data = json.load(f)

with open('capitals.json', 'r', encoding='utf-8') as f:
    cities_data = json.load(f)

# Construire un dictionnaire country -> city
city_dict = {entry["country"]: entry["city"] for entry in cities_data}

# Fusionner les données
merged_data = []
for entry in flags_data:
    country = entry["country"]
    merged_entry = {
        "country": country,
        "flag": entry["flag"],
        "city": city_dict.get(country)  # None si pas de ville trouvée
    }
    merged_data.append(merged_entry)

# Écrire le résultat dans un nouveau fichier JSON
with open('merged.json', 'w', encoding='utf-8') as f:
    json.dump(merged_data, f, ensure_ascii=False, indent=4)

print("Fichier merged.json créé avec succès !")
