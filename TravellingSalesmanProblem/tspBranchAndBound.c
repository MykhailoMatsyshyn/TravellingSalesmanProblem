#include "graph.h"

void tspBranchAndBoundUtil(Graph* graph, int visited[], int path[], int level, double currentWeight, double* minWeight);

void tspBranchAndBound(Graph* graph) {
    int visited[MAX_CITIES] = { 0 };
    int path[MAX_CITIES] = { 0 };
    double minWeight = INT_MAX;

    visited[0] = 1;
    path[0] = 0;

    tspBranchAndBoundUtil(graph, visited, path, 1, 0, &minWeight);

    printf("Найкоротший шлях: ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("%d-", path[i]);
    }
    printf("%d\n", path[0]); // Повернення до початкової вершини

    printf("Загальна вага: %f км\n", minWeight); // Додайте виведення загальної ваги маршруту
}

void tspBranchAndBoundUtil(Graph* graph, int visited[], int path[], int level, double currentWeight, double* minWeight) {
    if (level == graph->numCities) {
        if (graph->adjacency_matrix[path[level - 1]][path[0]] != 0) {
            double currentPathWeight = currentWeight + graph->adjacency_matrix[path[level - 1]][path[0]];
            if (currentPathWeight < *minWeight) {
                *minWeight = currentPathWeight;
            }
        }
        return;
    }

    for (int i = 0; i < graph->numCities; ++i) {
        if (!visited[i] && graph->adjacency_matrix[path[level - 1]][i] != 0) {
            visited[i] = 1;
            path[level] = i;
            tspBranchAndBoundUtil(graph, visited, path, level + 1, currentWeight + graph->adjacency_matrix[path[level - 1]][i], minWeight);
            visited[i] = 0;
        }
    }
}
