#include <stdio.h>
#include <stdlib.h>

#define T 3 // Grau mínimo t (Neste exemplo, máx de 5 chaves e 6 filhos por nó)

// ==========================================
// 1. ESTRUTURAS DE DADOS
// ==========================================
typedef struct BTreeNode {
    int n;                             // Número atual de chaves armazenadas no nó
    int keys[2 * T - 1];               // Vetor de chaves (capacidade máxima: 2t - 1)
    struct BTreeNode *children[2 * T]; // Vetor de ponteiros para os filhos (máximo: 2t)
    int leaf;                          // Flag booleana: 1 se for nó folha, 0 caso contrário
} BTreeNode;

typedef struct BTree {
    BTreeNode *root;
} BTree;

// ==========================================
// 2. FUNÇÃO DE BUSCA (SEARCH)
// ==========================================
// Retorna o nó onde a chave foi encontrada e salva o índice dela em 'index_found'
BTreeNode* BTreeSearch(BTreeNode *x, int key, int *index_found) {
    int i = 0;
    
    // Avança o índice enquanto a chave procurada for maior que as chaves do nó atual
    while (i < x->n && key > x->keys[i]) {
        i++;
    }
    
    // Se encontramos a chave no nó atual, retorna o ponteiro do nó
    if (i < x->n && key == x->keys[i]) {
        *index_found = i;
        return x;
    }
    
    // Se não encontramos e o nó é uma folha, a chave não existe na árvore
    if (x->leaf) {
        return NULL;
    }
    
    // Se não for folha, desce recursivamente para o filho correspondente
    return BTreeSearch(x->children[i], key, index_found);
}

// ==========================================
// 3. FUNÇÃO DE CISÃO (SPLIT CHILD)
// ==========================================
// Divide o filho 'y' (que está cheio no índice i do pai 'x') ao meio
void BTreeSplitChild(BTreeNode *x, int i, BTreeNode *y) {
    // Cria um novo nó 'z' que guardará a metade superior de 'y'
    BTreeNode *z = malloc(sizeof(BTreeNode));
    z->leaf = y->leaf;
    z->n = T - 1; // O novo nó terá o número mínimo de chaves (t - 1)
    
    // Passa as t-1 chaves finais de 'y' para 'z'
    for (int j = 0; j < T - 1; j++) {
        z->keys[j] = y->keys[j + T];
    }
    
    // Se 'y' não for folha, passa também os filhos correspondentes finais de 'y' para 'z'
    if (!y->leaf) {
        for (int j = 0; j < T; j++) {
            z->children[j] = y->children[j + T];
        }
    }
    
    // y agora foi reduzido pela metade das chaves
    y->n = T - 1;
    
    // Abre espaço no vetor de filhos do pai 'x' para receber o novo filho 'z'
    for (int j = x->n; j >= i + 1; j--) {
        x->children[j + 1] = x->children[j];
    }
    x->children[i + 1] = z; // Conecta o novo nó 'z' como filho do pai 'x'
    
    // Abre espaço no vetor de chaves do pai 'x' para a chave que vai subir de 'y'
    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }
    
    // Sobe a chave do meio de 'y' para o pai 'x'
    x->keys[i] = y->keys[T - 1];
    x->n = x->n + 1; // Pai agora tem uma chave a mais
}

// ==========================================
// 4. FUNÇÕES DE INSERÇÃO (PROATIVA / TOP-DOWN)
// ==========================================
// Função auxiliar para inserir em um nó que garantidamente possui espaço (não cheio)
void BTreeInsertNonFull(BTreeNode *x, int key) {
    int i = x->n - 1;
    
    // CASO A: Se o nó atual for uma folha, apenas insere ordenado arredando o vetor
    if (x->leaf) {
        while (i >= 0 && key < x->keys[i]) {
            x->keys[i + 1] = x->keys[i]; // Arreda as chaves para a direita
            i--;
        }
        x->keys[i + 1] = key;
        x->n = x->n + 1;
    } 
    // CASO B: Se o nó NÃO for folha, precisamos localizar o filho correto para descer
    else {
        while (i >= 0 && key < x->keys[i]) {
            i--;
        }
        i++; // Índice exato do filho onde a chave deve entrar
        
        // Estratégia proativa: Se o filho escolhido estiver cheio, faz o Split antes de descer
        if (x->children[i]->n == 2 * T - 1) {
            BTreeSplitChild(x, i, x->children[i]);
            
            // Após a cisão, a chave do meio subiu para 'x'. Verificamos qual novo lado seguir.
            if (key > x->keys[i]) {
                i++;
            }
        }
        BTreeInsertNonFull(x->children[i], key);
    }
}

// Função principal que gerencia o crescimento da árvore a partir da raiz
void BTreeInsert(BTree *tree, int key) {
    BTreeNode *r = tree->root;
    
    // Se a raiz estiver completamente cheia, a árvore cresce para cima (ganha um novo nível)
    if (r->n == 2 * T - 1) {
        BTreeNode *s = malloc(sizeof(BTreeNode)); // Nova raiz soberana
        tree->root = s;
        s->leaf = 0;
        s->n = 0;
        s->children[0] = r; // A antiga raiz vira a filha esquerda da nova raiz
        
        BTreeSplitChild(s, 0, r);   // Divide a antiga raiz ao meio através do novo pai
        BTreeInsertNonFull(s, key); // Executa a inserção normal a partir da nova raiz desobstruída
    } else {
        // Se a raiz não estava cheia, segue o fluxo recursivo normal de descida
        BTreeInsertNonFull(r, key);
    }
}

// ==========================================
// 5. PROGRAMA PRINCIPAL DE SIMULAÇÃO
// ==========================================
int main() {
    // Aloca a Árvore B e inicializa uma raiz folha vazia
    BTree *tree = malloc(sizeof(BTree));
    BTreeNode *root = malloc(sizeof(BTreeNode));
    root->n = 0;
    root->leaf = 1;
    tree->root = root;
    
    // Inserções de teste
    BTreeInsert(tree, 10);
    BTreeInsert(tree, 20);
    BTreeInsert(tree, 5);
    BTreeInsert(tree, 6);
    BTreeInsert(tree, 12); // Aqui a raiz atinge limite temporário dependendo do T
    
    // Testando a Busca
    int index_found = -1;
    BTreeNode *resultado = BTreeSearch(tree->root, 6, &index_found);
    
    if (resultado != NULL) {
        printf("Chave encontrada no indice [%d] do no localizado na memoria.\n", index_found);
    } else {
        printf("Chave nao encontrada na Arvore B.\n");
    }
    
    return 0;
}