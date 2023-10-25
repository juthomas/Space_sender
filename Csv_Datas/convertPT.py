import pandas as pd

# Liste de tous les fichiers CSV
# input = "PT0_20231010.csv"
# output = "PTC0_20231010.csv"

# input = "PT0_20231011.csv"
# output = "PTC0_20231011.csv"

# input = "PT1_20231011.csv"
# output = "PTC1_20231011.csv"

# input = "PT3_20231011.csv"
# output = "PTC3_20231011.csv"

input = "PT4_20231011.csv"
output = "PTC4_20231011.csv"

# Lire le premier fichier
df = pd.read_csv(input, sep=";")

print(f"Noms de colonnes pour {input} : ", df.columns)

# Fonction de conversion
def convertir(valeur):
    return int(valeur * 4095*0.02/5)

# Appliquer le facteur de conversion
for colonne in ['PT0 (degC)','PT1 (degC)','PT2 (degC)','PT3 (degC)','PT4 (degC)','PT5 (degC)','PT6 (degC)','PT7 (degC)']:
    df[colonne] = df[colonne].apply(convertir)

# Enregistrer le DataFrame fusionné dans un nouveau fichier CSV
df.to_csv(output, index=False, sep=";")