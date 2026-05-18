/*
    Autor: Fábio Miguel de Andrade
    Data: 17-05-2026

    Estudos para P1

    AP03 - Exercício de ordenação pelo método de Divisão e Conquista
           aplicando o algoritmo Quick Sort
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int gravidade;
}Paciente;

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

    //Entrada de Dados
    int numPacientes, id, gravidade;
    
    scanf("%d", &numPacientes);

    int *vetorPacientes = malloc(numPacientes * sizeof(Paciente));

    for(int i = 0; i < numPacientes; i++){
        
    }

    return 0;
}