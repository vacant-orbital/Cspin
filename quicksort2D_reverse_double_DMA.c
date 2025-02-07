#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <quicksort2D_reverse_double_DMA.h>

void swap(double *x, double *y){
	double temp = *x;
	*x = *y;
	*y = temp;
}
void quicksort(double** array, int length){
	srand(time(NULL));
	quicksort_recursion(array, 0, length - 1);
}

void quicksort_recursion(double** array, int low, int high){
	if (low < high)
	{
		int pivot_index = partition(array, low, high);
		quicksort_recursion(array, low, pivot_index - 1);
		quicksort_recursion(array, pivot_index + 1, high);
	}
}

int partition(double** array, int low, int high)
{
	int r;
	int pivot_index = low + (rand() % (high - low));
	if (pivot_index != high)
	{
		for (r = 0; r < 2; r++)//(sizeof(array[high])/sizeof(array[high][0]))
		{
			swap(&array[pivot_index][r], &array[high][r]);
		}
	}
	double pivot_value = array[high][0];
	int i = low;
	int j;
	for (j = low; j < high; j++)
	{
		if (array[j][0] >= pivot_value)
		{
			for (r = 0; r < 2; r++)//(sizeof(array[j])/sizeof(array[j][0]))
			{
				swap(&array[i][r], &array[j][r]);
			}
			i++;
		}
	}
	for (r = 0; r < 2; r++)//(sizeof(array[high])/sizeof(array[high][0]))
	{
		swap(&array[i][r], &array[high][r]);
	}
	return i; //return the pivot index
}
