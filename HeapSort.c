/*
    Nome: Fábio Miguel de Andrade
    Data: 10-05-2026

    Implementação do algoritmo Heap Sort

    Descrição: O algoritmo Heap Sort se babseia na lógica de 
               Transformar e Conquistar. De maneira semelhante
               ao Quick Sort, ele tranforma um problema grande
               em subproblemas a serem corrigidos.

               -Heap: Estrutura parcialmente ordenada que é adequada
               para a implementação de Filas de Prioridade. Se trata 
               de uma árvore binária balanceada, na qual o nó pai é 
               sempre maior que o filho (Arvore Binária padrão)

               -Max Heap: Arvore balanceada onde o valor do nó PAI é
               sempre MAIOR que o valor do nó FILHO, ou seja, o maior 
               valor dessa árvore está na raiz.

               -MaxHeapfy: Quando a entrada é uma árvore que não corresponde
               a um Heap (nesse caso Max Heap), temos que fazer a manutenção 
               das proriedades. Como estamos usando uma Max Heap, queremos 
               que a raiz seja o maior valor da árvore e que PAI > FILHO.

               -BuildMaxHeap: Quando temos uma arvore em que todos os elementos 
               fogem da regra, começamos - de baixo para cima - a aplicar o 
               MaxHeapfy, com o objetivo de percorrer a estrutura inteira 
               corrigindo a relação PAI > FILHO.

               -HeapSort: 
*/

#include <stdio.h>
#include <stdlib.h>

// Mantém a propriedade do Max Heap
void MaxHeapfy(int A[], int size, int i){
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int max = i; // Assume que o pai é o maior

    if(l < size && A[l] > A[max]){
        max = l;
    }
    if(r < size && A[r] > A[max]){
        max = r;
    }
    if(max != i){
        int swap = A[i];
        A[i] = A[max];
        A[max] = swap;
        
        // Chamada recursiva para ajustar os nós abaixo
        MaxHeapfy(A, size, max);
    }
}

// Transforma o array em um Max Heap válido
void BuildMaxHeap(int A[], int size){
    // (size/2) - 1 encontra o último nó pai da árvore (evita olhar as folhas)
    for(int k = (size / 2) - 1; k >= 0; k--){
        MaxHeapfy(A, size, k);
    }
}

// Algoritmo Heap Sort principal
void HeapSort(int A[], int size){
    // 1. Organiza o array como um Max Heap pela primeira vez
    BuildMaxHeap(A, size);

    // 2. Extrai os elementos do Heap de trás para frente
    for (int i = size - 1; i > 0; i--) {
        // O maior elemento sempre está na raiz (A[0]). 
        // Jogamos ele para o final do array (na parte que já vai ficando ordenada).
        int swap = A[0];
        A[0] = A[i];
        A[i] = swap;

        // Diminuímos o tamanho considerado do Heap (passando 'i') 
        // e reorganizamos a nova raiz que veio lá de trás.
        MaxHeapfy(A, i, 0);
    }
}

int main() {
    int v[] = {7, -3, 15, 0, 9, 2, 8};
    int tamanho = sizeof(v) / sizeof(v[0]);

    for(int i = 0; i < tamanho; i++) printf("%d ", v[i]);
    
    HeapSort(v, tamanho);

    for(int i = 0; i < tamanho; i++) printf("%d ", v[i]);
    printf("\n");

    return 0;
}