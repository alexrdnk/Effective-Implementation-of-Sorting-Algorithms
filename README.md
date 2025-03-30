# Sorting Algorithms Performance Comparison

This project implements and compares the performance of various sorting algorithms in C++. The application not only demonstrates the implementation of each algorithm but also measures and records their performance under different conditions.

## Overview

The project focuses on evaluating the efficiency of several well-known sorting algorithms:
- **Insertion Sort**
- **Heap Sort**
- **Shell Sort** (using both Knuth and Hibbard gap sequences)
- **Quick Sort** (with various pivot selection strategies: left, right, middle, and random)

The study examines how these algorithms perform with different types of data (integer and floating point) and initial array configurations (random, sorted ascending, sorted descending, and partially sorted). The performance results are measured in milliseconds and output into a CSV file for further analysis.

## Features

- **Multiple Sorting Algorithms:** Implementations of Insertion Sort, Heap Sort, Shell Sort, and Quick Sort.
- **Configurable Gap Sequences:** For Shell Sort, the user can choose between Knuth and Hibbard sequences.
- **Flexible Pivot Selection:** Quick Sort supports different pivot selection strategies.
- **Data Generation:** Generate arrays of varying sizes and orderings (random, fully sorted, and partially sorted).
- **Performance Testing:** Automated tests that average sorting times over multiple repetitions.
- **Menu-Driven Interface:** An interactive menu allows users to load, generate, sort, and save arrays, as well as run performance tests.
- **CSV Output:** Performance results are saved in `performance_results.csv` for later analysis.

## Project Structure

- **main.cpp**  
  Contains the complete implementation including:
  - Sorting algorithm implementations (within the `Sorter` class)
  - Data generation utilities (`DataGenerator`)
  - File operations (`FileManager`)
  - The menu-driven interface (`Menu` and `SortingApp`)

## Getting Started

### Prerequisites

- A C++ compiler with C++17 support (e.g., `g++`, `clang++`).
- Standard libraries: `<algorithm>`, `<vector>`, `<iostream>`, `<random>`, `<fstream>`, `<chrono>`, etc.

### Compilation

To compile the project, run:

```bash
g++ -std=c++17 main.cpp -o sorting_app
```

### Running the Application

After compiling, start the application with:

```bash
./sorting_app
```

Upon launching, you will be prompted to choose the data type (integer or float) and then presented with a menu to perform various operations such as:
- Loading or generating an array
- Sorting using the selected algorithm and options
- Viewing the sorted array
- Running performance tests

## Usage

1. **Data Type Selection:** Choose whether to work with integers or floating-point numbers.
2. **Menu Options:**
   - **Load Array:** Load an array from a file.
   - **Generate Array:** Create a new array (random, sorted, or partially sorted).
   - **Sort Array:** Select a sorting algorithm and, if applicable, choose the gap sequence or pivot strategy.
   - **Performance Test:** Run automated tests on multiple array sizes and data types. Results are saved to `performance_results.csv`.
   - **Save Array:** Save the original or sorted array to a file.
3. **Interactive Testing:** The console output will display sorting times and verification messages to ensure correctness.

## Experiments & Results

The project experiments with array sizes ranging from 10,000 to 200,000 elements (with some tests limited to smaller arrays for algorithms like Insertion Sort). Timing measurements are done using `std::chrono::high_resolution_clock`, and the results show:
- **Insertion Sort** exhibits quadratic growth in time for unsorted data.
- **Heap Sort** maintains a consistent O(n log n) performance.
- **Shell Sort** benefits from a well-chosen gap sequence, with Knuth’s sequence typically outperforming Hibbard’s in tests.
- **Quick Sort** shows superior average performance when a good pivot strategy (e.g., middle pivot) is used, despite potential pitfalls for already sorted arrays

## References

- Cormen, T. et al. *Introduction to Algorithms*. PWN, 2009.
- Drozdek, A. *C++: Algorytmy i struktury danych*. Helion, 2016.
- Knuth, D. E. *The Art of Computer Programming, Volume 3: Sorting and Searching*. Addison-Wesley, 1998.
- Hibbard, T. N. *An empirical study of minimal storage sorting*, Communications of the ACM, 1968.
- Documentation for `std::chrono::high_resolution_clock` can be found on [cppreference.com](https://en.cppreference.com/w/cpp/chrono/high_resolution_clock).

## Author

**Oleksandr Radionenko**  
