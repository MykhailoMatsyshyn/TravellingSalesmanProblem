// ��������� ������ ����������� �����

#include "graph.h"

void nearestNeighbor(Graph* graph) 
{
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

    printf("\n\n================\n");

    // 3. ��������� ��������
    printf("\n � ��������� ��������� ������� ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("%d-", path[i]);
    }

    // 4. ��������� �������� ������
    printf("\b, ���� ��������� �������:\n ");
    for (int i = 0; i < graph->numCities - 1; ++i) {
        printf("%.2f + ", graph->adjacency_matrix[path[i]][path[i + 1]]);
    }
    printf("\b\b= %.2f ��������.\n\n================\n\n", totalDistance);
}