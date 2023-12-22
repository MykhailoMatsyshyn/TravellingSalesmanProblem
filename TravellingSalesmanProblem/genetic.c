#include "graph.h"

/*******************************************************************************************************************/

// Функція для створення копії маршруту
void copyRoute(int* source, int* destination, int numCities) {
	for (int i = 0; i < numCities; i++) {
		destination[i] = source[i];
	}
}

// Функція для генерації випадкового маршруту
void shuffleRoute(int* route, int numCities) {
	for (int i = 1; i < numCities - 1; i++) {
		int j = rand() % (numCities - 1) + 1; // Зміна місцями елементів, крім першого
		int temp = route[i];
		route[i] = route[j];
		route[j] = temp;
	}
}

// Функція для перевірки чи маршрут унікальний
int isUniqueRoute(int** population, int populationSize, int* route, int numCities) {
	for (int i = 0; i < populationSize; i++) {
		if (population[i] == NULL) continue; // Пропустити незаповнені маршрути

		int isUnique = 1;
		for (int j = 0; j < numCities; j++) {
			if (population[i][j] != route[j]) {
				isUnique = 0;
				break;
			}
		}

		if (isUnique) {
			return 0; // Маршрут не унікальний
		}
	}
	return 1; // Маршрут унікальний
}

// Функція ініціалізації популяції
void initializePopulation(Graph* graph, int populationSize, int*** population) {
	// Алокація пам'яті для популяції
	*population = (int**)malloc(populationSize * sizeof(int*));

	// Створення базового маршруту
	int* baseRoute = (int*)malloc(graph->numCities * sizeof(int));
	for (int i = 0; i < graph->numCities; i++) {
		baseRoute[i] = i; // Простий маршрут від 0 до numCities - 1
	}

	// Встановлення першого маршруту як 0, 1, 2, 3, 4...
	(*population)[0] = (int*)malloc(graph->numCities * sizeof(int));
	copyRoute(baseRoute, (*population)[0], graph->numCities);

	// Вивід першого маршруту для перевірки
	printf(" Маршрут   0: ");
	for (int j = 0; j < graph->numCities; j++) {
		printf("%d ", (*population)[0][j]);
	}
	printf("\n");

	// Генерація решти популяції з випадковими маршрутами
	for (int i = 1; i < populationSize; i++) {
		do {
			shuffleRoute(baseRoute, graph->numCities);
		} while (!isUniqueRoute(*population, i, baseRoute, graph->numCities));

		(*population)[i] = (int*)malloc(graph->numCities * sizeof(int));
		copyRoute(baseRoute, (*population)[i], graph->numCities);

		// Вивід маршруту для перевірки
		printf(" Маршрут %3d: ", i);
		for (int j = 0; j < graph->numCities; j++) {
			printf("%d ", (*population)[i][j]);
		}
		printf("\n");
	}

	// Звільнення пам'яті базового маршруту
	free(baseRoute);
}

/*******************************************************************************************************************/


// Функція для обчислення довжини маршруту
double calculateRouteDistance(Graph* graph, int* route) {
	double distance = 0.0;
	for (int i = 0; i < graph->numCities - 1; i++) {
		distance += graph->adjacency_matrix[route[i]][route[i + 1]];
	}
	// Додавання відстані для повернення до початкової точки
	distance += graph->adjacency_matrix[route[graph->numCities - 1]][route[0]];
	return distance;
}

// Функція для обчислення пристосування кожного маршруту
void calculateFitness(Graph* graph, int** population, int populationSize, double* fitness) {
	printf("\n Пристосування:\n");
	for (int i = 0; i < populationSize; i++) {
		fitness[i] = calculateRouteDistance(graph, population[i]);

		// Виведення результату для перевірки
		printf(" %d: %f\n", i, fitness[i]);
	}
	printf("\n");
}

/*******************************************************************************************************************/

