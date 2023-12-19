// Реалізація методу найближчого сусіда

#include "graph.h"

void nearestNeighbor(Graph* graph) {
    struct timespec begin;
    struct timespec end;
    clock_t cpu_start, cpu_end;
    double cpu_time_used;

    timespec_get(&begin, TIME_UTC);
    cpu_start = clock();

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
    
    // Додавання зворотнього шляху від останньої вершини до початкової
    totalDistance += graph->adjacency_matrix[path[graph->numCities - 1]][startVertex];
    path[pathIndex++] = startVertex;

    cpu_end = clock();

    timespec_get(&end, TIME_UTC);

    printf("\n\n ================  \033[1;37m\033[4;37mМетод найближчого сусіда\033[0m ================\n");

    // 3. Виведення маршруту
    printf("\n МАРШРУТ:  ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("%d-", path[i]);
    }
    printf("%d\n           ", startVertex);

    for (int i = 0; i < graph->numCities; ++i) {
        printf("%s -> ", graph->cities[path[i]].name);
    }
    printf("%s\n", graph->cities[startVertex].name);

    // 4. Виведення загальної відстані
    printf("\n ВІДСТАНЬ: ");
    for (int i = 0; i < graph->numCities - 1; ++i) {
        printf("%.2f + ", graph->adjacency_matrix[path[i]][path[i + 1]]);
    }
    printf("%.2f = %.2f км.\n\n", 
           graph->adjacency_matrix[path[graph->numCities - 1]][startVertex], totalDistance);

    double time_spent = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    printf(" [ Час виконання WALL: %.7f секунд ]\n", time_spent);

    cpu_time_used = ((double)(cpu_end - cpu_start)) / CLOCKS_PER_SEC;
    printf(" [ Час виконання CPU: %.7f секунд ]\n\n", cpu_time_used);
    printf(" ===========================================================\n");
}