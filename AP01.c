/*
    Autor: Fábio Miguel de Andrade
    Data: 16-05-2026

    Estudos P1

    AP01 - Aplicação de algoritmo quadrático para ordenação de uma
           Lista Duplamente Encadeada
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int id;
    struct no *ant;
    struct no *prox;
}No;

typedef struct {
    int NEP;
    No *head;
    No *tail;
}List;

No* CreateNode(int id){
    No *novo = malloc(sizeof(No));
    novo->ant = NULL;
    novo->prox = NULL;
    novo->id = id;

    return novo;
}

List* InserirNoOrdenado(No *new, int size){
    //Cria a estrutura de lista duplamente encadeada
    List *lista = malloc(size * sizeof(No));
    lista->NEP = 0;

    //Caso seja a primeira inserção da lista
    if(lista->head == NULL && lista->tail == NULL){
        lista->head = new;
        lista->tail = new;
    }

    //Inserção no início
    if(new->id <= lista->head->id){
        new->prox = lista->head;
        lista->head->ant = new;
        lista->head = new;
    }

    //Inserção no final
    if(new->id >= lista->tail->id){
        lista->tail->prox = new;
        new->ant = lista->tail;
        lista->tail = new;
    }

    //Inserção no meio pela técnica da distancia
    int distHead = abs(new->id - lista->head->id);
    int distTail = abs(new->id - lista->tail->id);

    if(distHead <= distTail){

        No *aux = lista->head;

        while(new->id >= aux->id){
            aux = aux->prox;
            (lista->NEP)++;
        }
        aux->ant->prox = new;
        new->ant = aux->ant;
        new->prox = aux;
        aux->ant = new;
    }

    if(distHead > distTail){
        No *aux = lista->tail;

        while(new->id < aux->id){
            aux = aux->ant;
            (lista->NEP)++;
        }
        aux->prox->ant = new;
        new->prox = aux->prox;
        aux->prox = new;
        new->ant = aux;
    }
    
    return lista;
}

void printList(List *lista){

    No *start = lista->head;
    while (start != NULL){
        printf("%d", &start->id);
        start = start->prox;
    }
}

int main() {

    int exec, id, NEP;
    No *head = NULL;
    No *tail = NULL;

    scanf("%d", &exec);

    //Entrada de Dados
    for(int i = 0; i < exec; i++){
        scanf("%d", &id);
        InserirNoOrdenado(CreateNode(id), exec);
    }

    //Saída de Dados
    printList(InserirNoOrdenado(CreateNode(id), exec));

    return 0;
}