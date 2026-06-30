#include <stdio.h>
#include <stdlib.h>

// ==========================================
// 1. ESTRUTURAS DE DADOS
// ==========================================

typedef struct Node {
    int key;
    struct Node *prox;
    struct Node *ant;
} Node;

typedef struct List {
    int ref; // Usado aqui como contador de elementos no bucket
    Node *head;
    Node *tail;
} List;

typedef struct HashTable {
    int capacity;
    int total_items;
    List *buckets;
} HashTable;

// ==========================================
// 2. FUNÇÕES DE INICIALIZAÇÃO
// ==========================================

// Função Hash: Calcula o índice do vetor (Módulo)
int hashFunction(int key, int capacity) {
    return abs(key) % capacity;
}

// Cria e inicializa a tabela na memória
HashTable* createTable(int capacity) {
    HashTable *T = malloc(sizeof(HashTable));
    T->capacity = capacity;
    T->total_items = 0;
    T->buckets = malloc(capacity * sizeof(List));
    
    for (int i = 0; i < capacity; i++) {
        T->buckets[i].head = NULL;
        T->buckets[i].tail = NULL;
        T->buckets[i].ref = 0;
    }
    return T;
}

// ==========================================
// 3. FUNÇÃO DE INSERÇÃO (ORDENADA)
// ==========================================
void HashTableInsert(HashTable *T, int key) {
    int index = hashFunction(key, T->capacity);
    List *L = &(T->buckets[index]); // Ponteiro atalho para o bucket
    
    Node *novo = malloc(sizeof(Node));
    if (novo == NULL) return;
    novo->key = key;
    novo->prox = NULL;
    novo->ant = NULL;

    // CASO 1: Lista vazia OU elemento menor que o primeiro (Insere no Início)
    if (L->head == NULL || key < L->head->key) {
        novo->prox = L->head;
        if (L->head != NULL) {
            L->head->ant = novo;
        } else {
            L->tail = novo; // Se estava vazia, novo também é o fim
        }
        L->head = novo;
    } 
    // CASO 2: Inserção no Meio ou no Fim
    else {
        Node *atual = L->head;
        // Avança até encontrar o ponto correto de inserção
        while (atual->prox != NULL && atual->prox->key < key) {
            atual = atual->prox;
        }
        
        novo->prox = atual->prox;
        novo->ant = atual;
        
        if (atual->prox != NULL) {
            // No Meio: ajusta o ponteiro de retorno do nó da frente
            atual->prox->ant = novo;
        } else {
            // No Fim: o novo nó passa a ser a cauda (tail)
            L->tail = novo;
        }
        atual->prox = novo;
    }
    
    L->ref++;         // Incrementa itens no bucket
    T->total_items++; // Incrementa itens na tabela global
}

// ==========================================
// 4. FUNÇÃO DE BUSCA
// ==========================================
// Como a lista está ordenada, podemos parar a busca antes se acharmos 
// uma chave maior do que a procurada. Isso economiza tempo em pior caso.
Node* HashTableSearch(HashTable *T, int key) {
    int index = hashFunction(key, T->capacity);
    Node *atual = T->buckets[index].head;
    
    while (atual != NULL) {
        if (atual->key == key) {
            return atual; // Encontrou! Retorna o ponteiro do nó
        }
        if (atual->key > key) {
            break; // Otimização: se a chave atual já é maior, a procurada não existe adiante
        }
        atual = atual->prox;
    }
    return NULL; // Não encontrou
}

// ==========================================
// 5. FUNÇÃO DE REMOÇÃO
// ==========================================
int HashTableRemove(HashTable *T, int key) {
    int index = hashFunction(key, T->capacity);
    List *L = &(T->buckets[index]);
    
    // Primeiro, localiza o nó usando nossa lógica de busca
    Node *alvo = HashTableSearch(T, key);
    
    if (alvo == NULL) {
        return 0; // Chave não encontrada, nada a remover
    }
    
    // Ajuste do ponteiro ANTERIOR (ou da Cabeça)
    if (alvo->ant != NULL) {
        alvo->ant->prox = alvo->prox;
    } else {
        L->head = alvo->prox; // O alvo era o primeiro nó (head)
    }
    
    // Ajuste do ponteiro PRÓXIMO (ou da Cauda)
    if (alvo->prox != NULL) {
        alvo->prox->ant = alvo->ant;
    } else {
        L->tail = alvo->ant; // O alvo era o último nó (tail)
    }
    
    // Libera a memória do nó deletado
    free(alvo);
    
    // Atualiza contadores
    L->ref--;
    T->total_items--;
    
    return 1; // Remoção concluída com sucesso
}

// ==========================================
// 6. PROGRAMA PRINCIPAL (TESTE)
// ==========================================
int main() {
    HashTable *T = createTable(5); // Cria tabela com capacidade 5
    
    HashTableInsert(T, 12);
    HashTableInsert(T, 22); // Vai colidir no bucket 2 (22 % 5 = 2)
    HashTableInsert(T, 2);  // Vai colidir no bucket 2 (2 % 5 = 2) e ficar na frente devido à ordenação
    
    Node *busca = HashTableSearch(T, 22);
    if(busca != NULL) printf("Achou a chave: %d\n", busca->key);
    
    if(HashTableRemove(T, 22)) {
        printf("Chave 22 removida com sucesso!\n");
    }
    
    return 0;
}