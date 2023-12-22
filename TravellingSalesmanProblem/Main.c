#define _CRT_SECURE_NO_WARNINGS
#include "algorithms.h"

char filename[256];

void displayBanner();

int main(int argc, char* argv[]) {
    system("chcp 1251");
    char choice;

    do {
        displayBanner();

        int fileIndex = selectDataFile(argc, argv);

        if (fileIndex == -1) {
            char customFile[256];
            printf(" \033[1;37m\n Введіть шлях до вашого файлу: \n >> \033[0m");
            scanf_s("%s", filename, sizeof(filename));
        }
        else {
            strcpy(filename, argv[fileIndex]);
        }

        Graph graph;
        initializeGraph(&graph);
        loadCitiesFromFile(&graph, filename);

        printGraph(&graph);
        calculateDistances(&graph);
        printDistanceMatrix(&graph);

        bruteForce(&graph);

        nearestNeighbor(&graph);

        enhancedNearestNeighbor(&graph);

        insertionTSP(&graph);

        branchAndBound(&graph);

        //runGeneticAlgorithm(&graph);

        line("\033[0;104m \033[0m", 190);
        line("\033[0;103m \033[0m", 190);

        printf("\n \033[0;34mЧи бажаєте продовжити виконання програми? (y/n):\033[0m \n \033[0;34m>> \033[0m");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        scanf_s("%c", &choice);
        do {
            if (choice != "y" && choice != 'Y' && choice != 'n' && choice != 'N') {
                printf(" \033[0;101m(!) Помилка: Неправильний вибір. Спробуйте ще раз.\033[0m\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
                printf("\n \033[0;34mЧи бажаєте продовжити виконання програми? (y/n):\033[0m \n \033[0;34m>> \033[0m");
                scanf_s("%c", &choice);
            }
        } while (choice != "y" && choice != 'Y' && choice != 'n' && choice != 'N');
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

void displayBanner() {
    printf("\n \033[0;104m");  line(" ", 65); printf("\033[0m \033[0;104m  \033[0m"); line2(" ", 61); printf("\033[0;104m  \033[0m");
    printf("\n \033[0;104m  \033[0m\t\t  HUMANITARIAN AID DELIVERY (TSP) \t\t\033[0;103m  \033[0m");
    printf("\n \033[0;103m  \033[0m"); line2(" ", 61); printf("\033[0;103m  \033[0m"); printf("\n \033[0;103m");  line(" ", 65); printf("\033[0m\n");
}