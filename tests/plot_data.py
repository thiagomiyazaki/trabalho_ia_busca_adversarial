import os
import sys
import numpy as np
import matplotlib.pyplot as plt
import glob

def ler_arquivo(arquivo):
    with open(arquivo, 'r') as f:
        numeros = [float(line.strip()) for line in f]
    return numeros

def calcular_estatisticas(numeros):
    media = np.mean(numeros)
    desvio_padrao = np.std(numeros)
    return media, desvio_padrao

def plotar_grafico(pastas, medias, desvios_padrao):
    plt.bar(pastas, medias, yerr=desvios_padrao, capsize=5)
    plt.xlabel('Arquivo')
    plt.ylabel('Média')
    plt.title('Média e Desvio Padrão por Arquivo')
    plt.xticks(rotation=90)
    plt.tight_layout()
    plt.savefig('data.pdf')

def output_parameters(pastas, medias, desvios_padrao):
    with open('stats_values.txt', 'w') as file:
        for i in range(len(pastas)):
            file.write(f'{pastas[i]} : {medias[i]} : {desvios_padrao[i]}\n')


def main(pasta):

    pastas = []
    medias = []
    desvios_padrao = []

    for arquivo in glob.glob(os.path.join(pasta, '*.txt')):
        numeros = ler_arquivo(arquivo)
        media, desvio_padrao = calcular_estatisticas(numeros)
        pastas.append(os.path.basename(arquivo))
        medias.append(media)
        desvios_padrao.append(desvio_padrao)

    plotar_grafico(pastas, medias, desvios_padrao)
    output_parameters(pastas, medias, desvios_padrao)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Uso: python3 process_numbers.py <caminho_do_pasta>")
        sys.exit(1)
    main(sys.argv[1])