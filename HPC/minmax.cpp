#include <iostream>
#include <omp.h>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    long long sum = 0;
    double average = 0.0;

    #pragma omp parallel for reduction(min:minVal)
    for (int i = 0; i < n; i++) {
        if (arr[i] < minVal)
            minVal = arr[i];
    }

    #pragma omp parallel for reduction(max:maxVal)
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    average = static_cast<double>(sum) / n;

    cout << "Minimum Value: " << minVal << endl;
    cout << "Maximum Value: " << maxVal << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}
