#include "graph.h"

// Функція для пошуку найближчої точки, яка ще не в маршруті
int findNearestNotInRoute(Graph* graph, int* inRoute, int numCities) {
    double minDistance = 999999.0;
    int nearest = -1;
    // Проходимо по всім точкам графа
    for (int i = 0; i < numCities; ++i) {
        if (!inRoute[i]) {  // Якщо точка ще не в маршруті
            for (int j = 0; j < numCities; ++j) {  // Перевіряємо відстані до точок, які вже в маршруті
                if (inRoute[j] && graph->adjacency_matrix[j][i] < minDistance) {
                    minDistance = graph->adjacency_matrix[j][i];
                    nearest = i;
                }
            }
        }
    }
    return nearest;
}

void insertionTSP(Graph* graph) {
    printf("\n\n ======================= \033[1;37m\033[4;37mМетод вставки\033[0m =====================\n");

    int numCities = graph->numCities;
    int* route = malloc(numCities * sizeof(int));  // Масив для зберігання маршруту
    int* inRoute = calloc(numCities, sizeof(int));  // Масив для відстеження, чи точка вже в маршруті

    struct timespec begin, end;
    clock_t cpu_start, cpu_end;
    timespec_get(&begin, TIME_UTC);  // Початок вимірювання часу
    cpu_start = clock();

    // Ініціалізація маршруту з перших трьох точок
    route[0] = 0;
    route[1] = 1;
    route[2] = 2;
    inRoute[0] = inRoute[1] = inRoute[2] = 1;

    int routeSize = 3;

    // Поступово додавання найближчих точок
    for (int i = 3; i < numCities; ++i) {
        int nearest = findNearestNotInRoute(graph, inRoute, numCities);
        //printf("Найближча точка, що не в маршруті: %d\n", nearest);
        inRoute[nearest] = 1;

        // Знаходження найкращого місця для вставки точки
        double bestDistanceIncrease = 999999.0;
        int bestPosition = -1;
        for (int j = 0; j < routeSize; ++j) {
            int next = (j + 1) % routeSize;
            double distanceIncrease = graph->adjacency_matrix[route[j]][nearest] +
                graph->adjacency_matrix[nearest][route[next]] -
                graph->adjacency_matrix[route[j]][route[next]];
            if (distanceIncrease < bestDistanceIncrease) {
                bestDistanceIncrease = distanceIncrease;
                bestPosition = j + 1;
            }
        }
        //printf("Найкраща позиція для вставки: %d\n", bestPosition);

        // Вставка точки в маршрут
        for (int j = routeSize; j > bestPosition; --j) {
            route[j] = route[j - 1];
        }
        route[bestPosition] = nearest;
        routeSize++;
        // Виведення поточного маршруту після вставки
        //printf("Поточний маршрут: ");
        //for (int k = 0; k < routeSize; ++k) {
        //    printf("%d ", route[k]);
        //}
        //printf("\n");
    }

    cpu_end = clock();
    timespec_get(&end, TIME_UTC);  // Кінець вимірювання часу

    // Обчислення загальної відстані та виведення маршруту
    double totalDistance = 0.0;
    printf("\n \033[0;103m\033[1;37m\033[4;37mМАРШРУТ:\033[0m  ");
    for (int i = 0; i < numCities - 1; ++i) {
        printf("%d-", route[i]);
        totalDistance += graph->adjacency_matrix[route[i]][route[i + 1]];
    }
    totalDistance += graph->adjacency_matrix[route[numCities - 1]][route[0]];  // Додавання відстані до початкової точки
    printf("%d-%d\n           ", route[numCities - 1], route[0]);

    // Виведення назв міст
    for (int i = 0; i < numCities - 1; ++i) {
        printf("%s -> ", graph->cities[route[i]].name);
    }
    printf("%s -> %s\n", graph->cities[route[numCities - 1]].name, graph->cities[route[0]].name);

    // Виведення загальної відстані
    printf("\n \033[0;103m\033[1;37m\033[4;37mВІДСТАНЬ:\033[0m ");
    for (int i = 0; i < numCities - 1; ++i) {
        printf("%.2f + ", graph->adjacency_matrix[route[i]][route[i + 1]]);
    }
    printf("%.2f = \033[0;103m%.2f км.\033[0m\n\n", graph->adjacency_matrix[route[numCities - 1]][route[0]], totalDistance);

    double time_spent = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    printf(" [ Час виконання WALL: %.7f секунд ]\n", time_spent);

    double cpu_time_used = ((double)(cpu_end - cpu_start)) / CLOCKS_PER_SEC;
    printf(" [ Час виконання CPU: %.7f секунд ]\n\n", cpu_time_used);
    printf(" ===========================================================\n");

    free(route);
    free(inRoute);
}
