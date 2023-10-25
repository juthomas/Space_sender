import pandas as pd

# Liste de tous les fichiers CSV
# fichiers = ["OSCAR0_20231010.csv", "currents0_20231010.csv", "PD0_20231010.csv", "PT0_20231010.csv", "temperatures0_20231010.csv"]
# output = "Fusion0_20231010.csv"

# fichiers = ["OSCAR0_20231011.csv", "currents0_20231011.csv", "PD0_20231011.csv", "PT0_20231011.csv", "temperatures0_20231011.csv"]
# output = "Fusion0_20231011.csv"

# fichiers = ["OSCAR1_20231011.csv", "currents1_20231011.csv", "PD1_20231011.csv", "PT1_20231011.csv", "temperatures1_20231011.csv"]
# output = "Fusion1_20231011.csv"

fichiers = ["OSCAR3_20231011.csv", "currents3_20231011.csv", "PD3_20231011.csv", "PT3_20231011.csv", "temperatures3_20231011.csv"]
output = "Fusion3_20231011.csv"




# Lire le premier fichier
df_final = pd.read_csv(fichiers[0], sep="; ")

for fichier in fichiers:
    df_temp = pd.read_csv(fichier, sep="; ")
    print(f"Noms de colonnes pour {fichier} : ", df_temp.columns)

# Fusionner avec d'autres fichiers
for fichier in fichiers[1:]:
    # Lire le fichier actuel
    df_temp = pd.read_csv(fichier, sep="; ")
    df_temp.drop(columns=['Date', 'Line'], inplace=True)
    
    # Fusionner sur la colonne "Time"
    df_final = pd.merge(df_final, df_temp, on='Time', how='inner')
    # df_final = pd.merge_asof(df_final, df_temp, left_index=True, right_index=True, direction='nearest')


# Trier le DataFrame final selon le timestamp
df_final = df_final.sort_values(by='Time')
df_final['Line'] = df_final.index

# Enregistrer le DataFrame fusionné dans un nouveau fichier CSV
df_final.to_csv(output, index=False)