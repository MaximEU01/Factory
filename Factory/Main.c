#define MINIM 1
#define MAXED 9

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