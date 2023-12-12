// Реалізація вдосконаленого методу найближчого сусіда

#include "graph.h"


void enhancedNearestNeighbor(Graph* graph) {
    int initial = 0; // Початковий пункт для алгоритму
    double min_distance = -1.0; // Мінімальна знайдена відстань

    int best_route[MAX_CITIES]; // Найкращий маршрут
    double best_distance = -1.0; // Відстань для найкращого маршруту

    for (int start = 0; start < graph->numCities; ++start) {
        double total_distance = 0.0;
        int current = start;

        int visited[MAX_CITIES] = { 0 };
        visited[current] = 1;

        int count = 1;

        int route[MAX_CITIES]; // Зберігаємо маршрут для поточної початкової вершини
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

            route[count - 1] = nearest_city; // Запам'ятовуємо маршрут

            total_distance += min_distance;

            current = nearest_city;
        }

        total_distance += graph->adjacency_matrix[current][start];

        if (min_distance == -1 || total_distance < min_distance) {
            min_distance = total_distance;
            initial = start;

            // Перезаписуємо найкращий маршрут
            for (int i = 0; i < graph->numCities; ++i) {
                best_route[i] = route[i];
            }
            best_distance = total_distance;
        }
    }

    // Виводимо всі знайдені маршрути
    printf("Всі переглянуті маршрути та їхні відстані:\n");
    for (int i = 0; i < graph->numCities; ++i) {
        printf("Маршрут %d:", i + 1);
        for (int j = 0; j < graph->numCities; ++j) {
            printf(" %d", best_route[j] + 1); // Виводимо вершини маршруту
        }
        printf(" - Відстань: %.2f\n", best_distance);
    }

    // Виводимо найкращий маршрут
    printf("Найкращий маршрут починається з вершини %d з відстанню: %.2f\n", initial + 1, min_distance);
}
