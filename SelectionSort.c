/*
    Exercicio de Implemetacao do Algoritmo Selection Sort
    Nome: Fábio Miguel de Andrade
    Data: 09-05-2026

    Estudos para a P1;
*/

#include <stdio.h>
#include <stdlib.h>

void SELECTION_SORT(int Array[], int n){
    for(int i = 0; i < n; i++){
        int min = i;
        for(int j = i + 1; j < n; j++){
            if(Array[min] > Array[j]){
                min = j;
            }
        }
        //Swap
        int aux = Array[i];
        Array[i] = Array[min];
        Array[min] = aux;
    }
}

int main() {

    int n, val;
    val = 0;

    scanf("%d", &n);

    int vetor[n];

    for(int i = 0; i < n; i++){
        scanf("%d", &val);
        vetor[i] = val;
    }

    SELECTION_SORT(vetor, n);

    for(int j = 0; j < n; j++){
        printf("%d", vetor[j]);
    }
    return 0;
}