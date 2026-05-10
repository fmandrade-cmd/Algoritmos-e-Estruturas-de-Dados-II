/*
    Nome: Fábio Miguel de Andrade
    Data: 09-05-2026

    Implementação do algoritmo Merge Sort
*/

#include <stdio.h>
#include <stdlib.h>

void MERGE(int Array[], int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1 + 1], R[n2 + 1];

    for(int i = 0; i < n1; i++){
        L[i] = Array[p + i];
    }

    for(int j = 0; j < n2; j++){
        R[j] = Array[q + 1 + j];
    }

    L[n1] = 100000;
    R[n2] = 100000;

    int i = 0;
    int j = 0;

    for (int k = p; k <= r; k++){
        if(L[i] < R[j]){
            Array[k] = L[i];
            i = i + 1;
        }else{
            Array[k] = R[j];
            j = j + 1;
        }
    }
}

void MERGE_SORT(int Array[], int p, int r){
    if (p < r){
        int q = (p + r)/2;
        MERGE_SORT(Array, p, q);
        MERGE_SORT(Array, q + 1, r);
        MERGE(Array, p, q, r);
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

    MERGE_SORT(array, 0, n);

    for(int j = 0; j < n; j++){
        printf("%d", array[j]);
    }

    return 0;
}