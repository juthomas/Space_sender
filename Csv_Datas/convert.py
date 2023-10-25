import pandas as pd

# Liste de tous les fichiers CSV
# fichiers = ["OSCAR0_20231010.csv", "currents0_20231010.csv", "PD0_20231010.csv", "PT0_20231010.csv", "temperatures0_20231010.csv"]
# output = "Fusion0_20231010.csv"

# fichiers = ["OSCAR0_20231011.csv", "currents0_20231011.csv", "PD0_20231011.csv", "PT0_20231011.csv", "temperatures0_20231011.csv"]
# output = "Fusion0_20231011.csv"

# fichiers = ["OSCAR1_20231011.csv", "currents1_20231011.csv", "PD1_20231011.csv", "PT1_20231011.csv", "temperatures1_20231011.csv"]
# output = "Fusion1_20231011.csv"

input = "PD0_20231010.csv"
output = "PDC0_20231010.csv"




# Lire le premier fichier
df = pd.read_csv(input, sep="; ")

print(f"Noms de colonnes pour {input} : ", df.columns)

# Fonction de conversion
def convertir(valeur):
    return int(valeur * 4095/5)

# Appliquer le facteur de conversion
for colonne in ['PD0 (V)', 'PD1 (V)', 'PD2 (V)', 'PD3 (V)', 'PD4 (V)', 'PD5 (degC)']:
    df[colonne] = df[colonne].apply(convertir)

# Enregistrer le DataFrame fusionné dans un nouveau fichier CSV
df.to_csv(output, index=False, sep="; ")