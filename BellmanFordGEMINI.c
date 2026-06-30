#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definição de infinito para inicializar as distâncias
#define INF INT_MAX

// ==========================================
// 1. ESTRUTURAS DE DADOS
// ==========================================
// Representa uma aresta direcionada do grafo
typedef struct Edge {
    int src;    // Vértice de origem
    int dest;   // Vértice de destino
    int weight; // Peso da aresta (pode ser negativo)
} Edge;

// Representa o grafo completo
typedef struct Graph {
    int V;          // Número de vértices
    int E;          // Número de arestas
    Edge *edges;    // Vetor de arestas
} Graph;

// Função auxiliar para criar um grafo
Graph* createGraph(int V, int E) {
    Graph *graph = malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = malloc(E * sizeof(Edge));
    return graph;
}

// ==========================================
// 2. ALGORITMO DE BELLMAN-FORD
// ==========================================
void BellmanFord(Graph *graph, int source) {
    int V = graph->V;
    int E = graph->E;
    int *dist = malloc(V * sizeof(int));

    // Passo 1: Inicializa as distâncias do vértice de origem para todos os outros como Infinito
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
    }
    dist[source] = 0; // A distância da origem para ela mesma é zero

    // Passo 2: Relaxa todas as arestas do grafo (V - 1) vezes
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            
            // Se o vértice de origem já foi alcançado e encontramos um caminho mais curto para 'v'
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight; // Relaxação da aresta
            }
        }
    }

    // Passo 3: Verifica se existem ciclos de peso negativo.
    // Se conseguirmos relaxar qualquer aresta mais uma vez, existe um ciclo negativo.
    int possui_ciclo_negativo = 0;
    for (int j = 0; j < E; j++) {
        int u = graph->edges[j].src;
        int v = graph->edges[j].dest;
        int weight = graph->edges[j].weight;
        
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            printf("Aviso: O grafo contem um ciclo de peso negativo alcançavel a partir da origem!\n");
            possui_ciclo_negativo = 1;
            break;
        }
    }

    // Passo 4: Se não houver ciclo negativo, imprime o resultado das distâncias
    if (!possui_ciclo_negativo) {
        printf("Vertice \t Distancia da Origem (%d)\n", source);
        for (int i = 0; i < V; i++) {
            if (dist[i] == INF) {
                printf("%d \t\t INF\n", i);
            } else {
                printf("%d \t\t %d\n", i, dist[i]);
            }
        }
    }

    free(dist);
}

// ==========================================
// 3. PROGRAMA PRINCIPAL (TESTE)
// ==========================================
int main() {
    int V = 5; // Número de vértices (0 a 4)
    int E = 8; // Número de arestas
    Graph *graph = createGraph(V, E);

    // Adiciona as arestas do grafo de teste
    // Aresta 0 -> 1 (Peso -1)
    graph->edges[0].src = 0; graph->edges[0].dest = 1; graph->edges[0].weight = -1;
    
    // Aresta 0 -> 2 (Peso 4)
    graph->edges[1].src = 0; graph->edges[1].dest = 2; graph->edges[1].weight = 4;
    
    // Aresta 1 -> 2 (Peso 3)
    graph->edges[2].src = 1; graph->edges[2].dest = 2; graph->edges[2].weight = 3;
    
    // Aresta 1 -> 3 (Peso 2)
    graph->edges[3].src = 1; graph->edges[3].dest = 3; graph->edges[3].weight = 2;
    
    // Aresta 1 -> 4 (Peso 2)
    graph->edges[4].src = 1; graph->edges[4].dest = 4; graph->edges[4].weight = 2;
    
    // Aresta 3 -> 2 (Peso 5)
    graph->edges[5].src = 3; graph->edges[5].dest = 2; graph->edges[5].weight = 5;
    
    // Aresta 3 -> 1 (Peso 1)
    graph->edges[6].src = 3; graph->edges[6].dest = 1; graph->edges[6].weight = 1;
    
    // Aresta 4 -> 3 (Peso -3) -> Repare o peso negativo aqui
    graph->edges[7].src = 4; graph->edges[7].dest = 3; graph->edges[7].weight = -3;

    // Executa o algoritmo a partir do vértice 0
    BellmanFord(graph, 0);

    // Libera a memória do grafo
    free(graph->edges);
    free(graph);

    return 0;
}