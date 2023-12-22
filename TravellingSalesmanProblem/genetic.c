#include "graph.h"

/*******************************************************************************************************************/

// ������� ��� ��������� ��ﳿ ��������
void copyRoute(int* source, int* destination, int numCities) {
	for (int i = 0; i < numCities; i++) {
		destination[i] = source[i];
	}
}

// ������� ��� ��������� ����������� ��������
void shuffleRoute(int* route, int numCities) {
	for (int i = 1; i < numCities - 1; i++) {
		int j = rand() % (numCities - 1) + 1; // ���� ������ ��������, ��� �������
		int temp = route[i];
		route[i] = route[j];
		route[j] = temp;
	}
}

// ������� ��� �������� �� ������� ���������
int isUniqueRoute(int** population, int populationSize, int* route, int numCities) {
	for (int i = 0; i < populationSize; i++) {
		if (population[i] == NULL) continue; // ���������� ���������� ��������

		int isUnique = 1;
		for (int j = 0; j < numCities; j++) {
			if (population[i][j] != route[j]) {
				isUnique = 0;
				break;
			}
		}

		if (isUnique) {
			return 0; // ������� �� ���������
		}
	}
	return 1; // ������� ���������
}

// ������� ����������� ���������
void initializePopulation(Graph* graph, int populationSize, int*** population) {
	// �������� ���'�� ��� ���������
	*population = (int**)malloc(populationSize * sizeof(int*));

	// ��������� �������� ��������
	int* baseRoute = (int*)malloc(graph->numCities * sizeof(int));
	for (int i = 0; i < graph->numCities; i++) {
		baseRoute[i] = i; // ������� ������� �� 0 �� numCities - 1
	}

	// ������������ ������� �������� �� 0, 1, 2, 3, 4...
	(*population)[0] = (int*)malloc(graph->numCities * sizeof(int));
	copyRoute(baseRoute, (*population)[0], graph->numCities);

	// ���� ������� �������� ��� ��������
	printf(" �������   0: ");
	for (int j = 0; j < graph->numCities; j++) {
		printf("%d ", (*population)[0][j]);
	}
	printf("\n");

	// ��������� ����� ��������� � ����������� ����������
	for (int i = 1; i < populationSize; i++) {
		do {
			shuffleRoute(baseRoute, graph->numCities);
		} while (!isUniqueRoute(*population, i, baseRoute, graph->numCities));

		(*population)[i] = (int*)malloc(graph->numCities * sizeof(int));
		copyRoute(baseRoute, (*population)[i], graph->numCities);

		// ���� �������� ��� ��������
		printf(" ������� %3d: ", i);
		for (int j = 0; j < graph->numCities; j++) {
			printf("%d ", (*population)[i][j]);
		}
		printf("\n");
	}

	// ��������� ���'�� �������� ��������
	free(baseRoute);
}

/*******************************************************************************************************************/


// ������� ��� ���������� ������� ��������
double calculateRouteDistance(Graph* graph, int* route) {
	double distance = 0.0;
	for (int i = 0; i < graph->numCities - 1; i++) {
		distance += graph->adjacency_matrix[route[i]][route[i + 1]];
	}
	// ��������� ������ ��� ���������� �� ��������� �����
	distance += graph->adjacency_matrix[route[graph->numCities - 1]][route[0]];
	return distance;
}

// ������� ��� ���������� ������������� ������� ��������
void calculateFitness(Graph* graph, int** population, int populationSize, double* fitness) {
	printf("\n �������������:\n");
	for (int i = 0; i < populationSize; i++) {
		fitness[i] = calculateRouteDistance(graph, population[i]);

		// ��������� ���������� ��� ��������
		printf(" %d: %f\n", i, fitness[i]);
	}
	printf("\n");
}

/*******************************************************************************************************************/

