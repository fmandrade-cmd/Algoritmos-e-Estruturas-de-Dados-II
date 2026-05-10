/*
    Nome: Fábio Miguel de Andrade
    Data: 09-05-2026

    Implementação do algoritmo Bubble Sort
*/

#include <stdio.h>
#include <stdlib.h>

void BUBBLE_SORT(int Array[], int n){
    while (n > 0){
        for(int i = 0; i < n - 1; i++){
            if(Array[i] > Array[i + 1]){
                //Swap 
                int aux = Array[i];
                Array[i] = Array[i + 1];
                Array[i + 1] = aux;
            }
        }
        n = n - 1;
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

    BUBBLE_SORT(vetor, n);

    for(int j = 0; j < n; j++){
        printf("%d", vetor[j]);
    }

    return 0;
}