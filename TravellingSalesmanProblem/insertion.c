#include "graph.h"

// ������� ��� ������ ��������� �����, ��� �� �� � �������
int findNearestNotInRoute(Graph* graph, int* inRoute, int numCities) {
    double minDistance = 999999.0;
    int nearest = -1;
    // ��������� �� ��� ������ �����
    for (int i = 0; i < numCities; ++i) {
        if (!inRoute[i]) {  // ���� ����� �� �� � �������
            for (int j = 0; j < numCities; ++j) {  // ���������� ������ �� �����, �� ��� � �������
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
    printf("\n\n ======================= \033[1;37m\033[4;37m����� �������\033[0m =====================\n");

    int numCities = graph->numCities;
    int* route = malloc(numCities * sizeof(int));  // ����� ��� ��������� ��������
    int* inRoute = calloc(numCities, sizeof(int));  // ����� ��� ����������, �� ����� ��� � �������

    struct timespec begin, end;
    clock_t cpu_start, cpu_end;
    timespec_get(&begin, TIME_UTC);  // ������� ���������� ����
    cpu_start = clock();

    // ����������� �������� � ������ ����� �����
    route[0] = 0;
    route[1] = 1;
    route[2] = 2;
    inRoute[0] = inRoute[1] = inRoute[2] = 1;

    int routeSize = 3;

    // ��������� ��������� ���������� �����
    for (int i = 3; i < numCities; ++i) {
        int nearest = findNearestNotInRoute(graph, inRoute, numCities);
        //printf("��������� �����, �� �� � �������: %d\n", nearest);
        inRoute[nearest] = 1;

        // ����������� ���������� ���� ��� ������� �����
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
        //printf("�������� ������� ��� �������: %d\n", bestPosition);

        // ������� ����� � �������
        for (int j = routeSize; j > bestPosition; --j) {
            route[j] = route[j - 1];
        }
        route[bestPosition] = nearest;
        routeSize++;
        // ��������� ��������� �������� ���� �������
        //printf("�������� �������: ");
        //for (int k = 0; k < routeSize; ++k) {
        //    printf("%d ", route[k]);
        //}
        //printf("\n");
    }

    cpu_end = clock();
    timespec_get(&end, TIME_UTC);  // ʳ���� ���������� ����

    // ���������� �������� ������ �� ��������� ��������
    double totalDistance = 0.0;
    printf("\n \033[0;103m\033[1;37m\033[4;37m�������:\033[0m  ");
    for (int i = 0; i < numCities - 1; ++i) {
        printf("%d-", route[i]);
        totalDistance += graph->adjacency_matrix[route[i]][route[i + 1]];
    }
    totalDistance += graph->adjacency_matrix[route[numCities - 1]][route[0]];  // ��������� ������ �� ��������� �����
    printf("%d-%d\n           ", route[numCities - 1], route[0]);

    // ��������� ���� ���
    for (int i = 0; i < numCities - 1; ++i) {
        printf("%s -> ", graph->cities[route[i]].name);
    }
    printf("%s -> %s\n", graph->cities[route[numCities - 1]].name, graph->cities[route[0]].name);

    // ��������� �������� ������
    printf("\n \033[0;103m\033[1;37m\033[4;37m²������:\033[0m ");
    for (int i = 0; i < numCities - 1; ++i) {
        printf("%.2f + ", graph->adjacency_matrix[route[i]][route[i + 1]]);
    }
    printf("%.2f = \033[0;103m%.2f ��.\033[0m\n\n", graph->adjacency_matrix[route[numCities - 1]][route[0]], totalDistance);

    double time_spent = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    printf(" [ ��� ��������� WALL: %.7f ������ ]\n", time_spent);

    double cpu_time_used = ((double)(cpu_end - cpu_start)) / CLOCKS_PER_SEC;
    printf(" [ ��� ��������� CPU: %.7f ������ ]\n\n", cpu_time_used);
    printf(" ===========================================================\n");

    free(route);
    free(inRoute);
}
