/*

Description:
	Given an matrix A of size N*N, consisting of natural numbers (rows are for workers; columns - for engines).
	Each number shows how efficient the worker is on each engine.
	Each worker can get to work only on one engine.

Task:
	Output maximum productivity of workers.

Restrictions:
	Use graphs/trees.

Author: Maxim Uvarov (mix2013)

*/

void InfoInput() {
	int numberOfWorkers, currentNumber;
	printf_s("How many workers(engines) are available at the moment?\n");
	numberOfWorkers = ScanNumber();
	int* array = malloc(sizeof(int) * numberOfWorkers * numberOfWorkers);
	printf_s("Matrix of productivity (rows - workers; columns - engines):\n");
	for (currentNumber = 0; currentNumber < numberOfWorkers; currentNumber++) {
		printf_s("\nInput the productivity of worker %d on %d machines: ", currentNumber + 1, numberOfWorkers);
		for (int j = 0; j < numberOfWorkers; j++) {
			array[currentNumber * numberOfWorkers + j] = ScanNumber();
		}
	}
	for(int i = 0; i < numberOfWorkers; i++)
		for (int j = 0; j < numberOfWorkers; j++)
			printf_s("%d ", array[i * numberOfWorkers + j]);
	WorkerSplit(array, numberOfWorkers);
}

int main() {
	InfoInput();
	return 0;
}