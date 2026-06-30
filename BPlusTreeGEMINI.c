#include <stdio.h>
#include <stdlib.h>

#define T 3 // Grau mínimo t (Define a capacidade dos nós internos e folhas)

// ==========================================
// 1. ESTRUTURAS DE DADOS
// ==========================================
typedef struct BPlusNode {
    int n;                             // Número atual de chaves no nó
    int keys[2 * T - 1];               // Vetor de chaves
    int leaf;                          // 1 se for nó folha, 0 se for interno
    
    // UNIÃO: Se for interno, usa o vetor de filhos. Se for folha, aponta para a próxima folha.
    union {
        struct BPlusNode *children[2 * T]; // Ponteiros para nós filhos (Nós Internos)
        struct BPlusNode *next;            // Ponteiro para a próxima folha (Nós Folha)
    } pointer;
} BPlusNode;

typedef struct BPlusTree {
    BPlusNode *root;
} BPlusTree;

// ==========================================
// 2. FUNÇÃO DE BUSCA (SEARCH)
// ==========================================
// Na Árvore B+, a busca SEMPRE vai até a folha, mesmo se achar a chave no caminho.
BPlusNode* BPlusTreeSearch(BPlusNode *x, int key, int *index_found) {
    int i = 0;
    while (i < x->n && key >= x->keys[i]) {
        i++;
    }
    
    // Se for folha, fazemos a validação final se a chave existe
    if (x->leaf) {
        // Como o 'i' parou uma posição à frente no laço acima, checamos o índice anterior
        if (i > 0 && x->keys[i - 1] == key) {
            *index_found = i - 1;
            return x; // Retorna a folha onde o dado real está
        }
        return NULL; // Não encontrou nas folhas
    }
    
    // Se for nó interno, apenas desce no ponteiro correspondente
    return BPlusTreeSearch(x->pointer.children[i], key, index_found);
}

// ==========================================
// 3. FUNÇÃO DE CISÃO (SPLIT CHILD)
// ==========================================
// Divide um nó filho 'y' que está cheio. A lógica muda ligeiramente se 'y' for folha.
void BPlusTreeSplitChild(BPlusNode *x, int i, BPlusNode *y) {
    BPlusNode *z = malloc(sizeof(BPlusNode));
    z->leaf = y->leaf;
    
    if (y->leaf) {
        // --- SE O FILHO FOR FOLHA ---
        // Na folha, a chave do meio SOBE mas também FICA na folha da direita (z)
        z->n = T; 
        for (int j = 0; j < T; j++) {
            z->keys[j] = y->keys[j + T - 1];
        }
        y->n = T - 1;
        
        // Ajusta a lista encadeada das folhas
        z->pointer.next = y->pointer.next;
        y->pointer.next = z;
    } else {
        // --- SE O FILHO FOR NÓ INTERNO ---
        // No nó interno, a chave do meio SOBE e desaparece do nível inferior (igual à Árvore B)
        z->n = T - 1;
        for (int j = 0; j < T - 1; j++) {
            z->keys[j] = y->keys[j + T];
        }
        for (int j = 0; j < T; j++) {
            z->pointer.children[j] = y->pointer.children[j + T];
        }
        y->n = T - 1;
    }
    
    // Desloca os filhos do pai 'x' para abrir espaço para 'z'
    for (int j = x->n; j >= i + 1; j--) {
        x->pointer.children[j + 1] = x->pointer.children[j];
    }
    x->pointer.children[i + 1] = z;
    
    // Desloca as chaves do pai 'x' para abrir espaço para a chave que vai subir
    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }
    
    // Sobe a chave correta para o pai
    if (y->leaf) {
        x->keys[i] = z->keys[0]; // Cópia da primeira chave da nova folha
    } else {
        x->keys[i] = y->keys[T - 1]; // Elemento do meio do nó interno
    }
    x->n = x->n + 1;
}

// ==========================================
// 4. FUNÇÕES DE INSERÇÃO (TOP-DOWN)
// ==========================================
void BPlusTreeInsertNonFull(BPlusNode *x, int key) {
    int i = x->n - 1;
    
    if (x->leaf) {
        // Insere ordenado diretamente na folha
        while (i >= 0 && key < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = key;
        x->n = x->n + 1;
    } else {
        // Localiza qual filho descer
        while (i >= 0 && key < x->keys[i]) {
            i--;
        }
        i++;
        
        // Se o filho estiver cheio, realiza o Split proativo antes de descer
        if (x->pointer.children[i]->n == 2 * T - 1) {
            BPlusTreeSplitChild(x, i, x->pointer.children[i]);
            if (key >= x->keys[i]) {
                i++;
            }
        }
        BPlusTreeInsertNonFull(x->pointer.children[i], key);
    }
}

void BPlusTreeInsert(BPlusTree *tree, int key) {
    BPlusNode *r = tree->root;
    
    if (r->n == 2 * T - 1) {
        BPlusNode *s = malloc(sizeof(BPlusNode)); // Nova raiz
        tree->root = s;
        s->leaf = 0;
        s->n = 0;
        s->pointer.children[0] = r;
        
        BPlusTreeSplitChild(s, 0, r);
        BPlusTreeInsertNonFull(s, key);
    } else {
        BPlusTreeInsertNonFull(r, key);
    }
}

// ==========================================
// 5. PROGRAMA PRINCIPAL
// ==========================================
int main() {
    BPlusTree *tree = malloc(sizeof(BPlusTree));
    BPlusNode *root = malloc(sizeof(BPlusNode));
    root->n = 0;
    root->leaf = 1;
    root->pointer.next = NULL;
    tree->root = root;
    
    BPlusTreeInsert(tree, 15);
    BPlusTreeInsert(tree, 25);
    BPlusTreeInsert(tree, 5);
    BPlusTreeInsert(tree, 35);
    
    int index = -1;
    BPlusNode *res = BPlusTreeSearch(tree->root, 25, &index);
    
    if (res != NULL) {
        printf("Chave encontrada na folha! Valor: %d no indice %d\n", res->keys[index], index);
    } else {
        printf("Chave nao encontrada.\n");
    }
    
    return 0;
}