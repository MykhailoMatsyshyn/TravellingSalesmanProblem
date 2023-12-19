#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"

void loadCitiesFromFile(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Не вдалося відкрити файл");
        return;
    }

    char city_name[50];
    double latitude, longitude;

    while (fscanf(file, "%49[^,], %lf, %lf\n", city_name, &latitude, &longitude) == 3)
        addCity(graph, city_name, latitude, longitude);

    fclose(file);
}

//----------------------------------------------------------------------

int selectDataFile(int argc, char* argv[]) {
    int verticesOptions[] = { 5, 10, 13, 15, 20, 50, 75, 100, 125, 150 };
    int numOptions = sizeof(verticesOptions) / sizeof(verticesOptions[0]);

    int numVertices, index = -1;
    printf("\033[1;37m\n Оберіть кількість пунктів (5, 10, 13, 15, 20, 50, 75, 100, 125, 150): \n >> \033[0m");
    scanf_s("%d", &numVertices);

    for (int i = 0; i < numOptions; i++) {
        if (verticesOptions[i] == numVertices) {
            index = i + 1;
            break;
        }
    }

    if (index == -1) {
        printf("\n \033[0;101m(!) Помилка: Неправильна кількість пунктів.\033[0m\n");
        return NULL;
    }

    return index;
}
