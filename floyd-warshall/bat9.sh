#!/bin/bash

# Binário
floyd=./floyd-warshall.bin

echo "Testando algoritmo de Floyd-Warshall"

# Contadores para estatísticas
total=0
sucesso=0
falhas=0
gabaritos_ausentes=0

for entrada in entrada/*.mtx
do
    ((total++))
    echo -e "\e[33mInstância $entrada\e[0m"
    
    # Extrai o número do arquivo (input_1.mtx → 1)
    num=$(basename "$entrada" | grep -o -E '[0-9]+')
    gabarito="saida/output_${num}.mtx"
    
    # Verifica se o gabarito existe
    if [ ! -f "$gabarito" ]; then
        echo -e "\e[31mErro: Gabarito $gabarito não encontrado\e[0m"
        ((gabaritos_ausentes++))
        continue
    fi
    
    # Executa o Floyd-Warshall
    $floyd -f "$entrada" > temp_resultado.mtx 2>temp_erro.log
    
    # Verifica erros na execução
    if [ $? -ne 0 ]; then
        echo -e "\e[31mErro na execução:\e[0m"
        cat temp_erro.log
        ((falhas++))
        rm -f temp_resultado.mtx temp_erro.log
        continue
    fi
    
    # Compara com o gabarito
    if diff -w temp_resultado.mtx "$gabarito" > /dev/null; then
        echo -e "\e[32mOK\e[0m"
        ((sucesso++))
    else
        echo -e "\e[31mFalha\e[0m"
        echo "Diferenças:"
        diff -w --color=always temp_resultado.mtx "$gabarito" | head -n 5
        ((falhas++))
    fi
    
    # Limpeza
    rm -f temp_resultado.mtx temp_erro.log
done

# Relatório final
echo -e "\n\e[34m===== RELATÓRIO FINAL =====\e[0m"
echo "Total de testes: $total"
echo -e "\e[32mSucessos: $sucesso\e[0m"
echo -e "\e[31mFalhas: $falhas\e[0m"
echo "Gabaritos ausentes: $gabaritos_ausentes"