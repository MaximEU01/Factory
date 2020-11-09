#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int Dotry(int i, int* vx, int* vy, int* xy, int* yx, int* array, int size, int* maxRow, int* minCol) {
	if (vx[i] != 0)
		return 0;
	vx[i] = 1;
	for (int j = 0; j < size; j++)
		if (array[i * size + j] - maxRow[i] - minCol[j] == 0)
			vy[j] = 1;
	for (int j = 0; j < size; j++)
		if (array[i * size + j] - maxRow[i] - minCol[j] == 0 && yx[j] == -1) {
			xy[i] = j;
			yx[j] = i;
			return 1;
		}
	for (int j = 0; j < size; j++)
		if (array[i * size + j] - maxRow[i] - minCol[j] == 0 && Dotry(yx[j], vx, vy, xy, yx, array, size, maxRow, minCol)) {
			xy[i] = j;
			yx[j] = i;
			return 1;
		}
	return 0;
}

void WorkerSplit(int *array, int size) {
	int* minCol = malloc(sizeof(int) * size);
	int* maxRow = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		minCol[i] = 0;
		maxRow[i] = 0;
	}
	int maxed = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			maxRow[i] = max(maxRow[i], array[i * size + j]);
			if (maxed < maxRow[i])
				maxed = maxRow[i];
		}
	int* xy = malloc(sizeof(int) * size);
	int* yx = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		xy[i] = -1;
		yx[i] = -1;
	}
	for (int c = 0; c < size;) {
		int* vx = malloc(sizeof(int) * size);
		int* vy = malloc(sizeof(int) * size);
		for (int i = 0; i < size; i++) {
			vx[i] = 0;
			vy[i] = 0;
		}
		int k = 0;
		for (int i = 0; i < size; i++) 
			if (xy[i] == -1 && Dotry(i, vx, vy, xy, yx, array, size, maxRow, minCol) != 0)
				k++;
		c += k;
		if (k == 0) {
			int z = maxed + 1;
			for (int i = 0; i < size; i++)
				if (vx[i] != 0)
					for (int j = 0; j < size; j++)
						if (vy[j] == 0)
							z = min(z, maxRow[i] + minCol[j] - array[i * size + j]);
			for (int i = 0; i < size; i++) {
				if (vx[i] != 0) maxRow[i] -= z;
				if (vy[i] != 0) minCol[i] += z;
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < size; i++)
		ans += array[i * size + xy[i]];
	printf_s("\nMax productivity: %d\n", ans);
	for (int i = 0; i < size; i++)
		printf_s("Worker %d is on engine %d\n", i + 1, xy[i]+1);
}