#include "graph.h"

/* ��������� ������� ��� ���������� ����*/
void line(const char* sym, int ks) {
    for (int i = 0; i < ks; i++) {
        printf("%s", sym);
    }
    printf("\n");
}

void line2(const char* sym, int ks) {
    for (int i = 0; i < ks; i++) {
        printf("%s", sym);
    }
}

/*******************************************************/

void initializeGraph(Graph* graph) {
    // ������������� ������� �������� ������
    for (int i = 0; i < MAX_CITIES; ++i) {
        for (int j = 0; j < MAX_CITIES; ++j) {
            graph->adjacency_matrix[i][j] = 0.0;
        }
    }
}

void addEdge(Graph* graph, int city1, int city2, double distance) {
    // ������ ����� � ����� (��������) �� ������
    graph->adjacency_matrix[city1][city2] = distance;
    graph->adjacency_matrix[city2][city1] = distance;
}

// ������� ��������� ���� �� �����
void addCity(Graph* graph, char* name, double latitude, double longitude) {
    if (graph->numCities < MAX_CITIES) {
        City city;
        city.num = graph->numCities + 1; // �������� ��������� � 1
        strcpy_s(city.name, sizeof(city.name), name);
        city.latitude = latitude;
        city.longitude = longitude;
        graph->cities[graph->numCities++] = city;
    }
    else {
        printf("���������� ����������� ������� ���!\n");
    }
}

void calculateDistances(Graph* graph) {
    printf("\n  ������� ��������:\n");
    printf(" -------------------------------------------------------------------\n");
    printf(" ");  line("\227", 21);

    // ��������� ������������ ������ ������
    printf(" |"); line2(" ", 19);
    for (int i = 0; i < graph->numCities; ++i) {
        printf("|    %2d    ", i);
    }
    printf("|\n");

    // ��������� ������������� ����
    printf(" |    ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("----------");
    }
    printf("|");

    for (int i = 0; i < graph->numCities; ++i) {
        printf("\n | %-18s", graph->cities[i].name); // ����� ����

        for (int j = 0; j < graph->numCities; ++j) {
            if (i == j) {
                graph->adjacency_matrix[i][j] = 0.0;
            }
            else if (graph->adjacency_matrix[i][j] == 0.0) {
                double distance = haversine(graph->cities[i].latitude, graph->cities[i].longitude, graph->cities[j].latitude, graph->cities[j].longitude);
                addEdge(graph, i, j, distance);
            }
            printf("| %7.2f  ", graph->adjacency_matrix[i][j]);
        }
        puts("|");
        printf(" "); line2(" ", 21);  line2("\227", 11 * graph->numCities);
    }
}

/***************************************/

// ������� ������ �����
void printGraph(Graph* graph) {
    printf("\n  ������ ������� ������:\n");
    printf(" --------------------------------------------\n");
    for (int i = 0; i < graph->numCities; ++i) {
        printf(" | %2d. %-18s[%.4f, %.4f] |\n", i, graph->cities[i].name, graph->cities[i].latitude, graph->cities[i].longitude);
    }
    printf(" --------------------------------------------\n");
}
