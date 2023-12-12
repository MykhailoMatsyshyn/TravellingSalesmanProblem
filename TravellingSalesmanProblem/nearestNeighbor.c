// Реалізація методу найближчого сусіда

#include "graph.h"

void nearestNeighbor(Graph* graph) {
    // 1. Початок з випадкової вершини або заданої початкової точки
    int startVertex = 0; // Вибір початкової вершини (може бути будь-якою)
    int currentVertex = startVertex;

    // Масив для відстеження відвіданих вершин
    int visited[MAX_CITIES];
    for (int i = 0; i < MAX_CITIES; ++i) {
        visited[i] = 0; // Позначаємо, що жодна вершина не відвідана
    }

    // Змінна для зберігання шляху
    int path[MAX_CITIES];
    int pathIndex = 0;

    // 2. Обхід вершин
    visited[startVertex] = 1; // Позначаємо початкову вершину як відвідану
    path[pathIndex++] = startVertex; // Додаємо початкову вершину до шляху

    while (pathIndex < graph->numCities) {
        int nearestVertex = -1; // Найближча вершина

        // Знаходження найближчої вершини
        for (int i = 0; i < graph->numCities; ++i) {
            if (!visited[i] && (nearestVertex == -1 || graph->adjacency_matrix[currentVertex][i] < graph->adjacency_matrix[currentVertex][nearestVertex])) {
                nearestVertex = i;
            }
        }

        visited[nearestVertex] = 1; // Позначаємо найближчу вершину як відвідану
        path[pathIndex++] = nearestVertex; // Додаємо найближчу вершину до шляху
        currentVertex = nearestVertex; // Переходимо до найближчої вершини
    }

    // 3. Виведення маршруту
    printf("\nМаршрут, знайдений за допомогою алгоритму найближчого сусіда:\n");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("%d ", path[i]);
    }
    printf("\n");
}