// Реалізація методу найближчого сусіда

#include "graph.h"

void nearestNeighbor(Graph* graph) 
{
    // 1. Початок з випадкової вершини або заданої початкової точки
    int startVertex = 0; // Вибір початкової вершини (може бути будь-якою)
    int currentVertex = startVertex;

    // Масив для відстеження відвіданих вершин
    int visited[MAX_CITIES];
    for (int i = 0; i < MAX_CITIES; ++i) {
        visited[i] = 0; // Позначаємо, що жодна вершина не відвідана
    }

    // Змінна для зберігання шляху та загальної відстані
    int path[MAX_CITIES];
    int pathIndex = 0;
    double totalDistance = 0.0;

    // 2. Обхід вершин
    visited[startVertex] = 1; // Позначаємо початкову вершину як відвідану
    path[pathIndex++] = startVertex; // Додаємо початкову вершину до шляху

    while (pathIndex < graph->numCities) {
        int nearestVertex = -1; // Найближча вершина
        double minDistance = -1; // Мінімальна відстань

        // Знаходження найближчої вершини
        for (int i = 0; i < graph->numCities; ++i) {
            if (!visited[i] && (nearestVertex == -1 || graph->adjacency_matrix[currentVertex][i] < minDistance)) {
                nearestVertex = i;
                minDistance = graph->adjacency_matrix[currentVertex][i];
            }
        }

        visited[nearestVertex] = 1; // Позначаємо найближчу вершину як відвідану
        path[pathIndex++] = nearestVertex; // Додаємо найближчу вершину до шляху
        totalDistance += minDistance; // Додаємо відстань до загальної відстані
        currentVertex = nearestVertex; // Переходимо до найближчої вершини
    }

    printf("\n\n================\n");

    // 3. Виведення маршруту
    printf("\n У результаті знайдений маршрут ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("%d-", path[i]);
    }

    // 4. Виведення загальної відстані
    printf("\b, який становить відстань:\n ");
    for (int i = 0; i < graph->numCities - 1; ++i) {
        printf("%.2f + ", graph->adjacency_matrix[path[i]][path[i + 1]]);
    }
    printf("\b\b= %.2f кілометрів.\n\n================\n\n", totalDistance);
}