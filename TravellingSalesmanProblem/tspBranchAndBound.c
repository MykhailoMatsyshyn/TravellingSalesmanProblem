#include "graph.h"
#include <limits.h>

#define INF INT_MAX

void reduceMatrix(double** matrix, int n, double* lowerBound) {
    *lowerBound = 0;

    // Приведення рядків
    for (int i = 0; i < n; i++) {
        double rowMin = INF;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < rowMin) {
                rowMin = matrix[i][j];
            }
        }

        // Якщо в рядку є нескінченно великі значення, то пропустити цей рядок
        if (rowMin == INF) continue;

        for (int j = 0; j < n; j++) {
            matrix[i][j] -= rowMin;
        }
        *lowerBound += rowMin;
    }

    // Приведення стовпців
    for (int j = 0; j < n; j++) {
        double colMin = INF;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < colMin) {
                colMin = matrix[i][j];
            }
        }

        // Якщо в стовпці є нескінченно великі значення, то пропустити цей стовпець
        if (colMin == INF) continue;

        for (int i = 0; i < n; i++) {
            matrix[i][j] -= colMin;
        }
        *lowerBound += colMin;
    }
}

double calculatePenalty(double** matrix, int n, int row, int col) {
    double penalty = 0;
    double minRow = INF, minCol = INF;

    // Знаходження мінімального елементу в рядку, ігноруючи поточний стовпець
    for (int j = 0; j < n; j++) {
        if (j != col && matrix[row][j] < minRow) {
            minRow = matrix[row][j];
        }
    }

    // Знаходження мінімального елементу в стовпці, ігноруючи поточний рядок
    for (int i = 0; i < n; i++) {
        if (i != row && matrix[i][col] < minCol) {
            minCol = matrix[i][col];
        }
    }

    // Штраф є сумою мінімального елементу в рядку і мінімального елементу в стовпці
    penalty = (minRow == INF ? 0 : minRow) + (minCol == INF ? 0 : minCol);

    return penalty;
}

void updateMatrix(double** matrix, int n, int row, int col, int include) {
    if (include) {
        // Включення ребра (row, col) у маршрут
        for (int i = 0; i < n; i++) {
            matrix[row][i] = INF;  // Встановлення нескінченності для всіх елементів рядка
            matrix[i][col] = INF;  // Встановлення нескінченності для всіх елементів стовпця
        }
        matrix[col][row] = INF;  // Встановлення нескінченності для симетричного елемента
    }
    else {
        // Виключення ребра (row, col) з маршруту
        matrix[row][col] = INF;  // Встановлення нескінченності для конкретного елемента
    }
}

void branchAndBoundRecursive(double** matrix, int n, int level, double currentCost, double* minCost, int* currentPath, int* bestPath, int* visited) {
    if (level == n) {
        // Перевірка на зворотнє ребро та оновлення мінімальної вартості, якщо поточний шлях кращий
        if (matrix[currentPath[level - 1]][currentPath[0]] != INF && currentCost + matrix[currentPath[level - 1]][currentPath[0]] < *minCost) {
            *minCost = currentCost + matrix[currentPath[level - 1]][currentPath[0]];
            memcpy(bestPath, currentPath, n * sizeof(int));
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && matrix[currentPath[level - 1]][i] != INF) {
            // Додавання вартості ребра
            double temp = currentCost;
            currentCost += matrix[currentPath[level - 1]][i];

            // Оновлення поточного шляху та відвідуваних міст
            visited[i] = 1;
            currentPath[level] = i;

            // Рекурсивний виклик для наступного рівня
            branchAndBoundRecursive(matrix, n, level + 1, currentCost, minCost, currentPath, bestPath, visited);

            // Відновлення поточного стану
            currentCost = temp;
            visited[i] = 0;
        }
    }
}

void branchAndBound(Graph* graph) {
    printf("\n\n ==================== \033[1;37m\033[4;37mМетод гілок і меж\033[0m ====================\n");

    int n = graph->numCities;
    double** matrix = malloc(n * sizeof(double*));
    for (int i = 0; i < n; ++i) {
        matrix[i] = malloc(n * sizeof(double));
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = graph->adjacency_matrix[i][j];
        }
    }
     
    double lowerBound = 0;
    reduceMatrix(matrix, n, &lowerBound);

    int* bestRoute = malloc(n * sizeof(int));
    int* currentRoute = malloc(n * sizeof(int));
    int* visited = calloc(n, sizeof(int));
    double bestCost = INF;

    // Ініціалізація масивів
    currentRoute[0] = 0; // Почати шлях з першого міста
    visited[0] = 1; // Відзначити перше місто як відвідане

    // Вимірювання часу
    struct timespec start, end;
    clock_t cpu_start, cpu_end;
    timespec_get(&start, TIME_UTC);
    cpu_start = clock();

    branchAndBoundRecursive(matrix, n, 1, 0, &bestCost, currentRoute, bestRoute, visited);

    cpu_end = clock();
    timespec_get(&end, TIME_UTC);

    // Виведення результату
    printf("\n МАРШРУТ:  ");
    for (int i = 0; i < n; ++i) {
        printf("%d-", bestRoute[i]);
    }
    printf("%d\n           ", bestRoute[0]);

    // Виведення назв міст
    for (int i = 0; i < n; ++i) {
        printf("%s -> ", graph->cities[bestRoute[i]].name);
    }
    printf("%s\n", graph->cities[bestRoute[0]].name);

    // Обчислення та виведення загальної відстані
    double totalDistance = 0.0;
    printf("\n ВІДСТАНЬ: ");
    for (int i = 0; i < n - 1; ++i) {
        totalDistance += matrix[bestRoute[i]][bestRoute[i + 1]];
        printf("%.2f + ", matrix[bestRoute[i]][bestRoute[i + 1]]);
    }
    totalDistance += matrix[bestRoute[n - 1]][bestRoute[0]];
    printf("%.2f = %.2f км.\n\n", matrix[bestRoute[n - 1]][bestRoute[0]], totalDistance);


    // Виведення часу виконання
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf(" [ Час виконання WALL: %.7f секунд ]\n", time_spent);

    double cpu_time_used = ((double)(cpu_end - cpu_start)) / CLOCKS_PER_SEC;
    printf(" [ Час виконання CPU: %.7f секунд ]\n\n", cpu_time_used);

    printf(" ===========================================================\n");

    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    free(bestRoute);
    free(currentRoute);
    free(visited);
}