/*
    Exercicio de Implemetacao do Algoritmo de Arvores Rubro-Negra
    Nome: Fábio Miguel de Andrade
    Data: 28-06-2026

    Estudos para a P2;
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key; //Valor guardado no No
    int color; //0 - Black; 1 - Red
    struct Node *parent; //Pai
    struct Node *left; //Filho esquerdo
    struct Node *right; //Filho Direito
}Node;

typedef struct RedBlackTree{
    int size;
    struct Node *root;
}RedBlackTree;


void LeftRotate(RedBlackTree *T, Node *x){
    Node *y = x->right;
    x->right = y->left;
    if(y->left != NULL){
        y->left->parent = x; 
    }
    y->parent = x->parent;
    if(x->parent == NULL){
        T->root = y;
    }else if(x == x->parent->left){
        x->parent->left = y;
    }else{
        x->parent->right = y; 
    }
    y->left = x;
    x->parent = y;
}

void RightRotation(RedBlackTree *T, Node *y){
    Node *z = y->left;
    y->left = z->right;
    if(z->right != NULL){
        z->right->parent = y;
    }
    z->parent = y->parent;
    if(y->parent == NULL){
        T->root = z;
    }else if(y == y->parent->right){
        y->parent->right = z;
    }else{
        y->parent->left = z;
    }
    z->right = y;
    y->parent = z;
}

void RedBlackInsertFixup(RedBlackTree *T, Node *z){
    while(z != T->root && z->parent->color == 1){
        if(z->parent == z->parent->parent->left){
            Node *y = z->parent->parent->right;
            if(y->color == 1){
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            }else if(z == z->parent->right){
                z = z->parent;
                LeftRotate(T, z);
            }
            z->parent->color = 0;
            z->parent->parent->color = 1;
            RightRotation(T, z);
        }
    }
    T->root->color = 0;
}

void RedBlackInsert(RedBlackTree *T, Node *k){
    Node *y = NULL;
    Node *x = T->root;
    while(x != NULL){
        y = x;
        if(k->key < x->key){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    k->parent = y;
    if(y == NULL){
        T->root = k;
    }else if(k->key < y->key){
        y->left = k;
    }else{
        y->right = k;
    }
    k->left = NULL;
    k->right = NULL;
    k->color = 1;
    RedBlackInsertFixup(T, k);
}

int main() {


    return 0;
}