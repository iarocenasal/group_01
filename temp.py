

import pandas as pd
import matplotlib.pyplot as plt

# Reemplaza con tu Channel ID real
channel_id = "2952150"
url = f"https://api.thingspeak.com/channels/{channel_id}/feeds.csv"

# Leer los datos desde ThingSpeak
df = pd.read_csv(url)
df["created_at"] = pd.to_datetime(df["created_at"])

# Mostrar las primeras 5 filas para comprobar
print("Primeras filas del archivo descargado:")
print(df.head())

# Guardar los datos localmente en un archivo CSV
df.to_csv("datos_suelo.csv", index=False)
print("\nArchivo guardado como datos_suelo.csv")

# Graficar humedad
plt.plot(df["created_at"], df["field1"].astype(float), label="Humedad")

# Graficar temperatura
plt.plot(df["created_at"], df["field2"].astype(float), label="Temperatura", color='orange')

plt.title("Datos del suelo desde ThingSpeak")
plt.xlabel("Fecha")
plt.ylabel("Valor")
plt.grid()
plt.legend()
plt.show()