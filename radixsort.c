#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Utility function to get the maximum value in an array
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Counting sort for Radix Sort (sorting by digit represented by exp)
void countingSort(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int)); // Output array
    int count[10] = {0};

    // Count occurrences of digits in exp place
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // Transform count array to have positions of each digit in output
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy sorted numbers back to the original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(output);
}

// Radix Sort
void radixSort(int arr[], int n) {
    int max = getMax(arr, n); // Find the maximum number to know the number of digits

    // Perform counting sort for each digit
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);
    }
}

// Function to read integers from a CSV file (one integer per line)
int readCSV(const char* file_path, int* arr, int n) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", file_path);
        return 1;
    }

    int count = 0;
    while (count < n && fscanf(file, "%d", &arr[count]) == 1) {
        count++;
    }

    if (count != n) {
        fprintf(stderr, "Warning: Expected %d integers, but found %d in the file.\n", n, count);
    } else {
        fprintf(stderr, "Successfully read %d integers from the file.\n", count);
    }

    fclose(file);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_integers> <file_path>\n", argv[0]);
        return 1;
    }

    // Parse command-line arguments
    int n = atoi(argv[1]);
    char* file_path = argv[2];

    // Allocate memory for the array
    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Read integers from the CSV file
    if (readCSV(file_path, arr, n)) {
        free(arr);
        return 1;
    }

    // Measure sorting time
    clock_t start = clock();
    radixSort(arr, n);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Output the sorted array
    for (int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }

    // Print the sorting time
    fprintf(stderr, "Sorting time: %.6f seconds\n", time_taken);

    // Clean up
    free(arr);
    return 0;
}
