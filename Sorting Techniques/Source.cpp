#include<iostream>
#include<stdio.h>
#include<time.h>
#include<fstream>
#include <string>
using namespace std;

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void heapify(int arr[], int n, int i)
{
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	// If left child is larger than root
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// If right child is larger than largest so far
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// If largest is not root
	if (largest != i) {
		swap(&arr[i], &arr[largest]);

		// Recursively heapify the affected sub-tree
		heapify(arr, n, largest);
	}
}
void heapSort(int arr[], int n)
{
	// Build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap
	for (int i = n - 1; i >= 0; i--) {
		// Move current root to end
		swap(&arr[0], &arr[i]);

		// call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}
void insertion_sort(int* arr, int size)
{
	for (int i = 1; i < size; ++i)
	{
		for (int j = i; j > 0; --j)
		{
			if (arr[j] < arr[j - 1])
				swap(&arr[j], &arr[j - 1]);
			else
				break;
		}
	}
}
void merge(int* arr, int start, int mid, int end)
{
	int i1 = 0, i2 = 0, k = start;
	int n1 = mid - start + 1, n2 = end - mid;

	int* left = (int*)malloc(sizeof(int) * n1);
	int* right = (int*)malloc(sizeof(int) * n2);

	for (int i = 0; i < n1; ++i)
		left[i] = arr[start + i];
	for (int i = 0; i < n2; ++i)
		right[i] = arr[mid + i + 1];

	while (i1 < n1 && i2 < n2)
	{
		if (left[i1] < right[i2])
		{
			arr[k] = left[i1];
			++i1;
		}
		else
		{
			arr[k] = right[i2];
			++i2;
		}
		++k;
	}
	for (; i1 < n1; ++i1, ++k)
		arr[k] = left[i1];
	for (; i2 < n2; ++i2, ++k)
		arr[k] = right[i2];
}
void merge_sort(int* arr, int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		merge_sort(arr, start, mid);
		merge_sort(arr, mid + 1, end);
		merge(arr, start, mid, end);
	}
}

int* read_file(int* arr, int* size,const char*filename)
{
	int lines = 0;
	int i = 0;
	FILE* file;
	int temp;
	file = fopen(filename, "r");
	if (!file) {
		std::cout << "file cannot be readed" << std::endl;
		exit(0);
	}
	while (!feof(file)) {
		fscanf(file, "%d\n", &temp);
		++lines;
	}
	fclose(file);
	arr = (int*)malloc(lines * sizeof(int));
	file = fopen(filename, "r");
	while (!feof(file)) {
		fscanf(file, "%d\n", &arr[i]);
		i++;
	}
	fclose(file);
	*size = lines;
	return arr;
}
int* part_one(int* arr, int size)
{
	cout << "Part One:\n";
	clock_t start = clock();
	long double time = 0.0;
	heapSort(arr, size);
	clock_t end = clock();
	time = (long double)(end - start) / CLOCKS_PER_SEC;
	    for (int i = 0; i < size; ++i)
	        cout << arr[i] << " ";
	printf("\nExecution Time Of Heap Sort Is : %Lf milliseconds\n", time * 1000.0);
	return arr;
}
int* part_two(int* arr, int size)
{
	cout << "\n\nPart Two:\n";
	int* arr2 = (int*)malloc(sizeof(int) * size);
	int* arr3 = (int*)malloc(sizeof(int) * size);
	
	for (int i = 0; i < size; ++i)
	{
		*(arr2 + i) = *(arr + i);
		*(arr3 + i) = *(arr + i);
	}
	long double time = 0.0;
	clock_t start = clock();
	merge_sort(arr, 0, size - 1);
	clock_t end = clock();
	time += (long double)(end - start) / CLOCKS_PER_SEC;
	std::cout << std::endl;
	printf("execution time merge sort: %Lf milliseconds\n", time * 1000.0);

	time = 0.0;
	start = clock();
	heapSort(arr2, size);
	end = clock();
	time += (long double)(end - start) / CLOCKS_PER_SEC;

	printf("execution time of heap sort: %Lf milliseconds\n", time * 1000.0);

	time = 0.0;
	start = clock();
	insertion_sort(arr3, size - 1);
	end = clock();
	time += (long double)(end - start) / CLOCKS_PER_SEC;

	printf("execution time of insertion sort: %Lf milliseconds", time * 1000.0);
	return arr;

}
void conclusion(int* arr1, int* arr2, int size1, int size2)
{
	bool flag = true;
	for (int i = 0; i < size1&& i<size2; ++i)
	{
		if (arr1[i] != arr2[i])

		{
			flag = false;
			break;
		}
	}
	if (flag == true)
		cout << "\nThe Two Arrays Are Identical\n";
	else
		cout << "\nThe Two Arrays Are Different\n";
}
int main()
{
	char filename[10] = "1k.txt";
	char filename2[10] = "10k.txt";
	char filename3[10] = "100k.txt";
	int size1 = 0, size2 = 0;
	int* arr = (int*)malloc(sizeof(int) * 0);
	int* arr3 = (int*)malloc(sizeof(int) * 0);
	arr = read_file(arr, &size1,filename3);
	int* arr2 = (int*)malloc(sizeof(int) * size1);
	for (int i = 0; i < size1; ++i)
		*(arr2 + i) = *(arr + i);
	arr=part_one(arr, size1);
	arr3 = read_file(arr3, &size2,filename3);
	arr2=part_two(arr2, size1);
	arr3=part_two(arr3, size2);
	conclusion(arr, arr3, size1, size2);
	
}


