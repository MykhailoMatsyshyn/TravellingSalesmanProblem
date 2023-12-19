#include "algorithms.h"

void displayBanner();

int main(int argc, char* argv[]) {
    system("chcp 1251");

    displayBanner();

    char* filename = argv[selectDataFile(argc, argv)];

    Graph graph;
    initializeGraph(&graph);
    loadCitiesFromFile(&graph, filename);

    printGraph(&graph);
    calculateDistances(&graph);
    printDistanceMatrix(&graph);


    nearestNeighbor(&graph);

    enhancedNearestNeighbor(&graph);

    bruteForce(&graph);

    tspBranchAndBound(&graph);

    return 0;
}

void displayBanner() {
    printf("\n \033[0;104m");  line(" ", 65); printf("\033[0m \033[0;104m  \033[0m"); line2(" ", 61); printf("\033[0;104m  \033[0m");
    printf("\n \033[0;104m  \033[0m\t\t  HUMANITARIAN AID DELIVERY (TSP) \t\t\033[0;103m  \033[0m");
    printf("\n \033[0;103m  \033[0m"); line2(" ", 61); printf("\033[0;103m  \033[0m"); printf("\n \033[0;103m");  line(" ", 65); printf("\033[0m\n");
}