// Функція для вибору батьківських особин
void selectParents(int** population, int populationSize, double* fitness, int** parents, int numCities) {
	int parentIndex1, parentIndex2;

	do {
		parentIndex1 = rand() % populationSize;
		parentIndex2 = rand() % populationSize;
	} while (parentIndex1 == parentIndex2); // Переконатися, що індекси різні

	// Копіювання батьківських маршрутів
	for (int j = 0; j < numCities; j++) {
		parents[0][j] = population[parentIndex1][j];
		parents[1][j] = population[parentIndex2][j];
	}

	// Виведення інформації про вибрані особи
	printf(" Батьківська особа 1: \n   Фітнес = %f, \n   Маршрут: ", fitness[parentIndex1]);
	for (int j = 0; j < numCities; j++) {
		printf("%d ", parents[0][j]);
	}
	printf("\n");

	printf("\n Батьківська особа 2: \n   Фітнес = %f, \n   Маршрут: ", fitness[parentIndex2]);
	for (int j = 0; j < numCities; j++) {
		printf("%d ", parents[1][j]);
	}
	printf("\n");
}

/*******************************************************************************************************************/

// Одноточковий кросовер
void crossover(int* parent1, int* parent2, int* offspring, int numCities, int crossoverPoint) {
	printf("   Точка розриву: %d\n", crossoverPoint);

	// Масив для відстеження, які гени вже присутні в нащадку
	int* geneExists = (int*)malloc(numCities * sizeof(int));
	for (int i = 0; i < numCities; i++) {
		geneExists[i] = 0;
	}

	// Копіювання генів до точки розриву з першого батька
	for (int i = 0; i < crossoverPoint; i++) {
		offspring[i] = parent1[i];
		geneExists[parent1[i]] = 1;
	}

	// Копіювання генів після точки розриву з другого батька
	int index = crossoverPoint;
	for (int i = crossoverPoint; i < numCities; i++) {
		if (!geneExists[parent2[i]]) {
			offspring[index++] = parent2[i];
			geneExists[parent2[i]] = 1;
		}
	}

	// Додавання решти генів з першого батька, якщо є вільні місця
	for (int i = crossoverPoint; i < numCities && index < numCities; i++) {
		if (!geneExists[parent1[i]]) {
			offspring[index++] = parent1[i];
		}
	}

	// Виведення результуючого нащадка
	printf("   Нащадок: ");
	for (int i = 0; i < numCities; i++) {
		printf("%d ", offspring[i]);
	}
	puts("\n");

	// Звільнення виділеної пам'яті для масиву geneExists
	free(geneExists);
}

/*******************************************************************************************************************/

// Мутація з випадковим обміном генів
void mutate(int* offspring, int numCities) {
	int i, j;
	do {
		i = rand() % (numCities - 1) + 1;
		j = rand() % (numCities - 1) + 1;
	} while (i == j); // Перевірка на однаковість i та j

	// Міняємо місцями гени i та j
	int temp = offspring[i];
	offspring[i] = offspring[j];
	offspring[j] = temp;
}

/*******************************************************************************************************************/

// Структура, що містить маршрут та фітнес
typedef struct {
	int* route;
	double fitness;
} RouteWithFitness;

// Функція порівняння для сортування за фітнесом
int compareFitness(const void* a, const void* b) {
	double fitnessA = ((RouteWithFitness*)a)->fitness;
	double fitnessB = ((RouteWithFitness*)b)->fitness;
	if (fitnessA < fitnessB) return -1;
	if (fitnessA > fitnessB) return 1;
	return 0;
}

