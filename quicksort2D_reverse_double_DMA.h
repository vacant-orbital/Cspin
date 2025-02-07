#ifndef QUICKSORT_REVERSE_DOUBLE_DMA_H
#define QUICKSORT_REVERSE_DOUBLE_DMA_H

void swap(double *x, double *y);
void quicksort (double** array, int length);
void quicksort_recursion(double** array, int low, int high);
int partition(double** array, int low, int high);

#endif