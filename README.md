# Quicksort-branched-vs-unbranched
 This project compares two QuickSort implementations: naïve and branchless. The branchless version reduces branch mispredictions using bitwise operations, improving performance for large datasets. The execution times for both implementations are analyzed, showing that branchless QuickSort is faster for larger inputs

## Task / Problem Statement  
The task is to implement and compare two versions of the QuickSort algorithm: a naïve version prone to branch mispredictions, and an optimized branchless version that eliminates branching using bitwise operations and arithmetic expressions. The goal is to analyze the computational efficiency, time complexity, and execution times of both algorithms.

## Sub-Tasks  
1. **Implement Naïve QuickSort**: Implement the standard QuickSort algorithm with conditional branching.  
2. **Implement Branchless QuickSort**: Optimize the QuickSort algorithm by replacing conditional branches with bitwise operations and arithmetic expressions.  
3. **Performance Measurement**: Measure and compare the execution times for both implementations, excluding file I/O time.  
4. **Analyze Results**: Compare the efficiency of both algorithms, focusing on their scalability and performance on large datasets.

## Implementation Details  
### 1. **Naïve QuickSort Implementation**  
   - **Method**: The naïve version of QuickSort uses conditional checks in the partitioning phase, leading to potential branch mispredictions.  
   - **Random Pivot Selection**: A random pivot is selected, and the array is partitioned based on this pivot.  
   - **Recursive Sorting**: Recursive calls are made to sort the subarrays, with conditional checks (e.g., `if (arr[j] <= pivot)`) that could cause mispredictions.

### 2. **Branchless QuickSort Implementation**  
   - **Method**: The branchless version reduces branching by using bitwise operations and arithmetic expressions instead of conditional statements.  
   - **Optimized Partitioning**: The partitioning logic is performed with conditional moves and bitwise operations instead of branching, avoiding mispredictions.  
   - **Iterative QuickSort**: This version uses stack-based management to avoid recursive overhead.

## Steps to Execute

### **Compiling and Running the Programs**

Both programs must accept two command-line arguments:
1. **Number of values to read**: The size of the in-memory array.
2. **Path to the file**: The location of the input data file.

#### To Compile:
Use a C or C++ compiler to compile the program. For example, using `gcc`:

```bash
gcc -o quicksort naive_quick_sort.c
gcc -o quicksort_branchless branchless_quick_sort.c
```

#### To Run:

##### Naïve QuickSort:
```bash
./quicksort <number_of_elements> <input_file_path>
```

##### Branchless QuickSort:
```bash
./quicksort_branchless <number_of_elements> <input_file_path>
```

## Performance Results

### **Sorting Times**

| Dataset Size (n) | Naïve QuickSort (seconds) | Branchless QuickSort (seconds) |
|------------------|---------------------------|--------------------------------|
| 100              | 0.0000163                 | 0.0000086                     |
| 1,000            | 0.0003997                 | 0.0004009                     |
| 10,000           | 0.0350083                 | 0.0243685                     |
| 100,000          | 3.4027745                 | 2.4197545                     |
| 10,000,000      | 335.446                   | 240.678                       |

### **Observations**
1. **Scaling Behavior**: Both implementations show increasing sorting times with larger datasets, but the branchless QuickSort is consistently faster.
2. **Efficiency at Small Scales**: The execution times for both implementations are similar for small datasets (n = 100), as the overhead from branch mispredictions is negligible.
3. **Branchless Optimization**: For larger datasets, the branchless QuickSort significantly outperforms the naïve version, with a speedup of up to 28.2% for n = 10,000,000.

### **Algorithm Complexity**

| Algorithm               | Best Case      | Average Case   | Worst Case    | Space Complexity |
|-------------------------|----------------|----------------|---------------|------------------|
| Naïve QuickSort         | O(n log n)     | O(n log n)     | O(n²)         | O(log n)         |
| Branchless QuickSort    | O(n log n)     | O(n log n)     | O(n²)         | O(log n)         |

## Conclusion  
The branchless QuickSort implementation is more efficient, especially for large datasets, as it avoids branch mispredictions. While both implementations exhibit the same worst-case time complexity (O(n²)), the branchless version minimizes CPU inefficiencies and performs better, especially for larger inputs.

## Future Work  
- **Further Optimization**: Explore additional optimizations, such as multi-threading, to further enhance performance for large datasets.  
- **Real-World Data**: Apply both algorithms to more complex datasets, including those with different data distributions, to test scalability.

## References  
- **TPCH Benchmark**: [TPCH Benchmark](http://www.tpc.org/tpch/)
