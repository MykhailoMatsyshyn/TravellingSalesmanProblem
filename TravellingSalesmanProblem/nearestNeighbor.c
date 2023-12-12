// ��������� ������ ����������� �����

#include "graph.h"

void nearestNeighbor(Graph* graph) {
    // 1. ������� � ��������� ������� ��� ������ ��������� �����
    int startVertex = 0; // ���� ��������� ������� (���� ���� ����-����)
    int currentVertex = startVertex;

    // ����� ��� ���������� �������� ������
    int visited[MAX_CITIES];
    for (int i = 0; i < MAX_CITIES; ++i) {
        visited[i] = 0; // ���������, �� ����� ������� �� �������
    }

    // ����� ��� ��������� �����
    int path[MAX_CITIES];
    int pathIndex = 0;

    // 2. ����� ������
    visited[startVertex] = 1; // ��������� ��������� ������� �� �������
    path[pathIndex++] = startVertex; // ������ ��������� ������� �� �����

    while (pathIndex < graph->numCities) {
        int nearestVertex = -1; // ��������� �������

        // ����������� ��������� �������
        for (int i = 0; i < graph->numCities; ++i) {
            if (!visited[i] && (nearestVertex == -1 || graph->adjacency_matrix[currentVertex][i] < graph->adjacency_matrix[currentVertex][nearestVertex])) {
                nearestVertex = i;
            }
        }

        visited[nearestVertex] = 1; // ��������� ��������� ������� �� �������
        path[pathIndex++] = nearestVertex; // ������ ��������� ������� �� �����
        currentVertex = nearestVertex; // ���������� �� ��������� �������
    }

    // 3. ��������� ��������
    printf("\n�������, ��������� �� ��������� ��������� ����������� �����:\n");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("%d ", path[i]);
    }
    printf("\n");
}