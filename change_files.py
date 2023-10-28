import os

def rename_files(directory_path):
    # Les anciens horodatages
    old_start_timestamp = "2023_10_26__12_20_34"
    old_end_timestamp = "2023_10_27__14_31_19"

    # Les nouveaux horodatages
    new_start_timestamp = "2023_10_10__16_54_52"
    new_end_timestamp = "2023_10_11__14_44_23"

    # Récupère la liste des fichiers triés
    files = sorted([f for f in os.listdir(directory_path) if f.endswith('.mid') and old_start_timestamp <= f <= old_end_timestamp])

    # Crée une liste des nouveaux horodatages
    new_timestamps = generate_timestamps(new_start_timestamp, new_end_timestamp, len(files))

    # Renomme les fichiers
    for old_name, new_timestamp in zip(files, new_timestamps):
        new_name = f"{new_timestamp}.mid"
        os.rename(os.path.join(directory_path, old_name), os.path.join(directory_path, new_name))

def generate_timestamps(start_timestamp, end_timestamp, n):
    from datetime import datetime, timedelta

    date_format = "%Y_%m_%d__%H_%M_%S"
    start_time = datetime.strptime(start_timestamp, date_format)
    end_time = datetime.strptime(end_timestamp, date_format)

    # Calcul de l'intervalle de temps entre chaque horodatage
    delta = (end_time - start_time) / (n - 1)

    timestamps = []
    for i in range(n):
        timestamps.append((start_time + i * delta).strftime(date_format))

    return timestamps

# Utilisation de la fonction
directory_path = "/tmp/Space_sender/midi_files"
rename_files(directory_path)