// У функції formNewGeneration використовуємо структури для сортування
void formNewGeneration(int*** population, int** offspring, int populationSize, int numOffspring, double* fitness, Graph* graph) {
	// Створюємо масив структур RouteWithFitness
	RouteWithFitness* routesWithFitness = (RouteWithFitness*)malloc(populationSize * sizeof(RouteWithFitness));
	for (int i = 0; i < populationSize; i++) {
		routesWithFitness[i].route = (*population)[i];
		routesWithFitness[i].fitness = fitness[i];
	}

	// Сортуємо масив за фітнесом
	qsort(routesWithFitness, populationSize, sizeof(RouteWithFitness), compareFitness);

	// Виводимо відсортовану популяцію та фітнес
	printf(" Популяція після сортування:\n\n");
	for (int i = 0; i < populationSize; i++) {
		printf("  Маршрут %.3d: ", i);
		for (int j = 0; j < graph->numCities; j++) {
			printf("%d ", routesWithFitness[i].route[j]);
		}
		printf("    Фітнес: %.2lf\n", routesWithFitness[i].fitness);
	}

	// Видалення попередньої популяції
	for (int i = 0; i < populationSize; i++) {
		free((*population)[i]);
	}
	free(*population);

	// Оновлення популяції з новими маршрутами
	*population = (int**)malloc(populationSize * sizeof(int*));
	for (int i = 0; i < populationSize; i++) {
		// Виділення пам'яті для нового маршруту
		(*population)[i] = (int*)malloc(graph->numCities * sizeof(int));

		// Копіювання значень нового маршруту
		for (int j = 0; j < graph->numCities; j++) {
			(*population)[i][j] = routesWithFitness[i].route[j];
		}
	}

	//// Звільнюємо тимчасовий масив структур
	//free(routesWithFitness);

	//// Заміна нащадків
	//for (int i = 0; i < numOffspring; i++) {
	//	int replaceIndex = rand() % populationSize;
	//	free((*population)[replaceIndex]);
	//	(*population)[replaceIndex] = offspring[i];
	//}

	// Вивід маршруту для перевірки
	for (int i = 0; i < populationSize; i++) {
		printf(" Маршрут %3d: ", i);
		for (int j = 0; j < graph->numCities; j++) {
			printf("%d ", (*population)[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < populationSize; i++) {
		printf("Фітнес елементу %d: %.2lf\n", i, fitness[i]);
	}

}

/*******************************************************************************************************************/

// Основна функція генетичного алгоритму
void geneticAlgorithm(Graph* graph, int populationSize, int numGenerations, int mutationRate) {
	srand(time(NULL));

	int** population;
	double* fitness = (double*)malloc(populationSize * sizeof(double));
	int** parents = (int**)malloc(2 * sizeof(int*)); // Для двох батьківських особин
	for (int i = 0; i < 2; i++) {
		parents[i] = (int*)malloc(graph->numCities * sizeof(int));
	}
	int** offspring = (int**)malloc(2 * sizeof(int*)); // Два нащадки для кожного схрещування

	// Ініціалізація популяції
	initializePopulation(graph, populationSize, &population);

	for (int gen = 0; gen < numGenerations; gen++) {
		// Обчислення пристосування для кожного маршруту
		calculateFitness(graph, population, populationSize, fitness);

		// Вибір батьківських особин
		selectParents(population, populationSize, fitness, parents, graph->numCities);

		printf("\n === Процес схрещування генів ===\n\n");
		int crossoverPoint = rand() % (graph->numCities - 1) + 1;

		// Створення нащадків
		for (int i = 0; i < 2; i++) {
			offspring[i] = (int*)malloc(graph->numCities * sizeof(int));

			printf(" - Формування %s нащадка:\n", i == 0 ? "першого" : "другого");
			if (i == 0)
				crossover(parents[0], parents[1], offspring[i], graph->numCities, crossoverPoint);
			else
				crossover(parents[1], parents[0], offspring[i], graph->numCities, crossoverPoint);
		}

		/************************************************************/

		printf("\n === Процес мутації генів ===\n\n");

		// Мутація першого нащадка
		printf(" - Мутація першого нащадка:\n");

		printf("\n   Ймовірність мутації: %d%%\n", mutationRate);

		if (rand() % 100 < mutationRate) {
			// Мутація відбувається
			printf("   Мутація відбувається:\n");

			printf("     Нащадок до мутації: ");
			for (int i = 0; i < graph->numCities; i++) {
				printf("%d ", offspring[0][i]);
			}
			printf("\n");

			mutate(offspring[0], graph->numCities);
			printf("     Нащадок після мутації: ");
			for (int i = 0; i < graph->numCities; i++) {
				printf("%d ", offspring[0][i]);
			}
			printf("\n");
		}
		else {
			printf("   Мутація не відбувається.\n");
		}

		// Мутація другого нащадка
		printf("\n - Мутація другого нащадка:\n");

		printf("\n   Ймовірність мутації: %d%%\n", mutationRate);

		if (rand() % 100 < mutationRate) {
			// Мутація відбувається
			printf("   Мутація відбувається:\n");

			printf("     Нащадок до мутації: ");
			for (int i = 0; i < graph->numCities; i++) {
				printf("%d ", offspring[1][i]);
			}
			printf("\n");

			mutate(offspring[1], graph->numCities);
			printf("     Нащадок після мутації: ");
			for (int i = 0; i < graph->numCities; i++) {
				printf("%d ", offspring[1][i]);
			}
			printf("\n");
		}
		else {
			printf("   Мутація не відбувається.\n");
		}

		/************************************************************/

		printf("\n === Процес формування нового покоління ===\n\n");

		// Формування нового покоління
		formNewGeneration(&population, offspring, populationSize, 2, fitness, graph);

		printf("\n >>>>> Покоління %d сформовано <<<<<\n", gen + 1);
	}

	//// Очищення пам'яті
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

	// Встановлення параметрів залежно від кількості вершин
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
	else { // Для більших графів
		populationSize = 300;
		numGenerations = 1500;
		mutationRate = 50;
	}

	// Виклик функції генетичного алгоритму з відповідними параметрами
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
//    // Очищення маршруту нащадка і заповнення його випадковими значеннями
//    for (int i = 0; i < n; i++) {
//        offspring->cities[i] = -1;
//    }
//
//    // Генерація точки розриву
//    int breakpoint = rand() % n;
//
//    // Копіювання частини генів першого батька до точки розриву
//    for (int i = 0; i < breakpoint; i++) {
//        offspring->cities[i] = parent1->cities[i];
//    }
//
//    // Доповнення маршруту генами другого батька, які ще не присутні в маршруті нащадка
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
//            // Знаходження наступної вільної позиції в маршруті нащадка
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
//    // Визначення, чи відбудеться мутація
//    if ((double)rand() / RAND_MAX < mutationRate) {
//        // Вибір двох випадкових позицій для обміну
//        int idx1 = rand() % n;
//        int idx2 = rand() % n;
//
//        // Переконуємося, що idx1 і idx2 різні
//        while (idx1 == idx2) {
//            idx2 = rand() % n;
//        }
//
//        // Обмін місцями двох генів
//        int temp = individual->cities[idx1];
//        individual->cities[idx1] = individual->cities[idx2];
//        individual->cities[idx2] = temp;
//    }
//}
//
//void selectBest(Path* population, Path* newPopulation, int populationSize) {
//    // Копіюємо половину найкращих особин до нової популяції
//    for (int i = 0; i < populationSize / 2; i++) {
//        int bestIdx = i;
//        for (int j = i + 1; j < populationSize; j++) {
//            if (population[j].fitness < population[bestIdx].fitness) {
//                bestIdx = j;
//            }
//        }
//        newPopulation[i] = population[bestIdx];
//
//        // Переміщаємо вибрану найкращу особину в кінець розглянутої частини масиву,
//        // щоб вона не брала участі в наступній ітерації вибору
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
//        // Відбір кращих особин
//        Path* newPopulation = malloc(populationSize * sizeof(Path));
//        selectBest(population, newPopulation, populationSize);
//
//
//        Path offspring1, offspring2;
//        initializePath(&offspring1, graph->numCities);
//        initializePath(&offspring2, graph->numCities);
//
//        // Скрещування та мутація
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
//        // Оновлення популяції
//        for (int i = 0; i < populationSize; i++) {
//            free(population[i].cities);
//            population[i] = newPopulation[i];
//        }
//        free(newPopulation);
//    }
//
//    // Знаходження найкращого рішення
//    Path bestPath = population[0];
//    for (int i = 1; i < populationSize; i++) {
//        if (population[i].fitness < bestPath.fitness) {
//            bestPath = population[i];
//        }
//    }
//
//    printf("Найкращий маршрут: ");
//    for (int i = 0; i < bestPath.numCities; i++) {
//        printf("%d ", bestPath.cities[i]);
//    }
//    printf("\nДовжина маршруту: %f\n", bestPath.fitness);
//
//    // Очищення пам'яті
//    for (int i = 0; i < populationSize; i++) {
//        free(population[i].cities);
//    }
//    free(population);
//}
