/*
    Exercicio de Implemetacao do Algoritmo Insertion Sort
    Nome: Fábio Miguel de Andrade
    Data: 09-05-2026

    Estudos para a P1;
*/

#include <stdio.h>
#include <stdlib.h>

void INSERTION_SORT(int Array[], int n){
    for(int i = 1; i < n; i++){
        int key = Array[i];
        int j;
        j = i - 1;
        while (j >= 0 && Array[j] > key) {
            Array[j + 1] = Array[j];
            j = j - 1;
        }
        Array[j + 1] = key;
    }
}

int main() {

    int n, val;
    val = 0;
    //Pede um valor para N
    scanf("%d", &n);

    int vetor[n];

    //Insere valores no vetor
    for(int i = 0; i < n ; i++){
        scanf("%d", &val);
        vetor[i] = val;
    }

    INSERTION_SORT(vetor, n);

    //Imprimir o vetor
    for(int j = 0; j < n; j++){
        printf("%d", vetor[j]);
    }

    return 0;
}