// ������� ��� ������ ����������� ������
void selectParents(int** population, int populationSize, double* fitness, int** parents, int numCities) {
	int parentIndex1, parentIndex2;

	do {
		parentIndex1 = rand() % populationSize;
		parentIndex2 = rand() % populationSize;
	} while (parentIndex1 == parentIndex2); // ������������, �� ������� ���

	// ��������� ����������� ��������
	for (int j = 0; j < numCities; j++) {
		parents[0][j] = population[parentIndex1][j];
		parents[1][j] = population[parentIndex2][j];
	}

	// ��������� ���������� ��� ������ �����
	printf(" ���������� ����� 1: \n   Գ���� = %f, \n   �������: ", fitness[parentIndex1]);
	for (int j = 0; j < numCities; j++) {
		printf("%d ", parents[0][j]);
	}
	printf("\n");

	printf("\n ���������� ����� 2: \n   Գ���� = %f, \n   �������: ", fitness[parentIndex2]);
	for (int j = 0; j < numCities; j++) {
		printf("%d ", parents[1][j]);
	}
	printf("\n");
}

/*******************************************************************************************************************/

// ������������ ��������
void crossover(int* parent1, int* parent2, int* offspring, int numCities, int crossoverPoint) {
	printf("   ����� �������: %d\n", crossoverPoint);

	// ����� ��� ����������, �� ���� ��� ������� � �������
	int* geneExists = (int*)malloc(numCities * sizeof(int));
	for (int i = 0; i < numCities; i++) {
		geneExists[i] = 0;
	}

	// ��������� ���� �� ����� ������� � ������� ������
	for (int i = 0; i < crossoverPoint; i++) {
		offspring[i] = parent1[i];
		geneExists[parent1[i]] = 1;
	}

	// ��������� ���� ���� ����� ������� � ������� ������
	int index = crossoverPoint;
	for (int i = crossoverPoint; i < numCities; i++) {
		if (!geneExists[parent2[i]]) {
			offspring[index++] = parent2[i];
			geneExists[parent2[i]] = 1;
		}
	}

	// ��������� ����� ���� � ������� ������, ���� � ���� ����
	for (int i = crossoverPoint; i < numCities && index < numCities; i++) {
		if (!geneExists[parent1[i]]) {
			offspring[index++] = parent1[i];
		}
	}

	// ��������� ������������� �������
	printf("   �������: ");
	for (int i = 0; i < numCities; i++) {
		printf("%d ", offspring[i]);
	}
	puts("\n");

	// ��������� ������� ���'�� ��� ������ geneExists
	free(geneExists);
}

/*******************************************************************************************************************/

// ������� � ���������� ������ ����
void mutate(int* offspring, int numCities) {
	int i, j;
	do {
		i = rand() % (numCities - 1) + 1;
		j = rand() % (numCities - 1) + 1;
	} while (i == j); // �������� �� ���������� i �� j

	// ̳����� ������ ���� i �� j
	int temp = offspring[i];
	offspring[i] = offspring[j];
	offspring[j] = temp;
}

/*******************************************************************************************************************/

// ���������, �� ������ ������� �� ������
typedef struct {
	int* route;
	double fitness;
} RouteWithFitness;

// ������� ��������� ��� ���������� �� ��������
int compareFitness(const void* a, const void* b) {
	double fitnessA = ((RouteWithFitness*)a)->fitness;
	double fitnessB = ((RouteWithFitness*)b)->fitness;
	if (fitnessA < fitnessB) return -1;
	if (fitnessA > fitnessB) return 1;
	return 0;
}

