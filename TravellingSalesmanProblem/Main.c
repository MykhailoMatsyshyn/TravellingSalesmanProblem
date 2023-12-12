#include "algorithms.h"

/*================================================*/

int main() {
    system("chcp 1251");

    Graph graph;

    // ������������ ����
    graph.numCities = 0;
    initializeGraph(&graph);

    // ��������� ��� �� �����
    addCity(&graph, "���", 50.4501, 30.5234);
    addCity(&graph, "³�����", 49.2331, 28.4682);
    addCity(&graph, "�����", 48.45, 34.9833);
    addCity(&graph, "�������", 48.0159, 37.8028);
    addCity(&graph, "�������", 50.2547, 28.6587);

    // ��������� �����
    printGraph(&graph);

    // ���������� �������� �� ���������
    calculateDistances(&graph);


    nearestNeighbor(&graph);

    enhancedNearestNeighbor(&graph);

    return 0;
}

/*================================================*/
