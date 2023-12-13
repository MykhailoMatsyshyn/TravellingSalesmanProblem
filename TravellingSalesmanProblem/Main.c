#include "algorithms.h"

/*================================================*/

int main() {
    system("chcp 1251");

    Graph graph;

    // Ініціалізувати граф
    graph.numCities = 0;
    initializeGraph(&graph);

    // Додавання міст до графу
    addCity(&graph, "Перемишляни", 49.4014, 24.3336);
    addCity(&graph, "Львів", 49.8525, 24.0515);
    addCity(&graph, "Київ", 50.4501, 30.5234);
    addCity(&graph, "Вінниця", 49.2331, 28.4682);
    addCity(&graph, "Дніпро", 48.45, 34.9833);
    addCity(&graph, "Донецьк", 48.0159, 37.8028);
    addCity(&graph, "Житомир", 50.2547, 28.6587);
    addCity(&graph, "Одеса", 46.4694, 30.7409);
    addCity(&graph, "Харків", 49.9935, 36.2304);
    addCity(&graph, "Запоріжжя", 47.8388, 35.1396);
    addCity(&graph, "Івано-Франківськ", 48.9226, 24.7111);
    addCity(&graph, "Чернівці", 48.2921, 25.9354);
    addCity(&graph, "Хмельницький", 49.4225, 26.9871);
    addCity(&graph, "Черкаси", 49.4444, 32.0597);
    addCity(&graph, "Суми", 50.9077, 34.7981);


    // Виведення графу
    printGraph(&graph);

    // Обчислення відстаней між вершинами
    calculateDistances(&graph);


    nearestNeighbor(&graph);

    enhancedNearestNeighbor(&graph);

    return 0;
}

/*================================================*/
