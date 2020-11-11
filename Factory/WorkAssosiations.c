#include "Main.h"

//Giving work
int GiveWork(int i, int* workerAlternate, int* engineAlternate, int* workerToEngine, int* engineToWorker, int* array,
			int size, int* maxWorkerProductivity, int* minEngineProductivity) {
	//Check if GiveWork(...) was analyzing the worker before
	if (workerAlternate[i] != 0)
		return 0;
	workerAlternate[i] = 1;
	//Check if worker can work on different engines with specified productivity
	for (int curEngine = 0; curEngine < size; curEngine++)
		if (array[i * size + curEngine] - maxWorkerProductivity[i] - minEngineProductivity[curEngine] == 0)
			engineAlternate[curEngine] = 1;
	//Attempt to give work
	for (int curEngine = 0; curEngine < size; curEngine++)
		if (array[i * size + curEngine] - maxWorkerProductivity[i] - minEngineProductivity[curEngine] == 0 &&
				engineToWorker[curEngine] == -1) {
			//If the place is 'empty'
			workerToEngine[i] = curEngine;
			engineToWorker[curEngine] = i;
			return 1;
		}
	//If the place is occupied
	for (int curEngine = 0; curEngine < size; curEngine++)
		//Trying to free the other worker from our interesting engine
		if (array[i * size + curEngine] - maxWorkerProductivity[i] - minEngineProductivity[curEngine] == 0 &&
				GiveWork(engineToWorker[curEngine], workerAlternate, engineAlternate, workerToEngine, engineToWorker, array, size,
				maxWorkerProductivity, minEngineProductivity)) {
			//Engine is free, worker is happy
			workerToEngine[i] = curEngine;
			engineToWorker[curEngine] = i;
			return 1;
		}
	//No luck freeing up the place
	return 0;
}

void WorkerSplit(int *array, int size) {
	int* minEngineProductivity = malloc(sizeof(int) * size); //Min difference
	int* maxWorkerProductivity = malloc(sizeof(int) * size); //Max Worker Productivity
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
		workerToEngine[curWorker] = -1; //Pair-link to an engine
		engineToWorker[curWorker] = -1; //Pair-link to a worker
	}
	for (int c = 0; c < size;) {
		int* workerAlternate = malloc(sizeof(int) * size);
		int* engineAlternate = malloc(sizeof(int) * size);
		for (int curWorker = 0; curWorker < size; curWorker++) {
			workerAlternate[curWorker] = 0; //Alternate tree (connection from a worker)
			engineAlternate[curWorker] = 0; //Alternate tree (connection from an engine)
		}
		int k = 0;
		//Check for 'waiting' worker
		for (int curWorker = 0; curWorker < size; curWorker++) 
			if (workerToEngine[curWorker] == -1 && GiveWork(curWorker, workerAlternate, engineAlternate, workerToEngine,
					engineToWorker, array, size, maxWorkerProductivity, minEngineProductivity) != 0)
				k++;
		c += k;
		//If nobody gets their working place
		if (k == 0) {
			for (int curWorker = 0; curWorker < size; curWorker++)
				//Check if the worker is in the Tree
				if (workerAlternate[curWorker] != 0)
					for (int curEngine = 0; curEngine < size; curEngine++)
						//Check if the engine is not in the Tree
						if (engineAlternate[curEngine] == 0)
							//Calculating difference between the Worker Productivity and Free Engine Productivity
							maxOfArray = min(maxOfArray, maxWorkerProductivity[curWorker] +
									minEngineProductivity[curEngine] - array[curWorker * size + curEngine]);
			for (int curWorker = 0; curWorker < size; curWorker++) {
				//Check if the worker is in the Tree
				if (workerAlternate[curWorker] != 0)
					//Reduce the Worker Productivity value
					maxWorkerProductivity[curWorker] -= maxOfArray;
				//Check if the engine is in the Tree
				if (engineAlternate[curWorker] != 0)
					//Increase difference
					minEngineProductivity[curWorker] += maxOfArray;
			}
		}
		//Resetting the Tree
		free(workerAlternate);
		free(engineAlternate);
	}

	//Outputting answer
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