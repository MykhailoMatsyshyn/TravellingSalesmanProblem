#include "algorithms.h"

/*================================================*/

int main() {
    system("chcp 1251");

    Graph graph;

    // Ініціалізувати граф
    graph.numCities = 0;
    initializeGraph(&graph);

    // Додавання міст до графу
    addCity(&graph, "Київ", 50.4501, 30.5234);
    addCity(&graph, "Вінниця", 49.2331, 28.4682);
    addCity(&graph, "Дніпро", 48.45, 34.9833);
    addCity(&graph, "Донецьк", 48.0159, 37.8028);
    addCity(&graph, "Житомир", 50.2547, 28.6587);

    // Виведення графу
    printGraph(&graph);

    // Обчислення відстаней між вершинами
    calculateDistances(&graph);


    nearestNeighbor(&graph);

    enhancedNearestNeighbor(&graph);

    return 0;
}

/*================================================*/
