#define _CRT_SECURE_NO_WARNINGS
#include "algorithms.h"

/*================================================*/
void loadCitiesFromFile(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("�� ������� ������� ����");
        return;
    }

    char city_name[50];
    double latitude, longitude;

    while (fscanf(file, "%49[^,], %lf, %lf\n", city_name, &latitude, &longitude) == 3) {
        addCity(graph, city_name, latitude, longitude);
    }

    fclose(file);
}


int main(int argc, char* argv[]) {
    system("chcp 1251");

    printf("\n \033[0;104m");  line(" ", 65); printf("\033[0m \033[0;104m \033[0m"); line2(" ", 63); printf("\033[0;104m \033[0m");
    printf("\n \033[0;104m \033[0m\t\t  HUMANITARIAN AID DELIVERY (TSP) \t\t \033[0;103m \033[0m");
    printf("\n \033[0;103m \033[0m"); line2(" ", 63); printf("\033[0;103m \033[0m"); printf("\n \033[0;103m");  line(" ", 65); printf("\033[0m\n");

    int verticesOptions[] = { 5, 10, 13, 15, 20, 50, 75, 100, 125, 150 };
    int numOptions = sizeof(verticesOptions) / sizeof(verticesOptions[0]);

    int numVertices, index = -1;
    printf("\033[1;37m\n ������ ������� ������ (5, 10, 13, 15, 20, 50, 75, 100, 125, 150): \n >> \033[0m");
    scanf_s("%d", &numVertices);

    for (int i = 0; i < numOptions; i++) {
        if (verticesOptions[i] == numVertices) {
            index = i + 1;
            break;
        }
    }

    if (index == -1) {
        printf("\n \033[0;101m(!) �������: ����������� ������� ������.\033[0m\n");
        return 1;
    }

    char* filename = argv[index];

    Graph graph;
    graph.numCities = 0;

    initializeGraph(&graph);
    loadCitiesFromFile(&graph, filename);

    //Graph graph;

    //// ������������� ����
    //graph.numCities = 0;
    //initializeGraph(&graph);
    //
    //// ��������� ��� �� �����
    //addCity(&graph, "�����������", 49.4014, 24.3336);
    //addCity(&graph, "����", 49.8525, 24.0515);
    //addCity(&graph, "���", 50.4501, 30.5234);
    //addCity(&graph, "³�����", 49.2331, 28.4682);
    //addCity(&graph, "������", 48.45, 34.9833);
    //addCity(&graph, "�������", 48.0159, 37.8028);
    //addCity(&graph, "�������", 50.2547, 28.6587);
    //addCity(&graph, "�����", 46.4694, 30.7409);
    //addCity(&graph, "�����", 49.9935, 36.2304);
    //addCity(&graph, "��������", 47.8388, 35.1396);
    ///////* 10 */
    //addCity(&graph, "�����-���������", 48.9226, 24.7111);

    // ��������� �����
    printGraph(&graph);


    // ���������� �������� �� ���������
    calculateDistances(&graph);

    printDistanceMatrix(&graph);


    nearestNeighbor(&graph);

    enhancedNearestNeighbor(&graph);

    bruteForce(&graph);

    tspBranchAndBound(&graph);

    return 0;
}

