/*
    Nome: Fábio Miguel de Andrade
    Data: 10-05-2026

    Implementação do algoritmo Counting Sort - O(n)
*/

#include <stdio.h>
#include <stdlib.h>

int DEFINE_K(int A[], int n){
    int x = 0;
    for(int i = 0; i < n; i++){
        if(A[i] > x){
            x = A[i];
        }
    }
    return x;
}

void COUNTING_SORT(int A[], int B[], int n){
    int k = DEFINE_K(A, n);
    int C[k + 1];
    for(int i = 0; i <= k; i++){
        C[i] = 0;
    }

    for(int j = 0; j < n; j++){
        C[A[j]] = C[A[j]] + 1;      //Calcula a Frequênca de cada valor de A
    }

    for(int w = 1; w <= k; w++){
        C[w] = C[w] + C[w - 1];     //Sobrescreve o Vetor C
    }

    for(int z = n - 1; z >= 0; z--){
        B[C[A[z]] - 1] = A[z];
        C[A[z]] = C[A[z]] - 1;
    }
}

int main() {

    int n, val, k;
    val = 0;

    scanf("%d", &n);

    int a[n];
    int b[n];


    for(int i = 0; i < n; i++){
        scanf("%d", &val);
        a[i] = val;
    }

    COUNTING_SORT(a, b, n);

    for(int j = 0; j < n; j++){
        printf("%d", b[j]);
    }

    return 0;
}