// Homework 4
// Testing Sorting Algorithms
// William Yang

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;



// Computes duration given a start time and a stop time in nano seconds.
// Keep it in.
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time,
    chrono::high_resolution_clock::time_point end_time) {
    return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
}

// Generates and returns random vector of size @size_of_vector.
// Range of integer is 0 - 49.
vector<int> GenerateRandomVector(size_t size_of_vector) {
    // Use rand() to generate random integer

    vector<int> random_vector;
    srand(time(0));

    for (size_t i = 0; i < size_of_vector; ++i)
        random_vector.push_back(rand() % 50);

    return random_vector;
}

// Generates and returns sorted vector of size @size_of_vector.
// If @smaller_to_larger is true, returns vector sorted from small to large.
// Otherwise returns vector sorted from large to small
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger = true) {
    vector<int> random_vector;
    srand(time(0));

    // Generate vector of random integers
    for (size_t i = 0; i < size_of_vector; ++i)
        random_vector.push_back(rand() % 50);

    // Sort vector based on comparator.
    if (smaller_to_larger)
        QuickSort(random_vector, less<int>{});
    else
        QuickSort(random_vector, greater<int>{});

    return random_vector;
}

// Verifies that a vector is sorted given a comparator.
// I.e. it applies less_than() for consecutive pair of elements and returns true
// iff less_than() is true for all pairs.
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable>& input, Comparator less_than) {
    // Size 0: nothing to verify, so true.
    // Size 1: means order is already correct, so true.
    if (input.size() < 2)
        return true;
    for (size_t i = 0; i < input.size() - 1; ++i) {
        if (!less_than(input[i], input[i + 1]) && input[i] != input[i+1])
            return false;
    }
    return true;
}

