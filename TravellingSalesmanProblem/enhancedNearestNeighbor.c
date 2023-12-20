// Реалізація вдосконаленого методу найближчого сусіда
#include "graph.h"
#include <limits.h>

clock_t cpu_start, cpu_end, suspended_time;
double cpu_time_used;

struct timespec wall_start, wall_end;
struct timespec wall_start1, wall_end1;
struct timespec wall_start2, wall_end2;
struct timespec wall_start3, wall_end3;
double time_spent;

int* findBestPath(Graph* graph, int startVertex) {
    timespec_get(&wall_start3, TIME_UTC);
    // Отримання пам'яті для масиву шляху
    int* path = malloc((MAX_CITIES + 1) * sizeof(int));
    if (path == NULL) {
        printf("Помилка виділення пам'яті\n");
        return NULL;
    }
    timespec_get(&wall_end3, TIME_UTC);
    time_spent -= (wall_end3.tv_sec - wall_start3.tv_sec) + (wall_end3.tv_nsec - wall_start3.tv_nsec) / 1000000000.0;

    int currentVertex = startVertex;
    int visited[MAX_CITIES];
    int pathIndex = 0;

    for (int i = 0; i < MAX_CITIES; ++i) {
        visited[i] = 0;
    }

    visited[startVertex] = 1;
    path[pathIndex++] = startVertex;

    while (pathIndex < graph->numCities) {
        int nearestVertex = -1;
        double minDistance = -1;

        for (int i = 0; i < graph->numCities; ++i) {
            if (!visited[i] && (nearestVertex == -1 || graph->adjacency_matrix[currentVertex][i] < minDistance)) {
                nearestVertex = i;
                minDistance = graph->adjacency_matrix[currentVertex][i];
            }
        }

        visited[nearestVertex] = 1;
        path[pathIndex++] = nearestVertex;
        currentVertex = nearestVertex;
    }

    // Додаємо початкову вершину в кінець шляху
    path[pathIndex] = startVertex;

    timespec_get(&wall_start2, TIME_UTC);
    cpu_end = clock();
    suspended_time += cpu_end - cpu_start;

    //if (graph->numCities <= N_TO_PRINT) {
    //    // Вивід шляху
    //    printf("\n Шлях: ");
    //    for (int i = 0; i <= graph->numCities; ++i) {
    //        printf("%d-", path[i]);
    //    }
    //    printf("\b перетворюється в ");
    //}

    cpu_start = clock();
    timespec_get(&wall_end2, TIME_UTC);
    time_spent -= (wall_end2.tv_sec - wall_start2.tv_sec) + (wall_end2.tv_nsec - wall_start2.tv_nsec) / 1000000000.0;

    // Повернення масиву шляху
    return path;
}


void enhancedNearestNeighbor(Graph* graph) {
    printf("\n\n =========  \033[1;37m\033[4;37mУдосконалений метод найближчого сусіда\033[0m =========\n");

    cpu_start = clock();
    timespec_get(&wall_start, TIME_UTC);

    double minDistance = INT_MAX;
    int bestPath[MAX_CITIES];

    // Цикл для всіх вершин крім 0
    for (int i = 1; i < graph->numCities; ++i) {
        int* path = findBestPath(graph, i);
        if (path == NULL) {
            printf("Помилка у пошуку шляху\n");
            return;
        }

        // Знайдення позиції 0 у знайденому шляху
        int startIndex = 0;
        for (int j = 0; j < graph->numCities; ++j) {
            if (path[j] == 0) {
                startIndex = j;
                break;
            }
        }

        // Перетворення шляху
        int transformedPath[MAX_CITIES];
        int index = 0;
        for (int j = startIndex; j < graph->numCities; ++j) {
            transformedPath[index++] = path[j];
        }
        for (int j = 0; j < startIndex; ++j) {
            transformedPath[index++] = path[j];
        }

        // Переконання, що шлях закінчується початковою вершиною
        transformedPath[index] = 0;

        timespec_get(&wall_start1, TIME_UTC);
        cpu_end = clock();
        suspended_time += cpu_end - cpu_start;

        //if (graph->numCities <= N_TO_PRINT) {
        //    // Вивід перетвореного шляху
        //    for (int j = 0; j < graph->numCities; ++j) {
        //        printf("%d-", transformedPath[j]);
        //    }
        //    printf("%d\n", transformedPath[graph->numCities]);
        //}

        cpu_start = clock();
        timespec_get(&wall_end1, TIME_UTC);
        time_spent -= (wall_end1.tv_sec - wall_start1.tv_sec) + (wall_end1.tv_nsec - wall_start1.tv_nsec) / 1000000000.0;

        // Підрахунок відстані для перетвореного шляху
        double totalDistance = 0;
        for (int j = 0; j < graph->numCities; ++j) {
            int city1 = transformedPath[j];
            int city2 = transformedPath[j + 1];
            totalDistance += graph->adjacency_matrix[city1][city2];
        }

        // Порівняння та збереження найкращого шляху
        if (totalDistance < minDistance) {
            minDistance = totalDistance;
            for (int j = 0; j < graph->numCities + 1; ++j) {
                bestPath[j] = transformedPath[j];
            }
        }

        // Звільнення пам'яті
        free(path);
    }

    timespec_get(&wall_end, TIME_UTC);
    cpu_end = clock();
    suspended_time += cpu_end - cpu_start;

    // Вивід найкоротшого шляху та його відстані
    printf("\n МАРШРУТ:  ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("%d-", bestPath[i]);
    }
    printf("%d\n           ", bestPath[graph->numCities]);

    for (int i = 0; i < graph->numCities; ++i) {
        printf("%s -> ", graph->cities[bestPath[i]].name);
    }
    printf("%s\n", graph->cities[bestPath[graph->numCities]].name);

    printf("\n ВІДСТАНЬ: ");
    for (int i = 0; i < graph->numCities-1; ++i) {
        printf("%.2f + ", graph->adjacency_matrix[bestPath[i]][bestPath[i + 1]]);
    }
    printf("%.2f = %.2f км.\n\n", graph->adjacency_matrix[bestPath[graph->numCities - 1]][bestPath[0]], minDistance);


    time_spent += (wall_end.tv_sec - wall_start.tv_sec) + (wall_end.tv_nsec - wall_start.tv_nsec) / 1000000000.0;
    printf(" [ Час виконання WALL: %.7f секунд ]\n", time_spent);

    cpu_time_used = ((double)(cpu_end - cpu_start)) / CLOCKS_PER_SEC;
    printf(" [ Час виконання CPU: %.7f секунд ]\n\n", cpu_time_used);
    printf(" ===========================================================\n");
}