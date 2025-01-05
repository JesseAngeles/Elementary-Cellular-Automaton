import matplotlib.pyplot as plt
import csv

# Ruta del archivo CSV
file_path = "data/histogram.csv"


def normalize_and_trim(data):
    """Recorta ceros de los extremos y normaliza los datos."""
    while data and data[0] == 0:
        data.pop(0)
    while data and data[-1] == 0:
        data.pop()
    
    total = sum(data)
    if total > 0:
        data = [value / total for value in data]
    return data

def plot_histogram(data, index):
    """Genera y muestra un histograma a partir de los datos proporcionados."""
    plt.figure()
    plt.bar(range(len(data)), data, color='blue', alpha=0.7, edgecolor='black')
    plt.title(f"Histograma {index + 1}")
    plt.xlabel("Valores")
    plt.ylabel("Frecuencia Normalizada")
    plt.show()

def plot_histograms(file_path, specific_line=None):
    """Grafica todos los histogramas o solo el de una línea específica."""
    with open(file_path, 'r') as file:
        reader = csv.reader(file)
        for index, row in enumerate(reader):
            # Si se solicita una línea específica, ignorar las demás
            if specific_line is not None and index != specific_line - 1:
                continue
            
            # Convertir la fila a enteros y normalizar
            raw_data = [int(value) if value.strip() else 0 for value in row]
            data = normalize_and_trim(raw_data)
            
            # Generar y mostrar el histograma
            plot_histogram(data, index)
            
            # Detener si es una línea específica
            if specific_line is not None:
                break

# Configuración
print("¿Qué deseas hacer?")
print("1: Imprimir todos los histogramas")
print("2: Imprimir un histograma específico")
choice = input("Ingresa tu elección (1 o 2): ")

if choice == "1":
    # Mostrar todos los histogramas
    plot_histograms(file_path)
elif choice == "2":
    # Solicitar la línea específica
    line_number = int(input("Ingresa el número de línea que deseas imprimir: "))
    plot_histograms(file_path, specific_line=line_number)
else:
    print("Elección no válida.")