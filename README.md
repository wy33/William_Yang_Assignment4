# Assignment 4

## Information about the repository

This repository contains the following:
- `Sort.h`
- `test_sorting_algorithms.cc`

## Parts of the program completed

All parts completed.

`Sort.h`
- Heapsort(): replaced "<" with less_than comparator operation for element comparison.
- percDownWithComp(): replaced "<" with less_than comparator operation for element comparison.
- MergeSort(): replaced "<=" with less_than comparator operation for element comparison.
- Merge(): replaced "<" with less_than comparator operation for element comparison.
- QuickSort(): replaced "<" with less_than comparator operation for element comparison.
- median3(): replaced "<" with less_than comparator operation for element comparison.
- QuickSort2(): uses a new internal partition function "middlePivotPartition()" that returns the index of the pivot instead of the pivot element.
- middlePivotPartition(): this is the internal function that actually does the sorting. Both i and j had to be adjusted to accommodate changes to pivot selection process.
- QuickSort3(): uses a new internal partition function "firstPivotPartition()" that returns the index of the pivot instead of the pivot element.
- firstPivotPartition(): this is the internal function that actually does the sorting. Hides the pivot to the left instead to avoid a swap to the end of subarray. Both i and j had to be adjusted to accommodate changes to pivot selection process.

Most of the sorting functions were copy and pasted from the original code from the textbook and had its element comparison portion changed from "<" to the "less_than" comparator for the internal functions.

`test_sorting_algorithms.cc`
- VerifyOrder(): array is in correct order if size == 0 or size == 1, and if the array is sorted in the order dictated by the comparator supplied. For adjacent elements that are equal, the order is still correct.
- GenerateRandomVector(): generates a vector with integers ranging from 0 - 49. Range can be adjusted into the negatives, expand, or contract by changing the rand() calculations inside the parameter of the push_back() function inside the for loop.
- GenerateSortedVector(): uses the same algorithm of GenerateRandomVector(): and then uses QuickSort() function from "Sort.h" file to sort it in the order dictated by the boolean parameter (true for small to large, false for large to small. Default for the boolean parameter is true).
- ComputeDuration(): calculates the difference between start and end time supplied to parameters.
- sortTestingWrapper(): Verifies command line arguments are valid. Then generates a random or sorted vector (small to large/large to small specified by command line arguments. Then sorts the same vector using various sorting algorithms while timing them (order based on command line argument "less" or "greater"). Format for the huge chunk of code inside the last if/else statements is copy input_vector into copy_vector, get current time, sort copy_vector, get current time, compute the time from before sort and after sort, then verify order. The same vector is used for all sorting algorithms to get a fair comparison.

## Bugs encountered

No bugs encountered for final code. During testing, lots of segmentation faults while working with the 3 quicksort algorithms (i and j values adjusted as result).

## Running the assignment

Use provided `Makefile` for Homework 4.

To compile on terminal, type:

```bash
make
```

To delete executables and object files, type:

```bash
make clean
```

To run test_sorting_algorithms, type:

```bash
./test_sorting_algorithms <input_type> <input_size> <comparison_type>
```

```bash
./test_sorting_algorithms random 10000 less
```

```bash
./test_sorting_algorithms sorted_small_to_large 10000 greater
```

```bash
./test_sorting_algorithms sorted_large_to_small 10000 greater
```

input_type: is how the generated array is sorted (random, sorted_small_to_large, sorted_large_to_small).
input_size: is the size of the generated array (any positive integer).
comparison_type: is the type of comparison (less/greater).
