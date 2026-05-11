/*
    Nome: Fábio Miguel de Andrade
    Data: 11-05-2026

    Implementação de uma Árvore Binária de Busca (ABB)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node *left;
    struct node *rigth;
}Arvore;

Arvore* TREE_INSERTION(Arvore *raiz, int val){
    if(raiz == NULL){
        Arvore *folha = malloc(sizeof(Arvore));
        folha->left = NULL;
        folha->rigth = NULL;
        folha->val = val;
        return folha;
    }

    if(val > raiz->val){
        raiz->rigth = TREE_INSERTION((raiz->rigth), val);
    }else{
        raiz->left = TREE_INSERTION((raiz->left), val);
    }
    return raiz;

}

int TREE_SEARCH(Arvore *raiz, int ref){
    if(raiz == NULL){
        return -1; 
    }

    // Caso 2: Valor encontrado! Aqui começa a contagem.
    if(raiz->val == ref){
        return 0; 
    }
    int cont;
    if(ref < raiz->val){
        cont = TREE_SEARCH(raiz->left, ref);
    }else{
        cont = TREE_SEARCH(raiz->rigth, ref);
    }
    if(cont != -1) {
        return cont + 1;
    }

    // Se não foi encontrado, continuamos passando o -1 para cima
    return -1;
}

int main() {
    Arvore *raiz = NULL;
    int contador = 0;

    /*
    
        raiz = TREE_INSERTION(raiz, 50);
        raiz = TREE_INSERTION(raiz, 10);
        raiz = TREE_INSERTION(raiz, 35);
        raiz = TREE_INSERTION(raiz, 72);
        raiz = TREE_INSERTION(raiz, 7);
        raiz = TREE_INSERTION(raiz, 99);
        raiz = TREE_INSERTION(raiz, 18);
        
        contador = TREE_SEARCH(raiz, 7);

        printf("%d", contador);
    */
   
}