/*================================================*/



    //addCity(&graph, "��������", 48.2921, 25.9354);
    //addCity(&graph, "������������", 49.4225, 26.9871);
    //addCity(&graph, "�������", 49.4444, 32.0597);
    //addCity(&graph, "����", 50.9077, 34.7981);
    //addCity(&graph, "�������", 49.5937, 34.5407);
    //addCity(&graph, "�������������", 48.5044, 32.2605);
    //addCity(&graph, "г���", 50.6196, 26.2514);
    //addCity(&graph, "��������", 49.5535, 25.5948);
    //addCity(&graph, "�������", 48.6208, 22.2879);
    ///* 20 */
    //addCity(&graph, "�����������", 44.6166, 33.5254);
    //addCity(&graph, "ѳ���������", 44.9521, 34.1024);
    //addCity(&graph, "�������", 46.9750, 31.9946);
    //addCity(&graph, "������", 46.6354, 32.6169);
    //addCity(&graph, "�����������", 48.7365, 37.5845);
    /////* 25 */
    //addCity(&graph, "���������-�����.", 50.8484, 24.3232);
    //addCity(&graph, "���'�����-����.", 48.6843, 26.5809);
    //addCity(&graph, "�������������", 48.2921, 37.1835);
    //addCity(&graph, "����'�����", 48.8671, 37.6184);
    //addCity(&graph, "���� ������", 49.7968, 30.1157);
    //addCity(&graph, "�����", 45.3513, 28.8467);
    //addCity(&graph, "�������", 49.7982, 27.5725);
    //addCity(&graph, "������", 51.2184, 24.7067);
    //addCity(&graph, "���������", 50.9584, 28.6333);
    //addCity(&graph, "���������", 46.8389, 35.3765);
    //addCity(&graph, "�������", 50.5934, 32.3875);
    //addCity(&graph, "��������", 48.4422, 22.7111);
    //addCity(&graph, "��������", 49.3492, 23.5149);
    //addCity(&graph, "��������-������.", 46.1832, 30.3498);
    //addCity(&graph, "��������", 49.0383, 28.0973);
    //addCity(&graph, "��������", 50.1792, 30.3083);
    //addCity(&graph, "�������", 50.5200, 30.7936);
    //addCity(&graph, "��������", 49.4419, 24.9347);
    //addCity(&graph, "����������", 48.9226, 38.4424);
    //addCity(&graph, "��������", 48.5434, 25.7264);
    //addCity(&graph, "���������", 46.1175, 32.9054);
    //addCity(&graph, "���������", 47.6485, 34.6367);
    //addCity(&graph, "������", 48.8884, 36.3176);
    //addCity(&graph, "�����", 49.2584, 23.8469);
    //addCity(&graph, "ͳ������", 47.5730, 34.3964);
    /////* 50 */
    //addCity(&graph, "��������", 49.9005, 28.5916);
    //addCity(&graph, "�����", 51.3173, 28.8003);
    //addCity(&graph, "�������-������.", 49.4213, 31.2531);
    //addCity(&graph, "�������", 50.3019, 26.8655);
    //addCity(&graph, "���������", 50.6147, 29.2643);
    //addCity(&graph, "��������-�����.", 50.5956, 27.6160);
    //addCity(&graph, "�����������", 48.0500, 30.8500);
    //addCity(&graph, "��������", 46.6225, 30.4331);
    //addCity(&graph, "��������", 50.3289, 30.3065);
    //addCity(&graph, "����", 49.2305, 31.8837);
    //addCity(&graph, "��������", 49.3492, 23.5149);
    //addCity(&graph, "�����", 50.3896, 25.7459);
    //addCity(&graph, "����������������", 49.7639, 27.2201);
    //addCity(&graph, "������", 49.0167, 25.8000);
    //addCity(&graph, "��������", 47.2145, 32.7660);
    //addCity(&graph, "�������", 49.6496, 25.7778);
    //addCity(&graph, "������", 48.7628, 24.5558);
    //addCity(&graph, "��������", 51.5221, 30.0776);
    //addCity(&graph, "���������", 47.3232, 29.1340);
    //addCity(&graph, "���������", 49.0661, 33.4133);
    //addCity(&graph, "�������", 49.4139, 38.1488);
    //addCity(&graph, "����", 49.2109, 37.2597);
    //addCity(&graph, "�������", 51.2423, 33.2064);
    //addCity(&graph, "������", 50.3052, 30.2930);
    //addCity(&graph, "������", 49.7322, 29.6560);
    ///* 75 */
    //addCity(&graph, "������", 49.2767, 25.9291);
    //addCity(&graph, "ͳ���", 51.0527, 31.8863);
    //addCity(&graph, "�������", 50.5934, 32.3875);
    //addCity(&graph, "�������", 49.3647, 24.6412);
    //addCity(&graph, "���������", 47.1992, 31.3298);
    //addCity(&graph, "����� ���", 47.6997, 32.5235);
    //addCity(&graph, "����������", 50.9625, 28.9239);
    //addCity(&graph, "����", 51.5184, 31.3033);
    //addCity(&graph, "�������", 50.5942, 34.4871);
    //addCity(&graph, "�������", 50.5934, 32.3875);
    //addCity(&graph, "������", 50.3052, 30.2930);
    //addCity(&graph, "�����", 51.5028, 23.8663);
    //addCity(&graph, "�����������", 49.0443, 33.2417);
    //addCity(&graph, "�����", 49.0613, 25.3825);
    //addCity(&graph, "�������", 48.6847, 29.2476);
    //addCity(&graph, "�����", 49.7997, 33.3012);
    //addCity(&graph, "�����������", 47.5607, 31.3341);
    //addCity(&graph, "�������������", 47.7472, 37.5960);
    //addCity(&graph, "��������", 50.2855, 34.0297);
    //addCity(&graph, "������", 51.8669, 33.8856);
    //addCity(&graph, "����'����", 48.7150, 32.6675);
    //addCity(&graph, "��������", 48.6147, 37.5527);
    //addCity(&graph, "�������", 49.3655, 24.1435);
    //addCity(&graph, "������������", 48.7123, 38.4381);
    //addCity(&graph, "�������", 48.6658, 25.9264);
    ///* 100 */
