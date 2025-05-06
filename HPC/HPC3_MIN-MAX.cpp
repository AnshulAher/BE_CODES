#include <iostream>
#include <omp.h>
#include <vector>
#include <climits>
#include <cstdlib>
#include <ctime>

using namespace std;

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
    #pragma omp parallel for reduction(min : min_val)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val)
            min_val = arr[i];
    }
    cout << "\nMinimum value: " << min_val;

    // MAX
    #pragma omp parallel for reduction(max : max_val)
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val)
            max_val = arr[i];
    }
    cout << "\nMaximum value: " << max_val;

    // SUM
    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    cout << "\nSum: " << sum;

    // AVERAGE
    avg = static_cast<double>(sum) / n;
    cout << "\nAverage: " << avg << endl;

    return 0;
}
