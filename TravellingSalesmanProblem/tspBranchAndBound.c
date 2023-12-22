#include "graph.h"
#include <limits.h>

#define INF INT_MAX

void reduceMatrix(double** matrix, int n, double* lowerBound) {
    *lowerBound = 0;

    // ���������� �����
    for (int i = 0; i < n; i++) {
        double rowMin = INF;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < rowMin) {
                rowMin = matrix[i][j];
            }
        }

        // ���� � ����� � ���������� ����� ��������, �� ���������� ��� �����
        if (rowMin == INF) continue;

        for (int j = 0; j < n; j++) {
            matrix[i][j] -= rowMin;
        }
        *lowerBound += rowMin;
    }

    // ���������� ��������
    for (int j = 0; j < n; j++) {
        double colMin = INF;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < colMin) {
                colMin = matrix[i][j];
            }
        }

        // ���� � ������� � ���������� ����� ��������, �� ���������� ��� ��������
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

    // ����������� ���������� �������� � �����, ��������� �������� ��������
    for (int j = 0; j < n; j++) {
        if (j != col && matrix[row][j] < minRow) {
            minRow = matrix[row][j];
        }
    }

    // ����������� ���������� �������� � �������, ��������� �������� �����
    for (int i = 0; i < n; i++) {
        if (i != row && matrix[i][col] < minCol) {
            minCol = matrix[i][col];
        }
    }

    // ����� � ����� ���������� �������� � ����� � ���������� �������� � �������
    penalty = (minRow == INF ? 0 : minRow) + (minCol == INF ? 0 : minCol);

    return penalty;
}

void updateMatrix(double** matrix, int n, int row, int col, int include) {
    if (include) {
        // ��������� ����� (row, col) � �������
        for (int i = 0; i < n; i++) {
            matrix[row][i] = INF;  // ������������ ������������ ��� ��� �������� �����
            matrix[i][col] = INF;  // ������������ ������������ ��� ��� �������� �������
        }
        matrix[col][row] = INF;  // ������������ ������������ ��� ������������ ��������
    }
    else {
        // ���������� ����� (row, col) � ��������
        matrix[row][col] = INF;  // ������������ ������������ ��� ����������� ��������
    }
}

void branchAndBoundRecursive(double** matrix, int n, int level, double currentCost, double* minCost, int* currentPath, int* bestPath, int* visited) {
    if (level == n) {
        // �������� �� ������� ����� �� ��������� �������� �������, ���� �������� ���� ������
        if (matrix[currentPath[level - 1]][currentPath[0]] != INF && currentCost + matrix[currentPath[level - 1]][currentPath[0]] < *minCost) {
            *minCost = currentCost + matrix[currentPath[level - 1]][currentPath[0]];
            memcpy(bestPath, currentPath, n * sizeof(int));
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && matrix[currentPath[level - 1]][i] != INF) {
            // ��������� ������� �����
            double temp = currentCost;
            currentCost += matrix[currentPath[level - 1]][i];

            // ��������� ��������� ����� �� ���������� ���
            visited[i] = 1;
            currentPath[level] = i;

            // ����������� ������ ��� ���������� ����
            branchAndBoundRecursive(matrix, n, level + 1, currentCost, minCost, currentPath, bestPath, visited);

            // ³��������� ��������� �����
            currentCost = temp;
            visited[i] = 0;
        }
    }
}

void branchAndBound(Graph* graph) {
    printf("\n\n ==================== \033[1;37m\033[4;37m����� ���� � ���\033[0m ====================\n");

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

    // ����������� ������
    currentRoute[0] = 0; // ������ ���� � ������� ����
    visited[0] = 1; // ³�������� ����� ���� �� �������

    // ���������� ����
    struct timespec start, end;
    clock_t cpu_start, cpu_end;
    timespec_get(&start, TIME_UTC);
    cpu_start = clock();

    branchAndBoundRecursive(matrix, n, 1, 0, &bestCost, currentRoute, bestRoute, visited);

    cpu_end = clock();
    timespec_get(&end, TIME_UTC);

    // ��������� ����������
    printf("\n �������:  ");
    for (int i = 0; i < n; ++i) {
        printf("%d-", bestRoute[i]);
    }
    printf("%d\n           ", bestRoute[0]);

    // ��������� ���� ���
    for (int i = 0; i < n; ++i) {
        printf("%s -> ", graph->cities[bestRoute[i]].name);
    }
    printf("%s\n", graph->cities[bestRoute[0]].name);

    // ���������� �� ��������� �������� ������
    double totalDistance = 0.0;
    printf("\n ²������: ");
    for (int i = 0; i < n - 1; ++i) {
        totalDistance += matrix[bestRoute[i]][bestRoute[i + 1]];
        printf("%.2f + ", matrix[bestRoute[i]][bestRoute[i + 1]]);
    }
    totalDistance += matrix[bestRoute[n - 1]][bestRoute[0]];
    printf("%.2f = %.2f ��.\n\n", matrix[bestRoute[n - 1]][bestRoute[0]], totalDistance);


    // ��������� ���� ���������
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf(" [ ��� ��������� WALL: %.7f ������ ]\n", time_spent);

    double cpu_time_used = ((double)(cpu_end - cpu_start)) / CLOCKS_PER_SEC;
    printf(" [ ��� ��������� CPU: %.7f ������ ]\n\n", cpu_time_used);

    printf(" ===========================================================\n");

    for (int i = 0; i < n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    free(bestRoute);
    free(currentRoute);
    free(visited);
}