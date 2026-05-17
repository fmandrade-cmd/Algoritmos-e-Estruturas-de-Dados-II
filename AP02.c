/*
    Autor: Fábio Miguel de Andrade
    Data: 17-05-2026

    Estudos para P1

    AP02 - Exercício de ordenação pelo método de Divisão e Conquista
           aplicando o algoritmo Merge Sort
*/

#include <stdio.h>
#include <stdlib.h>

int CalcularQuedaDrastica(int Array[], int tamanho){
    long long int quedas = 0;
    for(int i = 0; i < tamanho; i++){
        for(int j = i + 1; j < tamanho; j++){
            if(Array[i] > 2 * Array[j]){
                quedas++;
            }
        }
    }
    return quedas;
}

void Merge(int Array[], int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1], R[n2];

    for(int i = 0; i < n1; i++){
        L[i] = Array[p + i];
    }

    for(int j = 0; j < n2; j++){
        R[j] = Array[q + 1 + j]; 
    }

    int i = 0;
    int j = 0;

    for(int k = p; k <= r; k++){
        if(L[i] < R[j]){
            Array[k] = L[i];
            i++;
        }else{
            Array[k] = R[j];
            j++;
        }
    }
}

void MergeSort(int Array[], int p ,int r){
    if(p < r){
        int q = (p + r) / 2;
        MergeSort(Array, p, q);
        MergeSort(Array, q + 1, r);
        Merge(Array, p, q, r);
    }
}

int main() {
    
    //Entrada de Dados
    int dias, valAtivo, quedas; 
    scanf("%d", &dias);
    if (dias < 1 || dias > 100000){
        return 0;
    }
    int vetorAtivos[dias];
    for(int i = 0; i < dias; i++){
        scanf("%d", &valAtivo);
        vetorAtivos[i] = valAtivo;
    }

    //Chamar o contador de quedas
    quedas = CalcularQuedaDrastica(vetorAtivos, dias);
    printf("%d\n", quedas);

    //Chamar o Merge Sort
    MergeSort(vetorAtivos, 0, dias);

    //Saida de Dados
    for(int x = 0; x < dias; x++){
        printf("%d ", vetorAtivos[x]);
    }

    return 0;
}