#include "graph.h"

void initializeGraph(Graph* graph) {
    // Ініціалізувати матрицю суміжності нулями
    for (int i = 0; i < MAX_CITIES; ++i) {
        for (int j = 0; j < MAX_CITIES; ++j) {
            graph->adjacency_matrix[i][j] = 0.0;
        }
    }
}

void addEdge(Graph* graph, int city1, int city2, double distance) {
    // Додати ребро з вагою (відстанню) між містами
    graph->adjacency_matrix[city1][city2] = distance;
    graph->adjacency_matrix[city2][city1] = distance;
}

// Функція додавання міста до графу
void addCity(Graph* graph, char* name, double latitude, double longitude) {
    if (graph->numCities < MAX_CITIES) {
        City city;
        city.num = graph->numCities + 1; // Починаємо нумерацію з 1
        strcpy_s(city.name, sizeof(city.name), name);
        city.latitude = latitude;
        city.longitude = longitude;
        graph->cities[graph->numCities++] = city;
    }
    else {
        printf("Перевищено максимальну кількість міст!\n");
    }
}

void calculateDistances(Graph* graph) {
    printf("\n  Матриця відстаней:\n");
    printf(" ----------------------------------------------\n");

    // Виведення вертикальних номерів вершин
    printf(" |      ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf(" %5d  ", i + 1);
    }
    printf("\n");

    // Виведення горизонтальної лінії
    printf(" |    ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("--------");
    }
    printf("|");

    for (int i = 0; i < graph->numCities; ++i) {
        printf(" | \n | %2d |", i + 1); // Номер вершини по горизонталі

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

/***************************************/

// Функція виводу графу
void printGraph(Graph* graph) {
    printf("\n  Список заданих пунктів:\n");
    printf(" --------------------------------------------\n");
    for (int i = 0; i < graph->numCities; ++i) {
        printf(" | %2d. %-18s[%.4f, %.4f] |\n", i + 1, graph->cities[i].name, graph->cities[i].latitude, graph->cities[i].longitude);
    }
    printf(" --------------------------------------------\n");
}