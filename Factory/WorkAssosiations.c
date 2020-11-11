#include "Main.h"

int Dotry(int curWorker, int* workerAlternate, int* engineAlternate, int* workerToEngine, int* engineToWorker, int* array, int size, int* maxWorkerProductivity,
	int* minEngineProductivity) {
	if (workerAlternate[curWorker] != 0)
		return 0;
	workerAlternate[curWorker] = 1;
	for (int curEngine = 0; curEngine < size; curEngine++)
		if (array[curWorker * size + curEngine] - maxWorkerProductivity[curWorker] - minEngineProductivity[curEngine] == 0)
			engineAlternate[curEngine] = 1;
	for (int curEngine = 0; curEngine < size; curEngine++)
		if (array[curWorker * size + curEngine] - maxWorkerProductivity[curWorker] - minEngineProductivity[curEngine] == 0 && engineToWorker[curEngine] == -1) {
			workerToEngine[curWorker] = curEngine;
			engineToWorker[curEngine] = curWorker;
			return 1;
		}
	for (int curEngine = 0; curEngine < size; curEngine++)
		if (array[curWorker * size + curEngine] - maxWorkerProductivity[curWorker] - minEngineProductivity[curEngine] == 0 && Dotry(engineToWorker[curEngine],
			workerAlternate, engineAlternate, workerToEngine, engineToWorker, array, size, maxWorkerProductivity, minEngineProductivity)) {
			workerToEngine[curWorker] = curEngine;
			engineToWorker[curEngine] = curWorker;
			return 1;
		}
	return 0;
}

void WorkerSplit(int *array, int size) {
	int* minEngineProductivity = malloc(sizeof(int) * size);
	int* maxWorkerProductivity = malloc(sizeof(int) * size); //Max power of a worker
	for (int curWorker = 0; curWorker < size; curWorker++) {
		minEngineProductivity[curWorker] = 0;
		maxWorkerProductivity[curWorker] = 0;
	}
	int maxOfArray = 0;
	for (int curWorker = 0; curWorker < size; curWorker++)
		for (int curEngine = 0; curEngine < size; curEngine++) {
			maxWorkerProductivity[curWorker] = max(maxWorkerProductivity[curWorker], array[curWorker * size + curEngine]);
			if (maxOfArray < maxWorkerProductivity[curWorker])
				maxOfArray = maxWorkerProductivity[curWorker];
		}
	int* workerToEngine = malloc(sizeof(int) * size);
	int* engineToWorker = malloc(sizeof(int) * size);
	for (int curWorker = 0; curWorker < size; curWorker++) {
		workerToEngine[curWorker] = -1; //Link to an engine
		engineToWorker[curWorker] = -1; //Link to a worker
	}
	for (int c = 0; c < size;) {
		int* workerAlternate = malloc(sizeof(int) * size);
		int* engineAlternate = malloc(sizeof(int) * size);
		for (int curWorker = 0; curWorker < size; curWorker++) {
			workerAlternate[curWorker] = 0; 
			engineAlternate[curWorker] = 0; 
		}
		int k = 0;
		for (int curWorker = 0; curWorker < size; curWorker++) 
			if (workerToEngine[curWorker] == -1 && Dotry(curWorker, workerAlternate, engineAlternate, workerToEngine, engineToWorker,
				array, size, maxWorkerProductivity, minEngineProductivity) != 0)
				k++;
		c += k;
		if (k == 0) {
			int maxOfArrayPlus1 = maxOfArray + 1;
			for (int curWorker = 0; curWorker < size; curWorker++)
				if (workerAlternate[curWorker] != 0)
					for (int curEngine = 0; curEngine < size; curEngine++)
						if (engineAlternate[curEngine] == 0)
							maxOfArrayPlus1 = min(maxOfArrayPlus1, maxWorkerProductivity[curWorker] + minEngineProductivity[curEngine]
								- array[curWorker * size + curEngine]);
			for (int curWorker = 0; curWorker < size; curWorker++) {
				if (workerAlternate[curWorker] != 0) maxWorkerProductivity[curWorker] -= maxOfArrayPlus1;
				if (engineAlternate[curWorker] != 0) minEngineProductivity[curWorker] += maxOfArrayPlus1;
			}
		}
		free(workerAlternate);
		free(engineAlternate);
	}

	int maxProductivity = 0;
	for (int curWorker = 0; curWorker < size; curWorker++)
		maxProductivity += array[curWorker * size + workerToEngine[curWorker]];
	printf_s("\nMax productivity: %d\n", maxProductivity);
	for (int curWorker = 0; curWorker < size; curWorker++)
		printf_s("Worker %d is on engine %d\n", curWorker + 1, workerToEngine[curWorker]+1);
	free(array);
	free(minEngineProductivity);
	free(maxWorkerProductivity);
	free(workerToEngine);
	free(engineToWorker);
}