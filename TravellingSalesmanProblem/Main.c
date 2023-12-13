#include "algorithms.h"

/*================================================*/

int main() {
    system("chcp 1251");

    Graph graph;

    // ������������ ����
    graph.numCities = 0;
    initializeGraph(&graph);

    // ��������� ��� �� �����
    addCity(&graph, "�����������", 49.4014, 24.3336);
    addCity(&graph, "����", 49.8525, 24.0515);
    addCity(&graph, "���", 50.4501, 30.5234);
    addCity(&graph, "³�����", 49.2331, 28.4682);
    addCity(&graph, "�����", 48.45, 34.9833);
    addCity(&graph, "�������", 48.0159, 37.8028);
    addCity(&graph, "�������", 50.2547, 28.6587);
    addCity(&graph, "�����", 46.4694, 30.7409);
    addCity(&graph, "�����", 49.9935, 36.2304);
    addCity(&graph, "��������", 47.8388, 35.1396);
    addCity(&graph, "�����-���������", 48.9226, 24.7111);
    addCity(&graph, "�������", 48.2921, 25.9354);
    addCity(&graph, "������������", 49.4225, 26.9871);
    addCity(&graph, "�������", 49.4444, 32.0597);
    addCity(&graph, "����", 50.9077, 34.7981);


    // ��������� �����
    printGraph(&graph);

    // ���������� �������� �� ���������
    calculateDistances(&graph);


    nearestNeighbor(&graph);

    enhancedNearestNeighbor(&graph);

    return 0;
}

/*================================================*/
