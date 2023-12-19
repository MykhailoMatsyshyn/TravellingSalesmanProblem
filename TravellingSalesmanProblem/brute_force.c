#include "graph.h"

int next_permutation(int* array, int size) {
    int i = size - 2;

    while (i >= 0 && array[i] >= array[i + 1]) {
        i--;
    }

    if (i < 0) {
        return 0; // ������ ������������ ����
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

    return 1; // � �� ������������
}


void bruteForce(Graph* graph) {
    printf("\n\n =================  \033[1;37m\033[4;37m����� ������� ��������\033[0m =================\n");
    if (graph->numCities > 13) {
        printf("\n (!) �������� ������� �������� �� ����������\n     ��� ���� �� 13 ������ ����� ������ ���������\n     ������������� ����������.\n\n");
        printf(" ===========================================================\n");
        return;
    }

    int vertices[MAX_CITIES];

    // ���������� ������ ������
    for (int i = 0; i < graph->numCities; ++i) {
        vertices[i] = i;
    }

    double minDistance = INT_MAX;
    int bestPath[MAX_CITIES];

    clock_t start_time = clock(); // ������� ���������

    struct timespec begin;
    struct timespec end;

    timespec_get(&begin, TIME_UTC);


    int iteration = 1; // ����� ��� ���������� ������ ��������

    // ����� ���������� �����
    do {
        double currentDistance = 0;

        // ϳ�������� ������ ��� ��������� �����
        for (int i = 0; i < graph->numCities - 1; ++i) {
            int city1 = vertices[i];
            int city2 = vertices[i + 1];
            currentDistance += graph->adjacency_matrix[city1][city2];
        }

        // ��������� ������ �� �������� �� ����� ������� ��� ��������� �����
        currentDistance += graph->adjacency_matrix[vertices[graph->numCities - 1]][vertices[0]];

        // ��������� �� ���������� ���������� �����
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            for (int i = 0; i < graph->numCities; ++i) {
                bestPath[i] = vertices[i];
            }
        }

        //// ��������� ��������� ������� ������
        //printf("�������� %d: ", iteration++);
        //for (int i = 0; i < graph->numCities; ++i) {
        //    printf("%d ", vertices[i]);
        //}
        //printf(" --> ");
    } while (next_permutation(vertices, graph->numCities)); // ������� next_permutation ���� ������� ������


    timespec_get(&end, TIME_UTC);
    clock_t end_time = clock(); // ʳ���� ���������

    double cpu_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("\n �������:  ");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("%d-", bestPath[i]);
    }
    printf("%d\n           ", bestPath[0]); // ���������� �� ��������� �������

    for (int i = 0; i < graph->numCities; ++i) {
        printf("%s -> ", graph->cities[bestPath[i]].name);
    }
    printf("%s\n", graph->cities[bestPath[0]].name); // ���������� �� ��������� �������

    printf("\n ²������: ");
    for (int i = 0; i < graph->numCities - 1; ++i) {
        printf("%.2f + ", graph->adjacency_matrix[bestPath[i]][bestPath[i + 1]]);
    }
    printf("%.2f = %.2f ��.\n\n", graph->adjacency_matrix[bestPath[graph->numCities - 1]][bestPath[0]], minDistance);

    double time_spent = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    printf(" [ ��� ��������� WALL: %.7f ������ ]\n", time_spent);

    printf(" [ ��� ��������� CPU: %.7f ������ ]\n\n", cpu_time);
    printf(" ===========================================================\n");
}
