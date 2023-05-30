#include <iostream>
#include <omp.h>

void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort_OpenMP(int arr[], int size) {
    if (size <= 1)
        return;

    int mid = size / 2;
    int* left = new int[mid];
    int* right = new int[size - mid];

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 0; i < mid; i++)
                left[i] = arr[i];

            mergeSort_OpenMP(left, mid);
        }

        #pragma omp section
        {
            for (int i = mid; i < size; i++)
                right[i - mid] = arr[i];

            mergeSort_OpenMP(right, size - mid);
        }
    }

    merge(arr, left, mid, right, size - mid);

    delete[] left;
    delete[] right;
}

int main() {
    int size;

    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    int* arr = new int[size];

    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; i++)
        std::cin >> arr[i];

    std::cout << "Original array: ";
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    mergeSort_OpenMP(arr, size);

    std::cout << "Sorted array: ";
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    delete[] arr;

    return 0;
}

