// ��������� �������������� ������ ����������� �����

#include "graph.h"


void enhancedNearestNeighbor(Graph* graph) {
    int initial = 0; // ���������� ����� ��� ���������
    double min_distance = -1.0; // ̳������� �������� �������

    int best_route[MAX_CITIES]; // ��������� �������
    double best_distance = -1.0; // ³������ ��� ���������� ��������

    for (int start = 0; start < graph->numCities; ++start) {
        double total_distance = 0.0;
        int current = start;

        int visited[MAX_CITIES] = { 0 };
        visited[current] = 1;

        int count = 1;

        int route[MAX_CITIES]; // �������� ������� ��� ������� ��������� �������
        route[0] = current;

        while (count < graph->numCities) {
            int nearest_city = -1;
            double min_distance = -1.0;

            for (int i = 0; i < graph->numCities; ++i) {
                if (!visited[i]) {
                    if (nearest_city == -1 || graph->adjacency_matrix[current][i] < min_distance) {
                        nearest_city = i;
                        min_distance = graph->adjacency_matrix[current][i];
                    }
                }
            }

            visited[nearest_city] = 1;
            count++;

            route[count - 1] = nearest_city; // �����'������� �������

            total_distance += min_distance;

            current = nearest_city;
        }

        total_distance += graph->adjacency_matrix[current][start];

        if (min_distance == -1 || total_distance < min_distance) {
            min_distance = total_distance;
            initial = start;

            // ������������ ��������� �������
            for (int i = 0; i < graph->numCities; ++i) {
                best_route[i] = route[i];
            }
            best_distance = total_distance;
        }
    }

    // �������� �� ������� ��������
    printf("�� ���������� �������� �� ��� ������:\n");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("������� %d:", i + 1);
        for (int j = 0; j < graph->numCities; ++j) {
            printf(" %d", best_route[j] + 1); // �������� ������� ��������
        }
        printf(" - ³������: %.2f\n", best_distance);
    }

    // �������� ��������� �������
    printf("��������� ������� ���������� � ������� %d � ��������: %.2f\n", initial + 1, min_distance);
}
