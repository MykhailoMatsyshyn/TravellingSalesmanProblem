#include "graph.h"

int next_permutation(int* array, int size) {
    int i = size - 2;

    while (i >= 0 && array[i] >= array[i + 1]) {
        i--;
    }

    if (i < 0) {
        return 0; // Більше перестановок немає
    }

    int j = size - 1;
    while (array[j] <= array[i]) {
        j--;
    }

    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;

    int left = i + 1;
    int right = size - 1;
    while (left < right) {
        temp = array[left];
        array[left] = array[right];
        array[right] = temp;
        left++;
        right--;
    }

    //for (int i = 0; i < size; ++i) {
    //    printf("%d ", array[i]);
    //}
    //printf("\n");

    return 1; // Є ще перестановки
}


void bruteForce(Graph* graph) {
    printf("\n\n =================  \033[1;37m\033[4;37mМетод повного перебору\033[0m =================\n");
    if (graph->numCities > 13) {
        printf("\n (!) Алгоритм повного перебору не ефективний\n     для більш ніж 13 вершин через значне зростання\n     обчислювальної складности.\n\n");
        printf(" ===========================================================\n");
        return;
    }

    int vertices[MAX_CITIES];

    // Заповнення масиву вершин
    for (int i = 0; i < graph->numCities; ++i) {
        vertices[i] = i;
    }

    double minDistance = INT_MAX;
    int bestPath[MAX_CITIES];

    clock_t start_time = clock(); // Початок обчислень

    struct timespec begin;
    struct timespec end;

    timespec_get(&begin, TIME_UTC);


    int iteration = 1; // Змінна для відстеження номера ітерації

    // Пошук найкращого шляху
    do {
        double currentDistance = 0;

        // Підрахунок відстані для поточного шляху
        for (int i = 0; i < graph->numCities - 1; ++i) {
            int city1 = vertices[i];
            int city2 = vertices[i + 1];
            currentDistance += graph->adjacency_matrix[city1][city2];
        }

        // Додавання відстані від останньої до першої вершини для утворення циклу
        currentDistance += graph->adjacency_matrix[vertices[graph->numCities - 1]][vertices[0]];

        // Порівняння та збереження найкращого шляху
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            for (int i = 0; i < graph->numCities; ++i) {
                bestPath[i] = vertices[i];
            }
        }

        //// Виведення поточного порядку вершин
        //printf("Ітерація %d: ", iteration++);
        //for (int i = 0; i < graph->numCities; ++i) {
        //    printf("%d ", vertices[i]);
        //}
        //printf(" --> ");
    } while (next_permutation(vertices, graph->numCities)); // Функція next_permutation міняє порядок вершин


    timespec_get(&end, TIME_UTC);
    clock_t end_time = clock(); // Кінець обчислень

    double cpu_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("\n МАРШРУТ:  ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("%d-", bestPath[i]);
    }
    printf("%d\n           ", bestPath[0]); // Повернення до початкової вершини

    for (int i = 0; i < graph->numCities; ++i) {
        printf("%s -> ", graph->cities[bestPath[i]].name);
    }
    printf("%s\n", graph->cities[bestPath[0]].name); // Повернення до початкової вершини

    printf("\n ВІДСТАНЬ: ");
    for (int i = 0; i < graph->numCities - 1; ++i) {
        printf("%.2f + ", graph->adjacency_matrix[bestPath[i]][bestPath[i + 1]]);
    }
    printf("%.2f = %.2f км.\n\n", graph->adjacency_matrix[bestPath[graph->numCities - 1]][bestPath[0]], minDistance);

    double time_spent = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    printf(" [ Час виконання WALL: %.7f секунд ]\n", time_spent);

    printf(" [ Час виконання CPU: %.7f секунд ]\n\n", cpu_time);
    printf(" ===========================================================\n");
}
