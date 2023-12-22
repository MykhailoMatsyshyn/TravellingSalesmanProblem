#include "graph.h"

/* Додаткова функція для формування ліній*/
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
    graph->numCities = 0;

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

// Функція для обчислення відстаней
void calculateDistances(Graph* graph) {
    for (int i = 0; i < graph->numCities; ++i) {
        for (int j = 0; j < graph->numCities; ++j) {
            if (i == j) {
                graph->adjacency_matrix[i][j] = 0.0;
            }
            else if (graph->adjacency_matrix[i][j] == 0.0) {
                double distance = haversine(graph->cities[i].latitude, graph->cities[i].longitude, graph->cities[j].latitude, graph->cities[j].longitude);
                addEdge(graph, i, j, distance);
            }
        }
    }
}

// Функція для виведення обчислених відстаней
void printDistanceMatrix(Graph* graph) {
    if (graph->numCities > N_TO_PRINT) return 0;
    printf("\n  Матриця відстаней:\n");
    printf(" "); line2("\227", 21); line2("\227", 11 * graph->numCities);
    printf("\n | Пункти:\\Їх номера:"); /* line2(" ", 19);*/
    // Виведення вертикальних номерів вершин
    for (int i = 0; i < graph->numCities; ++i) {
        printf("|    %2d    ", i);
    }
    printf("|\n");

    printf(" "); line2("\227", 21); line2("\227", 11 * graph->numCities);

    for (int i = 0; i < graph->numCities; ++i) {
        printf("\n | %-18s", graph->cities[i].name); // Назва міста

        for (int j = 0; j < graph->numCities; ++j) {
            printf("| %7.2f  ", graph->adjacency_matrix[i][j]);
        }
        puts("|");
        printf(" "); line2("\227", 21); line2("\227", 11 * graph->numCities);
    }
}

/***************************************/

// Функція виводу графу
void printGraph(Graph* graph) {
    printf("\n ---------------------------------------------");
    printf("\n \x0A6           Список заданих пунктів:         \x0A6\n");
    printf(" ---------------------------------------------\n");
    for (int i = 0; i < graph->numCities; ++i) {
        printf(" \x0A6 %3d. %-18s[%.4f, %.4f] \x0A6\n", i, graph->cities[i].name, graph->cities[i].latitude, graph->cities[i].longitude);
    }
    printf(" --------------------------------------------\n");
}
