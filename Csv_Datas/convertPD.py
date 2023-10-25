import pandas as pd

# Liste de tous les fichiers CSV
# input = "PD0_20231010.csv"
# output = "PDC0_20231010.csv"

# input = "PD0_20231011.csv"
# output = "PDC0_20231011.csv"

# input = "PD1_20231011.csv"
# output = "PDC1_20231011.csv"

# input = "PD3_20231011.csv"
# output = "PDC3_20231011.csv"

input = "PD4_20231011.csv"
output = "PDC4_20231011.csv"

# Lire le premier fichier
df = pd.read_csv(input, sep=";")

print(f"Noms de colonnes pour {input} : ", df.columns)

# Fonction de conversion
def convertir(valeur):
    return int(valeur * 4095/5)

# Appliquer le facteur de conversion
for colonne in ['PD0 (V)', 'PD1 (V)', 'PD2 (V)', 'PD3 (V)', 'PD4 (V)', 'PD5 (degC)']:
    df[colonne] = df[colonne].apply(convertir)

# Enregistrer le DataFrame fusionné dans un nouveau fichier CSV
df.to_csv(output, index=False, sep=";")