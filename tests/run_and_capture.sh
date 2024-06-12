#!/bin/bash

# Listas de argumentos
arg1_list=(0 1 2 3)
arg2_list=(1 2 3 4)

algoritmo="MinMax"

# Número de execuções por combinação de argumentos
num_execucoes=100

# Diretório para armazenar os arquivos de saída
output_dir="outputs"
rm -rf $output_dir 
mkdir -p $output_dir

# Itera sobre todas as combinações de arg1 e arg2
for arg1 in "${arg1_list[@]}"; do
    echo 
    for arg2 in "${arg2_list[@]}"; do

        case $arg1 in
            0)
                algoritmo="MinMax"
                ;;
            1)
                algoritmo="Alpha_Beta_Pruning"
                ;;
            2)
                algoritmo="MAX_AB_Pruning"
                ;;
            3)
                algoritmo="MIN_AB_Pruning"
                ;;
        esac

        echo "Executando $algoritmo com $arg2 espacos pre ocupados"
        
        # Nome do arquivo de saída baseado na combinação de argumentos
        output_file="${output_dir}/output_${algoritmo}_${arg2}.txt"
        
        # Limpa o arquivo de saída se existir
        > $output_file
        
        for i in $(seq 1 $num_execucoes); do
            ./run_tests.out $arg2 $arg1 2>> $output_file
        done
    done
done

echo 

# Passa a pasta de saída para o script Python
python3 plot_data.py $output_dir
