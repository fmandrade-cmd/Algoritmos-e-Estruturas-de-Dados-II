/*
    Nome: Fábio Miguel de Andrade
    Data: 10-05-2026

    Implementação do algoritmo Quick Sort - Divisão e Conquista
*/

#include <stdio.h>
#include <stdlib.h>

int Partition(int Array[], int p, int r){
    //Mediada de 3
    int med = (r + p) / 2;
    int aux = 0;

    if (Array[med] < Array[p]) {
        aux = Array[med]; Array[med] = Array[p]; Array[p] = aux;
    }
    if (Array[r] < Array[p]) {
        aux = Array[r]; Array[r] = Array[p]; Array[p] = aux;
    }
    if (Array[r] < Array[med]) {
        aux = Array[r]; Array[r] = Array[med]; Array[med] = aux;
    }

    aux = Array[r];
    Array[r] = Array[med];
    Array[med] = aux;
    
    //Partition
    int x = Array[r];
    int i = p - 1; 
    int aux2 = 0;
    for(int j = p; j < r; j++){
        if(Array[j] <= x){
            i++;
            //Swap
            aux2 = Array[i];
            Array[i] = Array[j];
            Array[j] = aux2;
        }
    }
    aux2 = Array[i + 1];
    Array[i + 1] = Array[r];
    Array[r] = aux2;

    return i + 1;
}

void QuickSort(int Array[], int p, int r){
    if(p < r){
        int q = Partition(Array, p, r);
        QuickSort(Array, p, q - 1);
        QuickSort(Array, q + 1, r);
    }
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