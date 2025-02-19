import matplotlib.pyplot as plt
import numpy as np

algoritmos = ["Bubble Sort", "Heap Sort", "Inserção Direta", "Merge Sort", 
              "Quick Sort", "Seleção Direta", "Shell Sort"]

tempos_5000_pior = [117.418, 1.08662, 32.5269, 0.456066, 1.2, 29.6068, 0.272353]
tempos_5000_melhor = [28, 1, 0.01, 0.4, 0.9, 31, 0.2]
tempos_5000_aleatorio = [95, 1, 17, 0.7, 1, 32, 0.8]

tempos_10000_pior = [783, 10, 132, 4, 1.4, 488, 2]
tempos_10000_melhor = [123, 2.7, 0.03, 1.1, 1.0, 133, 0.4]
tempos_10000_aleatorio = [415, 11, 64, 7, 1.3, 454, 1.9]

def plot_resultados_log(titulos, valores, titulo_principal, filename):
    x = np.arange(len(algoritmos))  
    width = 0.25  

    fig, ax = plt.subplots(figsize=(12, 6))
    
    ax.bar(x - width, valores[0], width, label=titulos[0])
    ax.bar(x, valores[1], width, label=titulos[1])
    ax.bar(x + width, valores[2], width, label=titulos[2])

    ax.set_yscale('log')  
    ax.set_xlabel('Algoritmos')
    ax.set_ylabel('Tempo (ms)')
    ax.set_title(titulo_principal)
    ax.set_xticks(x)
    ax.set_xticklabels(algoritmos, rotation=45)
    ax.legend()

    plt.tight_layout()
    plt.savefig(filename)
    plt.show()

plot_resultados_log(
    ["Pior Caso", "Melhor Caso", "Caso Aleatório"],
    [tempos_5000_pior, tempos_5000_melhor, tempos_5000_aleatorio],
    "Comparação de Algoritmos (5000 itens, 20 repetições) - Escala Log",
    "5000_items_log.png"
)

plot_resultados_log(
    ["Pior Caso", "Melhor Caso", "Caso Aleatório"],
    [tempos_10000_pior, tempos_10000_melhor, tempos_10000_aleatorio],
    "Comparação de Algoritmos (10000 itens, 100 repetições) - Escala Log",
    "10000_items_log.png"
)
