// ��������� ������ ����������� �����

#include "graph.h"

void nearestNeighbor(Graph* graph) {
    struct timespec begin;
    struct timespec end;
    clock_t cpu_start, cpu_end;
    double cpu_time_used;

    timespec_get(&begin, TIME_UTC);
    cpu_start = clock();

    // 1. ������� � ��������� ������� ��� ������ ��������� �����
    int startVertex = 0; // ���� ��������� ������� (���� ���� ����-����)
    int currentVertex = startVertex;

    // ����� ��� ���������� �������� ������
    int visited[MAX_CITIES];
    for (int i = 0; i < MAX_CITIES; ++i) {
        visited[i] = 0; // ���������, �� ����� ������� �� �������
    }

    // ����� ��� ��������� ����� �� �������� ������
    int path[MAX_CITIES];
    int pathIndex = 0;
    double totalDistance = 0.0;

    // 2. ����� ������
    visited[startVertex] = 1; // ��������� ��������� ������� �� �������
    path[pathIndex++] = startVertex; // ������ ��������� ������� �� �����

    while (pathIndex < graph->numCities) {
        int nearestVertex = -1; // ��������� �������
        double minDistance = -1; // ̳������� �������

        // ����������� ��������� �������
        for (int i = 0; i < graph->numCities; ++i) {
            if (!visited[i] && (nearestVertex == -1 || graph->adjacency_matrix[currentVertex][i] < minDistance)) {
                nearestVertex = i;
                minDistance = graph->adjacency_matrix[currentVertex][i];
            }
        }

        visited[nearestVertex] = 1; // ��������� ��������� ������� �� �������
        path[pathIndex++] = nearestVertex; // ������ ��������� ������� �� �����
        totalDistance += minDistance; // ������ ������� �� �������� ������
        currentVertex = nearestVertex; // ���������� �� ��������� �������
    }
    
    // ��������� ����������� ����� �� �������� ������� �� ���������
    totalDistance += graph->adjacency_matrix[path[graph->numCities - 1]][startVertex];
    path[pathIndex++] = startVertex;

    cpu_end = clock();

    timespec_get(&end, TIME_UTC);

    printf("\n\n ================  \033[1;37m\033[4;37m����� ����������� �����\033[0m ================\n");

    // 3. ��������� ��������
    printf("\n �������:  ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("%d-", path[i]);
    }
    printf("%d\n           ", startVertex);

    for (int i = 0; i < graph->numCities; ++i) {
        printf("%s -> ", graph->cities[path[i]].name);
    }
    printf("%s\n", graph->cities[startVertex].name);

    // 4. ��������� �������� ������
    printf("\n ²������: ");
    for (int i = 0; i < graph->numCities - 1; ++i) {
        printf("%.2f + ", graph->adjacency_matrix[path[i]][path[i + 1]]);
    }
    printf("%.2f = %.2f ��.\n\n", 
           graph->adjacency_matrix[path[graph->numCities - 1]][startVertex], totalDistance);

    double time_spent = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    printf(" [ ��� ��������� WALL: %.7f ������ ]\n", time_spent);

    cpu_time_used = ((double)(cpu_end - cpu_start)) / CLOCKS_PER_SEC;
    printf(" [ ��� ��������� CPU: %.7f ������ ]\n\n", cpu_time_used);
    printf(" ===========================================================\n");
}