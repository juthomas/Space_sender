import argparse
import pandas as pd

# Créez un parseur d'arguments
parser = argparse.ArgumentParser(description="Lire un fichier CSV")
parser.add_argument("fichier_csv", help="Chemin du fichier CSV à lire")

# Analysez les arguments
args = parser.parse_args()

# Utilisez pandas pour lire le fichier CSV
df = pd.read_csv(args.fichier_csv, sep="; ")


# Enregistrer le DataFrame fusionné dans un nouveau fichier CSV
df.to_csv(args.fichier_csv, index=False, sep=";")