#define _USE_MATH_DEFINES 
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*================================================*/

// ʳ������ ������������ ��� ��� �����
#define MAX_CITIES 50

// ����� ���� � ���������
#define EARTH_RADIUS 6371.0

// ��������� ��� ��������� ��������� ���
typedef struct {
    int num;
    char name[50];
    double latitude;
    double longitude;
} City;

// ��������� ��� ��������� �����
typedef struct {
    int numCities;
    City cities[MAX_CITIES];
    double adjacency_matrix[MAX_CITIES][MAX_CITIES];
} Graph;

/*================================================*/

double haversine(double, double, double, double);
void calculateDistances(Graph*);
void addCity(Graph*, char*, double, double);
void printGraph(Graph*);
void initializeGraph(Graph* graph);
void addEdge(Graph* graph, int city1, int city2, double distance);

/*================================================*/

/*================================================*/


int main() {
    system("chcp 1251");

    Graph graph;

    // ������������ ����
    graph.numCities = 0;
    initializeGraph(&graph);

    // ��������� ��� �� �����
    addCity(&graph, "���", 50.4501, 30.5234);
    addCity(&graph, "³�����", 49.2331, 28.4682);
    addCity(&graph, "�����", 48.45, 34.9833);
    addCity(&graph, "�������", 48.0159, 37.8028);
    addCity(&graph, "�������", 50.2547, 28.6587);
    addCity(&graph, "��������", 47.8388, 35.1396);
    addCity(&graph, "�����-���������", 48.9226, 24.7111);
    addCity(&graph, "�������������", 48.5044, 32.2607);
    addCity(&graph, "��������", 48.574, 39.3078);
    addCity(&graph, "��������", 48.574, 39.3078);


    // ��������� �����
    printGraph(&graph);

    // ���������� �������� �� ���������
    calculateDistances(&graph);

    return 0;
}

/*================================================*/

/*================================================*/

void initializeGraph(Graph* graph) {
    // ������������ ������� �������� ������
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

// ������� ������ �����
void printGraph(Graph* graph) {
    printf("\n  ������ ������� ������:\n");
    printf(" --------------------------------------------\n");
    for (int i = 0; i < graph->numCities; ++i) {
        printf(" | %2d. %-18s[%.4f, %.4f] |\n", i + 1, graph->cities[i].name, graph->cities[i].latitude, graph->cities[i].longitude);
    }
    printf(" --------------------------------------------\n");
}

/*================================================*/

/*================================================*/

// ������� ���������� ������ �� �������� �����������
double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dlat = (lat2 - lat1) * M_PI / 180.0;
    double dlon = (lon2 - lon1) * M_PI / 180.0;
    double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) * sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = EARTH_RADIUS * c;

    return distance;
}

void calculateDistances(Graph* graph) {
    printf("\n  ������� ��������:\n");
    printf(" ----------------------------------------------\n");

    // ��������� ������������ ������ ������
    printf(" |      ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf(" %5d  ", i + 1);
    }
    printf("\n");

    // ��������� ������������� ��
    printf(" |    ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("--------");
    }
    printf("|");

    for (int i = 0; i < graph->numCities; ++i) {
        printf(" | \n | %2d |", i + 1); // ����� ������� �� ����������

        for (int j = 0; j < graph->numCities; ++j) {
            if (i == j) {
                graph->adjacency_matrix[i][j] = 0.0;
            }
            else if (graph->adjacency_matrix[i][j] == 0.0) {
                double distance = haversine(graph->cities[i].latitude, graph->cities[i].longitude, graph->cities[j].latitude, graph->cities[j].longitude);
                addEdge(graph, i, j, distance);
            }
            printf(" %7.2f  ", graph->adjacency_matrix[i][j]);
        }
        puts("|");
    }
}

/*================================================*/