// � ������� formNewGeneration ������������� ��������� ��� ����������
void formNewGeneration(int*** population, int** offspring, int populationSize, int numOffspring, double* fitness, Graph* graph) {
	// ��������� ����� �������� RouteWithFitness
	RouteWithFitness* routesWithFitness = (RouteWithFitness*)malloc(populationSize * sizeof(RouteWithFitness));
	for (int i = 0; i < populationSize; i++) {
		routesWithFitness[i].route = (*population)[i];
		routesWithFitness[i].fitness = fitness[i];
	}

	// ������� ����� �� ��������
	qsort(routesWithFitness, populationSize, sizeof(RouteWithFitness), compareFitness);

	// �������� ����������� ��������� �� ������
	printf(" ��������� ���� ����������:\n\n");
	for (int i = 0; i < populationSize; i++) {
		printf("  ������� %.3d: ", i);
		for (int j = 0; j < graph->numCities; j++) {
			printf("%d ", routesWithFitness[i].route[j]);
		}
		printf("    Գ����: %.2lf\n", routesWithFitness[i].fitness);
	}

	// ��������� ���������� ���������
	for (int i = 0; i < populationSize; i++) {
		free((*population)[i]);
	}
	free(*population);

	// ��������� ��������� � ������ ����������
	*population = (int**)malloc(populationSize * sizeof(int*));
	for (int i = 0; i < populationSize; i++) {
		// �������� ���'�� ��� ������ ��������
		(*population)[i] = (int*)malloc(graph->numCities * sizeof(int));

		// ��������� ������� ������ ��������
		for (int j = 0; j < graph->numCities; j++) {
			(*population)[i][j] = routesWithFitness[i].route[j];
		}
	}

	//// ��������� ���������� ����� ��������
	//free(routesWithFitness);

	//// ����� �������
	//for (int i = 0; i < numOffspring; i++) {
	//	int replaceIndex = rand() % populationSize;
	//	free((*population)[replaceIndex]);
	//	(*population)[replaceIndex] = offspring[i];
	//}

	// ���� �������� ��� ��������
	for (int i = 0; i < populationSize; i++) {
		printf(" ������� %3d: ", i);
		for (int j = 0; j < graph->numCities; j++) {
			printf("%d ", (*population)[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < populationSize; i++) {
		printf("Գ���� �������� %d: %.2lf\n", i, fitness[i]);
	}

}

/*******************************************************************************************************************/

// ������� ������� ����������� ���������
void geneticAlgorithm(Graph* graph, int populationSize, int numGenerations, int mutationRate) {
	srand(time(NULL));

	int** population;
	double* fitness = (double*)malloc(populationSize * sizeof(double));
	int** parents = (int**)malloc(2 * sizeof(int*)); // ��� ���� ����������� ������
	for (int i = 0; i < 2; i++) {
		parents[i] = (int*)malloc(graph->numCities * sizeof(int));
	}
	int** offspring = (int**)malloc(2 * sizeof(int*)); // ��� ������� ��� ������� �����������

	// ����������� ���������
	initializePopulation(graph, populationSize, &population);

	for (int gen = 0; gen < numGenerations; gen++) {
		// ���������� ������������� ��� ������� ��������
		calculateFitness(graph, population, populationSize, fitness);

		// ���� ����������� ������
		selectParents(population, populationSize, fitness, parents, graph->numCities);

		printf("\n === ������ ����������� ���� ===\n\n");
		int crossoverPoint = rand() % (graph->numCities - 1) + 1;

		// ��������� �������
		for (int i = 0; i < 2; i++) {
			offspring[i] = (int*)malloc(graph->numCities * sizeof(int));

			printf(" - ���������� %s �������:\n", i == 0 ? "�������" : "�������");
			if (i == 0)
				crossover(parents[0], parents[1], offspring[i], graph->numCities, crossoverPoint);
			else
				crossover(parents[1], parents[0], offspring[i], graph->numCities, crossoverPoint);
		}

		/************************************************************/

		printf("\n === ������ ������� ���� ===\n\n");

		// ������� ������� �������
		printf(" - ������� ������� �������:\n");

		printf("\n   ��������� �������: %d%%\n", mutationRate);

		if (rand() % 100 < mutationRate) {
			// ������� ����������
			printf("   ������� ����������:\n");

			printf("     ������� �� �������: ");
			for (int i = 0; i < graph->numCities; i++) {
				printf("%d ", offspring[0][i]);
			}
			printf("\n");

			mutate(offspring[0], graph->numCities);
			printf("     ������� ���� �������: ");
			for (int i = 0; i < graph->numCities; i++) {
				printf("%d ", offspring[0][i]);
			}
			printf("\n");
		}
		else {
			printf("   ������� �� ����������.\n");
		}

		// ������� ������� �������
		printf("\n - ������� ������� �������:\n");

		printf("\n   ��������� �������: %d%%\n", mutationRate);

		if (rand() % 100 < mutationRate) {
			// ������� ����������
			printf("   ������� ����������:\n");

			printf("     ������� �� �������: ");
			for (int i = 0; i < graph->numCities; i++) {
				printf("%d ", offspring[1][i]);
			}
			printf("\n");

			mutate(offspring[1], graph->numCities);
			printf("     ������� ���� �������: ");
			for (int i = 0; i < graph->numCities; i++) {
				printf("%d ", offspring[1][i]);
			}
			printf("\n");
		}
		else {
			printf("   ������� �� ����������.\n");
		}

		/************************************************************/

		printf("\n === ������ ���������� ������ �������� ===\n\n");

		// ���������� ������ ��������
		formNewGeneration(&population, offspring, populationSize, 2, fitness, graph);

		printf("\n >>>>> �������� %d ���������� <<<<<\n", gen + 1);
	}

	//// �������� ���'��
	//for (int i = 0; i < populationSize; i++) {
	//	free(population[i]);
	//}
	//free(population);
	//free(fitness);
	//for (int i = 0; i < 2; i++) {
	//	free(offspring[i]);
	//}
	//free(offspring);
	//free(parents);
}

/*******************************************************************************************************************/

void runGeneticAlgorithm(Graph* graph) {
	int numCities = graph->numCities;
	int populationSize, numGenerations, mutationRate;

	// ������������ ��������� ������� �� ������� ������
	if (numCities <= 5) {
		populationSize = 10;
		numGenerations = 50;
		mutationRate = 50;
	}
	else if (numCities <= 10) {
		populationSize = 20;
		numGenerations = 100;
		mutationRate = 60;
	}
	else if (numCities <= 15) {
		populationSize = 30;
		numGenerations = 200;
		mutationRate = 50;
	}
	else if (numCities <= 20) {
		populationSize = 40;
		numGenerations = 300;
		mutationRate = 50;
	}
	else if (numCities <= 50) {
		populationSize = 100;
		numGenerations = 500;
		mutationRate = 50;
	}
	else if (numCities <= 75) {
		populationSize = 150;
		numGenerations = 750;
		mutationRate = 50;
	}
	else if (numCities <= 100) {
		populationSize = 200;
		numGenerations = 1000;
		mutationRate = 50;
	}
	else if (numCities <= 125) {
		populationSize = 250;
		numGenerations = 1250;
		mutationRate = 50;
	}
	else { // ��� ������ ������
		populationSize = 300;
		numGenerations = 1500;
		mutationRate = 50;
	}

	// ������ ������� ����������� ��������� � ���������� �����������
	geneticAlgorithm(graph, populationSize, numGenerations, mutationRate);
}






































//typedef struct {
//    int* cities;
//    int numCities;
//    double fitness;
//} Path;
//
//void initializePath(Path* path, int numCities) {
//    path->cities = malloc(numCities * sizeof(int));
//    path->numCities = numCities;
//    path->fitness = 0.0;
//    for (int i = 0; i < numCities; i++) {
//        path->cities[i] = i;
//        printf("%d-\n", path->cities[i]);
//    }
//}
//
//void randomizePath(Path* path) {
//    for (int i = 0; i < path->numCities; i++) {
//        int j = rand() % path->numCities;
//        int temp = path->cities[i];
//        path->cities[i] = path->cities[j];
//        path->cities[j] = temp;
//    }
//}
//
//double calculatePathDistance(Path* path, Graph* graph) {
//    double distance = 0.0;
//    for (int i = 0; i < path->numCities - 1; i++) {
//        distance += graph->adjacency_matrix[path->cities[i]][path->cities[i + 1]];
//    }
//    distance += graph->adjacency_matrix[path->cities[path->numCities - 1]][path->cities[0]];
//    return distance;
//}
//
//void evaluateFitness(Path* population, int populationSize, Graph* graph) {
//    for (int i = 0; i < populationSize; i++) {
//        population[i].fitness = calculatePathDistance(&population[i], graph);
//    }
//}
//
//void crossover(Path* parent1, Path* parent2, Path* offspring) {
//    int n = parent1->numCities;
//    printf("%d\n", parent1->numCities);
//
//    // �������� �������� ������� � ���������� ���� ����������� ����������
//    for (int i = 0; i < n; i++) {
//        offspring->cities[i] = -1;
//    }
//
//    // ��������� ����� �������
//    int breakpoint = rand() % n;
//
//    // ��������� ������� ���� ������� ������ �� ����� �������
//    for (int i = 0; i < breakpoint; i++) {
//        offspring->cities[i] = parent1->cities[i];
//    }
//
//    // ���������� �������� ������ ������� ������, �� �� �� ������� � ������� �������
//    for (int i = 0; i < n; i++) {
//        int city = parent2->cities[i];
//        int alreadyExists = 0;
//
//        for (int j = 0; j < breakpoint; j++) {
//            if (offspring->cities[j] == city) {
//                alreadyExists = 1;
//                break;
//            }
//        }
//
//        if (!alreadyExists) {
//            // ����������� �������� ����� ������� � ������� �������
//            for (int j = breakpoint; j < n; j++) {
//                if (offspring->cities[j] == -1) {
//                    offspring->cities[j] = city;
//                    break;
//                }
//            }
//        }
//    }
//}
//
//void mutate(Path* individual, double mutationRate) {
//    int n = individual->numCities;
//
//    // ����������, �� ���������� �������
//    if ((double)rand() / RAND_MAX < mutationRate) {
//        // ���� ���� ���������� ������� ��� �����
//        int idx1 = rand() % n;
//        int idx2 = rand() % n;
//
//        // ������������, �� idx1 � idx2 ���
//        while (idx1 == idx2) {
//            idx2 = rand() % n;
//        }
//
//        // ���� ������ ���� ����
//        int temp = individual->cities[idx1];
//        individual->cities[idx1] = individual->cities[idx2];
//        individual->cities[idx2] = temp;
//    }
//}
//
//void selectBest(Path* population, Path* newPopulation, int populationSize) {
//    // ������� �������� ��������� ������ �� ���� ���������
//    for (int i = 0; i < populationSize / 2; i++) {
//        int bestIdx = i;
//        for (int j = i + 1; j < populationSize; j++) {
//            if (population[j].fitness < population[bestIdx].fitness) {
//                bestIdx = j;
//            }
//        }
//        newPopulation[i] = population[bestIdx];
//
//        // ��������� ������� �������� ������� � ����� ���������� ������� ������,
//        // ��� ���� �� ����� ����� � �������� �������� ������
//        Path temp = population[i];
//        population[i] = population[bestIdx];
//        population[bestIdx] = temp;
//    }
//}
//
//void geneticAlgorithm(Graph* graph, int populationSize, int numGenerations, double mutationRate) {
//    srand(time(NULL));
//
//    Path* population = malloc(populationSize * sizeof(Path));
//    for (int i = 0; i < populationSize; i++) {
//        initializePath(&population[i], graph->numCities);
//        randomizePath(&population[i]);
//    }
//
//    for (int generation = 0; generation < numGenerations; generation++) {
//        evaluateFitness(population, populationSize, graph);
//
//        // ³��� ������ ������
//        Path* newPopulation = malloc(populationSize * sizeof(Path));
//        selectBest(population, newPopulation, populationSize);
//
//
//        Path offspring1, offspring2;
//        initializePath(&offspring1, graph->numCities);
//        initializePath(&offspring2, graph->numCities);
//
//        // ����������� �� �������
//        for (int i = 0; i < populationSize; i += 2) {
//            crossover(&newPopulation[i], &newPopulation[i + 1], &offspring1);
//            crossover(&newPopulation[i + 1], &newPopulation[i], &offspring2);
//
//            mutate(&offspring1, mutationRate);
//            mutate(&offspring2, mutationRate);
//
//            newPopulation[i] = offspring1;
//            newPopulation[i + 1] = offspring2;
//        }
//
//        // ��������� ���������
//        for (int i = 0; i < populationSize; i++) {
//            free(population[i].cities);
//            population[i] = newPopulation[i];
//        }
//        free(newPopulation);
//    }
//
//    // ����������� ���������� ������
//    Path bestPath = population[0];
//    for (int i = 1; i < populationSize; i++) {
//        if (population[i].fitness < bestPath.fitness) {
//            bestPath = population[i];
//        }
//    }
//
//    printf("��������� �������: ");
//    for (int i = 0; i < bestPath.numCities; i++) {
//        printf("%d ", bestPath.cities[i]);
//    }
//    printf("\n������� ��������: %f\n", bestPath.fitness);
//
//    // �������� ���'��
//    for (int i = 0; i < populationSize; i++) {
//        free(population[i].cities);
//    }
//    free(population);
//}
