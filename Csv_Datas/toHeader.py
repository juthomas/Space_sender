import argparse
import pandas as pd

# Créez un parseur d'arguments
parser = argparse.ArgumentParser(description="Lire un fichier CSV")
parser.add_argument("fichier_csv", help="Chemin du fichier CSV à lire")

# Analysez les arguments
args = parser.parse_args()

# Utilisez pandas pour lire le fichier CSV
df = pd.read_csv(args.fichier_csv, sep=";")

starting_index = 1

list_of_steps = ""
# Itérez sur les lignes du DataFrame
for index, row in df.iterrows():
    # print("Index:", index)
    # print("Row data:", row)
    # print("Accès à une colonne spécifique (par exemple 'nom_de_la_colonne'):", row['Time'])
    list_of_steps += f"g_all_data_step_{index + starting_index}, "
    print(f"static const t_data g_all_data_step_{index + starting_index}[] =  {{")
    print(f"	(t_data){{.name = \"Photodiode_1\", .offset = offsetof(t_sensors, photodiode_1), .data_type = INTEGER, .int_data = {row['PD0 (V)']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Photodiode_2\", .offset = offsetof(t_sensors, photodiode_2), .data_type = INTEGER, .int_data = {row['PD1 (V)']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Photodiode_3\", .offset = offsetof(t_sensors, photodiode_3), .data_type = INTEGER, .int_data = {row['PD2 (V)']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Photodiode_4\", .offset = offsetof(t_sensors, photodiode_4), .data_type = INTEGER, .int_data = {row['PD3 (V)']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Photodiode_5\", .offset = offsetof(t_sensors, photodiode_5), .data_type = INTEGER, .int_data = {row['PD4 (V)']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Photodiode_6\", .offset = offsetof(t_sensors, photodiode_6), .data_type = INTEGER, .int_data = {row['PD5 (degC)']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Temperature_1\", .offset = offsetof(t_sensors, temperature_1), .data_type = INTEGER, .int_data = {row['PT1']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Temperature_2\", .offset = offsetof(t_sensors, temperature_2), .data_type = INTEGER, .int_data = {row['PT2']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Temperature_3\", .offset = offsetof(t_sensors, temperature_3), .data_type = INTEGER, .int_data = {row['PT3']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Temperature_4\", .offset = offsetof(t_sensors, temperature_4), .data_type = INTEGER, .int_data = 0, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Temperature_5\", .offset = offsetof(t_sensors, temperature_5), .data_type = INTEGER, .int_data = 0, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Temperature_6\", .offset = offsetof(t_sensors, temperature_6), .data_type = INTEGER, .int_data = 0, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Temperature_7\", .offset = offsetof(t_sensors, temperature_7), .data_type = INTEGER, .int_data = 0, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Temperature_8\", .offset = offsetof(t_sensors, temperature_8), .data_type = INTEGER, .int_data = 0, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Temperature_9\", .offset = offsetof(t_sensors, temperature_9), .data_type = INTEGER, .int_data = 0, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Temperature_10\", .offset = offsetof(t_sensors, temperature_10), .data_type = INTEGER, .int_data = 0, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Microphone\", .offset = offsetof(t_sensors, microphone), .data_type = BINARY, .binary = 0}},")
    print(f"	(t_data){{.name = \"Spectro_current\", .offset = offsetof(t_sensors, spectro_current), .data_type = INTEGER, .int_data = {row['I INA SPECTRO (mA)']}, .int_delta = 0}},//TODO : Manage negative values")#TODO : Manage negative values
    print(f"	(t_data){{.name = \"Organ_current\", .offset = offsetof(t_sensors, organ_current), .data_type = INTEGER, .int_data = {row['I INA OSCAR (mA)']}, .int_delta = 0}},//TODO : Manage negative values")#TODO : Manage negative values
    print(f"	(t_data){{.name = \"Vin_current\", .offset = offsetof(t_sensors, vin_current), .data_type = INTEGER, .int_data = {row['I INA DC_BUS (mA)']}, .int_delta = 0}},//TODO : Manage negative values")#TODO : Manage negative values
    print(f"	(t_data){{.name = \"Q7_current\", .offset = offsetof(t_sensors, q7_current), .data_type = INTEGER, .int_data = {row['I INA Q7 (mA)']}, .int_delta = 0}},//TODO : Manage negative values")#TODO : Manage negative values
    print(f"	(t_data){{.name = \"5v_current\", .offset = offsetof(t_sensors, t5v_current), .data_type = INTEGER, .int_data = {row['I INA 5V (mA)']}, .int_delta = 0}},//TODO : Manage negative values")#TODO : Manage negative values
    print(f"	(t_data){{.name = \"3.3v_current\", .offset = offsetof(t_sensors, t3_3v_current), .data_type = INTEGER, .int_data = {row['I INA 3V3 (mA)']}, .int_delta = 0}},//TODO : Manage negative values")#TODO : Manage negative values
    print(f"	(t_data){{.name = \"Motor_current\", .offset = offsetof(t_sensors, motor_current), .data_type = INTEGER, .int_data = {row['I INA MOTORS (mA)']}, .int_delta = 0}},//TODO : Manage negative values")#TODO : Manage negative values
    print(f"	(t_data){{.name = \"Carousel_state\", .offset = offsetof(t_sensors, carousel_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Lid_state\", .offset = offsetof(t_sensors, lid_state), .data_type = INTEGER, .int_data = 0, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Organ_1\", .offset = offsetof(t_sensors, organ_1), .data_type = INTEGER, .int_data = {row['POT1']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Organ_2\", .offset = offsetof(t_sensors, organ_2), .data_type = INTEGER, .int_data = {row['POT2']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Organ_3\", .offset = offsetof(t_sensors, organ_3), .data_type = INTEGER, .int_data = {row['POT3']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Organ_4\", .offset = offsetof(t_sensors, organ_4), .data_type = INTEGER, .int_data = {row['POT4']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Organ_5\", .offset = offsetof(t_sensors, organ_5), .data_type = INTEGER, .int_data = {row['POT5']}, .int_delta = 0}},")
    print(f"	(t_data){{.name = \"Organ_6\", .offset = offsetof(t_sensors, organ_6), .data_type = INTEGER, .int_data = {row['POT6']}, .int_delta = 0}}}};")
    print(f"")

print(f"{list_of_steps}")
