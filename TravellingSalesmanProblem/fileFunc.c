#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"

void loadCitiesFromFile(Graph* graph, const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf(" \033[0;101m(!) Не вдалося відкрити файл\033[0m\n");
		exit(101);
	}

	char city_name[50];
	double latitude, longitude;

	while (fscanf(file, "%49[^,], %lf, %lf\n", city_name, &latitude, &longitude) == 3)
		addCity(graph, city_name, latitude, longitude);

	fclose(file);
}

//----------------------------------------------------------------------

int getNumberOfCities() {
	int numCities;
	printf("\033[1;37m\n Введіть кількість міст для обробки: \n >> \033[0m");
	scanf("%d", &numCities);
	return numCities;
}

//----------------------------------------------------------------------


int selectDataFile(int argc, char* argv[]) {
	char choice;

	do {
		printf("\n \033[1;37mЧи хочете ви використати власний файл? (y/n): \n >> \033[0m");
		scanf_s(" %c", &choice);

		if (choice == 'y' || choice == 'Y') {
			return -1; // Повертаємо спеціальний індекс для вказівки на власний файл
		}
		else if (choice == 'n' || choice == 'N') {
			int verticesOptions[] = { 5, 10, 13, 15, 20, 50, 75, 100, 125, 150 };
			int numOptions = sizeof(verticesOptions) / sizeof(verticesOptions[0]);

			int numVertices, index = -1;

			do {
				printf("\033[1;37m\n Оберіть кількість пунктів (5, 10, 13, 15, 20, 50, 75, 100, 125, 150): \n >> \033[0m");
				scanf_s("%d", &numVertices);

				for (int i = 0; i < numOptions; i++) {
					if (verticesOptions[i] == numVertices) {
						index = i + 1;
						break;
					}
				}

				if (index == -1) {
					printf("\n \033[0;101m(!) Помилка: Неправильна кількість пунктів.\033[0m\n");
					int c;
					while ((c = getchar()) != '\n' && c != EOF) {}
				}

			} while (index == -1);

			return index;
		}
		else printf(" \033[0;101m(!) Помилка: Неправильний вибір. Спробуйте ще раз.\033[0m\n");
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {}
	} while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

	exit(111);
}

/*

C:\Users\Mykhailo\GumanitariumCenters.txt

*/
