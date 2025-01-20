#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int randomPartition(int arr[], int low, int high) {
  
    int pivotIndex = low + rand() % (high - low + 1);
    swap(&arr[pivotIndex], &arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
    
        int flag = -(arr[j] <= pivot); 

        i += (flag & 1);

        int vi = arr[i];
        int vj = arr[j];

        arr[i] = (flag & vj) | (~flag & vi);
        arr[j] = (flag & vi) | (~flag & vj);
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


void quickSortIterative(int arr[], int low, int high) {
    int* stack = (int*)malloc((high - low + 1) * sizeof(int)); 
    if (!stack) {
        fprintf(stderr, "Memory allocation for stack failed\n");
        return;
    }

    int top = -1;
    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];

        int pi = randomPartition(arr, low, high);

        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }

    free(stack); 
}

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

    int n = atoi(argv[1]);
    char* file_path = argv[2];

    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));

    if (readCSV(file_path, arr, n)) {
        free(arr);
        return 1;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    quickSortIterative(arr, 0, n - 1); 
    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken = (end.tv_sec - start.tv_sec) + 
                        (end.tv_nsec - start.tv_nsec) / 1e9;

    for (int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }

    fprintf(stderr, "Sorting time: %.16f seconds\n", time_taken);

    free(arr);
    return 0;
}
