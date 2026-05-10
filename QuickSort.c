/*
    Nome: Fábio Miguel de Andrade
    Data: 10-05-2026

    Implementação do algoritmo Quick Sort - Divisão e Conquista
*/

#include <stdio.h>
#include <stdlib.h>

int PARTITION(int Array[], int p, int r){
    int x = Array[r];
    int i = p - 1;
    for (int j = p; j < r - 1; j++){
        if(Array[j < x]){
            i = i + 1;
            //SWAP
            int aux = Array[i];
            Array[i] = Array[j];
            Array[j] = aux;
        }
    }
    //SWAP
    int aux2 = Array[i + 1];
    Array[i + 1] = Array[r];
    Array[r] = aux2;

    return (i + 1);
}

void QUICK_SORT(int Array[], int p, int r){
    int q = PARTITION(Array, p, r);
    QUICK_SORT(Array, p, q - 1);
    QUICK_SORT(Array, q + 1, r);
}

int main() {

    int n, val;
    val = 0;

    scanf("%d", &n);

    int array[n];

    for(int i = 0; i < n; i++){
        scanf("%d", &val);
        array[i] = val;
    }

    QUICK_SORT(array, 0, n);

    for(int j = 0; j < n; j++){
        printf("%d", array[j]);
    }

    return 0;
}