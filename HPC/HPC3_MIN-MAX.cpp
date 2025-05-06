#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>
#include <climits>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> arr(n);

    // Seed and generate random numbers
    srand(time(0));
    cout << "\nGenerating random array:\n";
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
        cout << arr[i] << " ";
    }
    cout << endl;

    int min_val = INT_MAX;
    int max_val = INT_MIN;
    long long sum = 0;
    double avg = 0.0;

    // MIN
    int min_threads = 0;
    auto start = high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single
        min_threads = omp_get_num_threads();

        #pragma omp for reduction(min : min_val)
        for (int i = 0; i < n; i++) {
            if (arr[i] < min_val)
                min_val = arr[i];
        }
    }
    auto end = high_resolution_clock::now();
    auto min_duration = duration<double, milli>(end - start);
    cout << fixed << setprecision(6);
    cout << "\nMinimum value: " << min_val
         << " (Time taken: " << min_duration.count() << " ms)"
         << " | Threads used: " << min_threads;

    // MAX
    int max_threads = 0;
    start = high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single
        max_threads = omp_get_num_threads();

        #pragma omp for reduction(max : max_val)
        for (int i = 0; i < n; i++) {
            if (arr[i] > max_val)
                max_val = arr[i];
        }
    }
    end = high_resolution_clock::now();
    auto max_duration = duration<double, milli>(end - start);
    cout << "\nMaximum value: " << max_val
         << " (Time taken: " << max_duration.count() << " ms)"
         << " | Threads used: " << max_threads;

    // SUM
    int sum_threads = 0;
    start = high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single
        sum_threads = omp_get_num_threads();

        #pragma omp for reduction(+ : sum)
        for (int i = 0; i < n; i++) {
            sum += arr[i];
        }
    }
    end = high_resolution_clock::now();
    auto sum_duration = duration<double, milli>(end - start);
    cout << "\nSum: " << sum
         << " (Time taken: " << sum_duration.count() << " ms)"
         << " | Threads used: " << sum_threads;

    // AVERAGE
    start = high_resolution_clock::now();
    avg = static_cast<double>(sum) / n;
    end = high_resolution_clock::now();
    auto avg_duration = duration<double, milli>(end - start);
    cout << "\nAverage: " << avg
         << " (Time taken: " << avg_duration.count() << " ms)"
         << " | Threads used: 1 (simple division)\n";

    return 0;
}