// Wrapper function to test different sorting algorithms. See homework's PDF for details.
void testSortingWrapper(int argc, char** argv) {
    const string input_type = string(argv[1]);
    const int input_size = stoi(string(argv[2]));
    const string comparison_type = string(argv[3]);

    // Verify command line arguments
    if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small") {
        cout << "Invalid input type" << endl;
        return;
    }
    if (input_size <= 0) {
        cout << "Invalid size" << endl;
        return;
    }
    if (comparison_type != "less" && comparison_type != "greater") {
        cout << "Invalid comparison type" << endl;
        return;
    }

    cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl << endl;
    vector<int> input_vector;
    if (input_type == "random") {
        // Generate random vector @input_vector.
        input_vector = GenerateRandomVector(input_size);
    }
    else if (input_type == "sorted_small_to_large") {
        // Generate sorted vector (small to large) @input_vector.
        input_vector = GenerateSortedVector(input_size, true);
    }
    else if (input_type == "sorted_large_to_small") {
        // Generate sorted vector (large to small) @input_vector.
        input_vector = GenerateSortedVector(input_size, false);
    }

    vector<int> copy_vector = input_vector;
    // Call HeapSort / MergeSort / QuickSort  using appropriate input.
    // Call quicksort with median of three as pivot / middle as pivot / first as pivot using appropriate input.
    if (comparison_type == "less") // less, sort small to large
    {
        cout << "Heapsort" << endl;
        auto begin_time = chrono::high_resolution_clock::now();
        HeapSort(copy_vector, less<int>{});
        auto end_time = chrono::high_resolution_clock::now();
        cout << "Runtime: " << ComputeDuration(begin_time, end_time) << "ns" << endl;
        cout << "Verified: " << VerifyOrder(copy_vector, less<int>{}) << endl << endl;

        copy_vector = input_vector;
        cout << "MergeSort" << endl;
        begin_time = chrono::high_resolution_clock::now();
        MergeSort(copy_vector, less<int>{});
        end_time = chrono::high_resolution_clock::now();
        cout << "Runtime: " << ComputeDuration(begin_time, end_time) << "ns" << endl;
        cout << "Verified: " << VerifyOrder(copy_vector, less<int>{}) << endl << endl;

        copy_vector = input_vector;
        cout << "QuickSort" << endl;
        begin_time = chrono::high_resolution_clock::now();
        QuickSort(copy_vector, less<int>{});
        end_time = chrono::high_resolution_clock::now();
        cout << "Runtime: " << ComputeDuration(begin_time, end_time) << "ns" << endl;
        cout << "Verified: " << VerifyOrder(copy_vector, less<int>{}) << endl << endl;

        cout << "Testing Quicksort Pivot Implementations\n\n";

        cout << "Median of Three\nRuntime: "
            << ComputeDuration(begin_time, end_time) << "ns\nVerified: "
            << VerifyOrder(copy_vector, less<int>{}) << endl << endl;

        copy_vector = input_vector;
        cout << "Middle" << endl;
        begin_time = chrono::high_resolution_clock::now();
        QuickSort2(copy_vector, less<int>{});
        end_time = chrono::high_resolution_clock::now();
        cout << "Runtime: " << ComputeDuration(begin_time, end_time) << "ns" << endl;
        cout << "Verified: " << VerifyOrder(copy_vector, less<int>{}) << endl << endl;

        copy_vector = input_vector;
        cout << "First" << endl;
        begin_time = chrono::high_resolution_clock::now();
        QuickSort3(copy_vector, less<int>{});
        end_time = chrono::high_resolution_clock::now();
        cout << "Runtime: " << ComputeDuration(begin_time, end_time) << "ns" << endl;
        cout << "Verified: " << VerifyOrder(copy_vector, less<int>{}) << endl << endl;
    }
    else // greater, sort large to small
    {
        cout << "Heapsort" << endl;
        auto begin_time = chrono::high_resolution_clock::now();
        HeapSort(copy_vector, greater<int>{});
        auto end_time = chrono::high_resolution_clock::now();
        cout << "Runtime: " << ComputeDuration(begin_time, end_time) << "ns" << endl;
        cout << "Verified: " << VerifyOrder(copy_vector, greater<int>{}) << endl << endl;

        copy_vector = input_vector;
        cout << "MergeSort" << endl;
        begin_time = chrono::high_resolution_clock::now();
        MergeSort(copy_vector, greater<int>{});
        end_time = chrono::high_resolution_clock::now();
        cout << "Runtime: " << ComputeDuration(begin_time, end_time) << "ns" << endl;
        cout << "Verified: " << VerifyOrder(copy_vector, greater<int>{}) << endl << endl;

        copy_vector = input_vector;
        cout << "QuickSort" << endl;
        begin_time = chrono::high_resolution_clock::now();
        QuickSort(copy_vector, greater<int>{});
        end_time = chrono::high_resolution_clock::now();
        cout << "Runtime: " << ComputeDuration(begin_time, end_time) << "ns" << endl;
        cout << "Verified: " << VerifyOrder(copy_vector, greater<int>{}) << endl << endl;

        cout << "Testing Quicksort Pivot Implementations\n\n";

        cout << "Median of Three\nRuntime: "
            << ComputeDuration(begin_time, end_time) << "ns\nVerified: "
            << VerifyOrder(copy_vector, greater<int>{}) << endl << endl;

        copy_vector = input_vector;
        cout << "Middle" << endl;
        begin_time = chrono::high_resolution_clock::now();
        QuickSort2(copy_vector, greater<int>{});
        end_time = chrono::high_resolution_clock::now();
        cout << "Runtime: " << ComputeDuration(begin_time, end_time) << "ns" << endl;
        cout << "Verified: " << VerifyOrder(copy_vector, greater<int>{}) << endl << endl;

        copy_vector = input_vector;
        cout << "First" << endl;
        begin_time = chrono::high_resolution_clock::now();
        QuickSort3(copy_vector, greater<int>{});
        end_time = chrono::high_resolution_clock::now();
        cout << "Runtime: " << ComputeDuration(begin_time, end_time) << "ns" << endl;
        cout << "Verified: " << VerifyOrder(copy_vector, greater<int>{}) << endl;
    }
}

int main(int argc, char** argv) {
    // DO NOT CHANGE or ADD ANY CODE in this function.
    if (argc != 4) {
        cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
        return 0;
    }

    testSortingWrapper(argc, argv);

    return 0;
}
