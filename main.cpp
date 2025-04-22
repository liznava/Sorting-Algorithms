#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

// Generate 10,000 random numbers between 0 and 1000
void generateData(const string& filename, int size) {
    ofstream file(filename);
    srand(time(0));
    for (int i = 0; i < size; ++i) {
        file << rand() % 1001 << "\n";
    }
    file.close();
}

// Load data from file into a vector
vector<int> loadData(const string& filename) {
    vector<int> data;
    ifstream file(filename);
    int number;
    while (file >> number) {
        data.push_back(number);
    }
    file.close();
    return data;
}

// Write sorted data to a file
void writeData(const string& filename, const vector<int>& data) {
    ofstream file(filename);
    for (int num : data) {
        file << num << "\n";
    }
    file.close();
}

// Timer function
double getTime() {
    return static_cast<double>(clock()) / CLOCKS_PER_SEC;
}

// Insertion Sort
void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Counting Sort
void countingSort(vector<int>& arr) {
    const int MAX_VAL = 1000;
    vector<int> count(MAX_VAL + 1, 0);
    for (int i = 0; i < arr.size(); ++i) {
        count[arr[i]]++;
    }
    int idx = 0;
    for (int i = 0; i <= MAX_VAL; ++i) {
        while (count[i]--) {
            arr[idx++] = i;
        }
    }
}

// Merge Sort and Merge function
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// Bubble Sort
void bubbleSort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        for (int j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

// Quick Sort and Partition function
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    int tmp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = tmp;
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    const string dataFile = "data.txt";
    const int dataSize = 10000;

    generateData(dataFile, dataSize);

    vector<int> data;
    double start, end;

    // Insertion Sort
    data = loadData(dataFile);
    start = getTime();
    insertionSort(data);
    end = getTime();
    writeData("result_insertion.txt", data);
    double insertionTime = end - start;

    // Counting Sort
    data = loadData(dataFile);
    start = getTime();
    countingSort(data);
    end = getTime();
    writeData("result_counting.txt", data);
    double countingTime = end - start;

    // Merge Sort
    data = loadData(dataFile);
    start = getTime();
    mergeSort(data, 0, data.size() - 1);
    end = getTime();
    writeData("result_merge.txt", data);
    double mergeTime = end - start;

    // Bubble Sort
    data = loadData(dataFile);
    start = getTime();
    bubbleSort(data);
    end = getTime();
    writeData("result_bubble.txt", data);
    double bubbleTime = end - start;

    // Quick Sort
    data = loadData(dataFile);
    start = getTime();
    quickSort(data, 0, data.size() - 1);
    end = getTime();
    writeData("result_quick.txt", data);
    double quickTime = end - start;

    // Output time comparisons
    cout << "\n=== Sorting Algorithm Runtime Comparison ===\n";
    cout << "Insertion Sort : " << insertionTime << " seconds\n";
    cout << "Counting Sort  : " << countingTime << " seconds\n";
    cout << "Merge Sort     : " << mergeTime << " seconds\n";
    cout << "Bubble Sort    : " << bubbleTime << " seconds\n";
    cout << "Quick Sort     : " << quickTime << " seconds\n";

    return 0;
}
