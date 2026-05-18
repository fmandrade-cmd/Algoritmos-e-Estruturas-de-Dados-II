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



int main() {

    return 0;
}