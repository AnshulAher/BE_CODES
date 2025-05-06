#include <iostream>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// Sequential Bubble Sort
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int start = i % 2;
#pragma omp parallel for
        for (int j = start; j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Merge function for Merge Sort
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

// Sequential Merge Sort
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort
void parallelMergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            parallelMergeSort(arr, l, m);
#pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

// Print array
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int *arr = new int[n];
    int *original = new int[n];

    for (int i = 0; i < n; ++i)
    {
        cout << "Enter element: ";
        cin >> arr[i];
        original[i] = arr[i];
    }

    cout << "\nOriginal array: ";
    printArray(arr, n);

    high_resolution_clock::time_point start, end;
    duration<double, milli> duration;

    // Sequential Bubble Sort
    for (int i = 0; i < n; ++i)
        arr[i] = original[i];
    start = high_resolution_clock::now();
    bubbleSort(arr, n);
    end = high_resolution_clock::now();
    duration = end - start;
    cout << "\nSequential Bubble Sorted array: ";
    printArray(arr, n);
    cout << "Time taken: " << duration.count() << " milliseconds\n";

    // Parallel Bubble Sort
    for (int i = 0; i < n; ++i)
        arr[i] = original[i];
    start = high_resolution_clock::now();
    parallelBubbleSort(arr, n);
    end = high_resolution_clock::now();
    duration = end - start;
    cout << "\nParallel Bubble Sorted array: ";
    printArray(arr, n);
    cout << "Time taken: " << duration.count() << " milliseconds\n";

    // Sequential Merge Sort
    for (int i = 0; i < n; ++i)
        arr[i] = original[i];
    start = high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    end = high_resolution_clock::now();
    duration = end - start;
    cout << "\nSequential Merge Sorted array: ";
    printArray(arr, n);
    cout << "Time taken: " << duration.count() << " milliseconds\n";

    // Parallel Merge Sort
    for (int i = 0; i < n; ++i)
        arr[i] = original[i];
    start = high_resolution_clock::now();
#pragma omp parallel
    {
#pragma omp single
        {
            parallelMergeSort(arr, 0, n - 1);
        }
    }
    end = high_resolution_clock::now();
    duration = end - start;
    cout << "\nParallel Merge Sorted array: ";
    printArray(arr, n);
    cout << "Time taken: " << duration.count() << " milliseconds\n";

    delete[] arr;
    delete[] original;

    return 0;
}

 // Bubble Sort:

// Best Case Time Complexity: O(n) (when the array is already sorted)
// Average Case Time Complexity: O(n^2)
// Worst Case Time Complexity: O(n^2) (when the array is sorted in reverse order)
// Space Complexity: O(1)

// Merge Sort:

// Best Case Time Complexity: O(n log n)
// Average Case Time Complexity: O(n log n)
// Worst Case Time Complexity: O(n log n)
// Space Complexity: O(n)

