#define MINIM 1
#define MAXED 9

void InfoInput() {
	int numberOfWorkers = 5, currentNumber;
	int* array = malloc(sizeof(int) * numberOfWorkers * numberOfWorkers);
	printf_s("Matrix of productivity (rows - workers; columns - engines):");
	for (currentNumber = 0; currentNumber < numberOfWorkers * numberOfWorkers; currentNumber++) {
		array[currentNumber] = rand() % (MAXED - MINIM + 1) + MINIM;
		if (currentNumber % numberOfWorkers == 0)
			printf_s("\n");
		printf_s("%d ", array[currentNumber]);
	}
	WorkerSplit(array, numberOfWorkers);
}

int main() {
	InfoInput();
	return 0;
}