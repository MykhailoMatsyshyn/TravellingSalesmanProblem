// ��������� �������������� ������ ����������� �����

#include "graph.h"
#include <limits.h>

clock_t cpu_start, cpu_end, suspended_time;
double cpu_time_used;

int* findBestPath(Graph* graph, int startVertex) {
    // ��������� ���'�� ��� ������ �����
    int* path = malloc((MAX_CITIES + 1) * sizeof(int));
    if (path == NULL) {
        printf("������� �������� ���'��\n");
        return NULL;
    }

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

    // ������ ��������� ������� � ����� �����
    path[pathIndex] = startVertex;

    cpu_end = clock();
    suspended_time += cpu_end - cpu_start;

    if (graph->numCities <= N_TO_PRINT) {
        // ���� �����
        printf("\n ����: ");
        for (int i = 0; i <= graph->numCities; ++i) {
            printf("%d-", path[i]);
        }
        printf("\b �������������� � ");
    }

    cpu_start = clock();

    // ���������� ������ �����
    return path;
}


void enhancedNearestNeighbor(Graph* graph) {
    cpu_start = clock();

    double minDistance = INT_MAX;
    int bestPath[MAX_CITIES];

    // ���� ��� ��� ������ ��� 0
    for (int i = 1; i < graph->numCities; ++i) {
        int* path = findBestPath(graph, i);
        if (path == NULL) {
            printf("������� � ������ �����\n");
            return;
        }

        // ��������� ������� 0 � ���������� �����
        int startIndex = 0;
        for (int j = 0; j < graph->numCities; ++j) {
            if (path[j] == 0) {
                startIndex = j;
                break;
            }
        }

        // ������������ �����
        int transformedPath[MAX_CITIES];
        int index = 0;
        for (int j = startIndex; j < graph->numCities; ++j) {
            transformedPath[index++] = path[j];
        }
        for (int j = 0; j < startIndex; ++j) {
            transformedPath[index++] = path[j];
        }

        // �����������, �� ���� ���������� ���������� ��������
        transformedPath[index] = 0;

        cpu_end = clock();
        suspended_time += cpu_end - cpu_start;

        if (graph->numCities <= N_TO_PRINT) {
            // ���� ������������� �����
            for (int j = 0; j < graph->numCities; ++j) {
                printf("%d-", transformedPath[j]);
            }
            printf("%d\n", transformedPath[graph->numCities]);
        }

        cpu_start = clock();

        // ϳ�������� ������ ��� ������������� �����
        double totalDistance = 0;
        for (int j = 0; j < graph->numCities; ++j) {
            int city1 = transformedPath[j];
            int city2 = transformedPath[j + 1];
            totalDistance += graph->adjacency_matrix[city1][city2];
        }

        // ��������� �� ���������� ���������� �����
        if (totalDistance < minDistance) {
            minDistance = totalDistance;
            for (int j = 0; j < graph->numCities + 1; ++j) {
                bestPath[j] = transformedPath[j];
            }
        }

        // ��������� ���'��
        free(path);
    }

    cpu_end = clock();
    suspended_time += cpu_end - cpu_start;

    // ���� ������������ ����� �� ���� ������
    printf("\n����������� ����: ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("%d-", bestPath[i]);
    }
    printf("%d\n³������: %.2f\n", bestPath[graph->numCities], minDistance);

    cpu_time_used = ((double)(suspended_time)) / CLOCKS_PER_SEC; // ���������� ��� ��������� � ��������
    printf("\n ��� ��������� CPU: %.7f ������\n", cpu_time_used);
}
