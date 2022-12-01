// Current code is from the textbook.
// Modified by: William Yang
// Sort.h: A file with various sorting algorithms.

#ifndef SORT_H
#define SORT_H

/**
 * Several sorting routines.
 * Arrays are rearranged with smallest item first for the first half.
 * Arrays are rearranged depending on the comparator supplied for the second half.
 */

#include <vector>
#include <functional>
using namespace std;



//********************//    NON-COMPARATOR SORTS    //********************//

/**
 * Simple insertion sort.
 */
template <typename Comparable>
void insertionSort(vector<Comparable>& a)
{
    for (int p = 1; p < a.size(); ++p)
    {
        Comparable tmp = std::move(a[p]);

        int j;
        for (j = p; j > 0 && tmp < a[j - 1]; --j)
            a[j] = std::move(a[j - 1]);
        a[j] = std::move(tmp);
    }
}


/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void insertionSort(vector<Comparable>& a, int left, int right)
{
    for (int p = left + 1; p <= right; ++p) // Insert partition
    {
        Comparable tmp = std::move(a[p]);
        int j;

        for (j = p; j > left && tmp < a[j - 1]; --j)
            a[j] = std::move(a[j - 1]);
        a[j] = std::move(tmp);
    }
}



/**
 * Shellsort, using Shell's (poor) increments.
 */
template <typename Comparable>
void shellsort(vector<Comparable>& a)
{
    for (int gap = a.size() / 2; gap > 0; gap /= 2)
        for (int i = gap; i < a.size(); ++i)
        {
            Comparable tmp = std::move(a[i]);
            int j = i;

            for (; j >= gap && tmp < a[j - gap]; j -= gap)
                a[j] = std::move(a[j - gap]);
            a[j] = std::move(tmp);
        }
}

/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild(int i)
{
    return 2 * i + 1;
}

/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
template <typename Comparable>
void percDown(vector<Comparable>& a, int i, int n)
{
    int child;
    Comparable tmp;

    for (tmp = std::move(a[i]); leftChild(i) < n; i = child)
    {
        child = leftChild(i);
        if (child != n - 1 && a[child] < a[child + 1])
            ++child;
        if (tmp < a[child])
            a[i] = std::move(a[child]);
        else
            break;
    }
    a[i] = std::move(tmp);
}

/**
 * Standard heapsort.
 */
template <typename Comparable>
void heapsort(vector<Comparable>& a)
{
    for (int i = a.size() / 2 - 1; i >= 0; --i)  /* buildHeap */
        percDown(a, i, a.size());
    for (int j = a.size() - 1; j > 0; --j)
    {
        std::swap(a[0], a[j]);               /* deleteMax */
        percDown(a, 0, j);
    }
}

/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
template <typename Comparable>
void merge(vector<Comparable>& a, vector<Comparable>& tmpArray,
    int leftPos, int rightPos, int rightEnd)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while (leftPos <= leftEnd && rightPos <= rightEnd)
        if (a[leftPos] <= a[rightPos])
            tmpArray[tmpPos++] = std::move(a[leftPos++]);
        else
            tmpArray[tmpPos++] = std::move(a[rightPos++]);

    while (leftPos <= leftEnd)    // Copy rest of first half
        tmpArray[tmpPos++] = std::move(a[leftPos++]);

    while (rightPos <= rightEnd)  // Copy rest of right half
        tmpArray[tmpPos++] = std::move(a[rightPos++]);

    // Copy tmpArray back
    for (int i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = std::move(tmpArray[rightEnd]);
}

/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void mergeSort(vector<Comparable>& a,
    vector<Comparable>& tmpArray, int left, int right)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        mergeSort(a, tmpArray, left, center);
        mergeSort(a, tmpArray, center + 1, right);
        merge(a, tmpArray, left, center + 1, right);
    }
}

/**
 * Mergesort algorithm (driver).
 */
template <typename Comparable>
void mergeSort(vector<Comparable>& a)
{
    vector<Comparable> tmpArray(a.size());

    mergeSort(a, tmpArray, 0, a.size() - 1);
}



/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename Comparable>
const Comparable& median3(vector<Comparable>& a, int left, int right)
{
    int center = (left + right) / 2;

    // Order left, center, and right
    if (a[center] < a[left])
        std::swap(a[left], a[center]);
    if (a[right] < a[left])
        std::swap(a[left], a[right]);
    if (a[right] < a[center])
        std::swap(a[center], a[right]);

    // Place pivot at position right - 1
    std::swap(a[center], a[right - 1]);
    return a[right - 1];
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void quicksort(vector<Comparable>& a, int left, int right)
{
    if (left + 10 <= right)
    {
        const Comparable& pivot = median3(a, left, right);

        // Begin partitioning
        int i = left, j = right - 1;
        for (; ; )
        {
            while (a[++i] < pivot) {}
            while (pivot < a[--j]) {}
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]);  // Restore pivot

        quicksort(a, left, i - 1);     // Sort small elements
        quicksort(a, i + 1, right);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort(a, left, right);
}

/**
 * Quicksort algorithm (driver).
 */
template <typename Comparable>
void quicksort(vector<Comparable>& a)
{
    quicksort(a, 0, a.size() - 1);
}


/**
 * Internal selection method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect(vector<Comparable>& a, int left, int right, int k)
{
    if (left + 10 <= right)
    {
        const Comparable& pivot = median3(a, left, right);

        // Begin partitioning
        int i = left, j = right - 1;
        for (; ; )
        {
            while (a[++i] < pivot) {}
            while (pivot < a[--j]) {}
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]);  // Restore pivot

            // Recurse; only this part changes
        if (k <= i)
            quickSelect(a, left, i - 1, k);
        else if (k > i + 1)
            quickSelect(a, i + 1, right, k);
    }
    else  // Do an insertion sort on the subarray
        insertionSort(a, left, right);
}

/**
 * Quick selection algorithm.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect(vector<Comparable>& a, int k)
{
    quickSelect(a, 0, a.size() - 1, k);
}

/*
 * A divide and conquer-type sort.
 */
template <typename Comparable>
void SORT(vector<Comparable>& items)
{
    if (items.size() > 1)
    {
        vector<Comparable> smaller;
        vector<Comparable> same;
        vector<Comparable> larger;

        auto chosenItem = items[items.size() / 2];

        // Split items array's elements into smaller, same, and larger arrays
        for (auto& i : items)
        {
            if (i < chosenItem)
                smaller.push_back(std::move(i));
            else if (chosenItem < i)
                larger.push_back(std::move(i));
            else
                same.push_back(std::move(i));
        }

        SORT(smaller);     // Recursive call to sort smaller items
        SORT(larger);      // Recursive call to sort larger items

        std::move(begin(smaller), end(smaller), begin(items));
        std::move(begin(same), end(same), begin(items) + smaller.size());
        std::move(begin(larger), end(larger), end(items) - larger.size());
    }
}

//********************//    COMPARATOR SORTS    //********************//

/*
 * This is the more public version of insertion sort.
 * It requires a pair of iterators and a comparison
 * function object.
 */
template <typename RandomIterator, typename Comparator>
void insertionSort(const RandomIterator& begin,
    const RandomIterator& end,
    Comparator lessThan)
{
    if (begin == end)
        return;

    RandomIterator j;

    for (RandomIterator p = begin + 1; p != end; ++p) // Insert partition
    {
        auto tmp = std::move(*p);
        for (j = p; j != begin && lessThan(tmp, *(j - 1)); --j)
            *j = std::move(*(j - 1));
        *j = std::move(tmp);
    }
}

/*
 * The two-parameter version calls the three parameter version, using C++11 decltype.
 */
template <typename RandomIterator>
void insertionSort(const RandomIterator& begin,
    const RandomIterator& end)
{
    insertionSort(begin, end, less<decltype(*begin)>{ });
}


/**
 * Internal method for heapsort that is used in
 * deleteMax/DeleteMin and buildHeap using a comparator.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 * less_than is the comparator.
 */
template <typename Comparable, typename Comparator>
void percDownWithComp(vector<Comparable>& a, int i, int n, Comparator less_than)
{
    int child;
    Comparable tmp;

    for (tmp = std::move(a[i]); leftChild(i) < n; i = child)
    {
        child = leftChild(i);
        if (child != n - 1 && less_than(a[child], a[child + 1]))
            ++child;
        if (less_than(tmp, a[child]))
            a[i] = std::move(a[child]);
        else
            break;
    }
    a[i] = std::move(tmp);
}

// Driver for HeapSort.
// @a: input/output vector to be sorted.
// @less_than: Comparator to be used.
template <typename Comparable, typename Comparator>
void HeapSort(vector<Comparable>& a, Comparator less_than)
{
    for (int i = a.size() / 2 - 1; i >= 0; --i)  /* buildHeap */
        percDownWithComp(a, i, a.size(), less_than);
    for (int j = a.size() - 1; j > 0; --j)
    {
        std::swap(a[0], a[j]);               /* deleteMax */
        percDownWithComp(a, 0, j, less_than);
    }
}



/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 * less_than is the comparator used.
 */
template <typename Comparable, typename Comparator>
void Merge(vector<Comparable>& a, vector<Comparable>& tmpArray,
    int leftPos, int rightPos, int rightEnd, Comparator less_than)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while (leftPos <= leftEnd && rightPos <= rightEnd)
        if (less_than(a[leftPos], a[rightPos]))
            tmpArray[tmpPos++] = std::move(a[leftPos++]);
        else
            tmpArray[tmpPos++] = std::move(a[rightPos++]);

    while (leftPos <= leftEnd)    // Copy rest of first half
        tmpArray[tmpPos++] = std::move(a[leftPos++]);

    while (rightPos <= rightEnd)  // Copy rest of right half
        tmpArray[tmpPos++] = std::move(a[rightPos++]);

    // Copy tmpArray back
    for (int i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = std::move(tmpArray[rightEnd]);
}

/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * less_than is the comparator to be used.
 */
template <typename Comparable, typename Comparator>
void MergeSort(vector<Comparable>& a,
    vector<Comparable>& tmpArray, int left, int right, Comparator less_than)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        MergeSort(a, tmpArray, left, center, less_than);
        MergeSort(a, tmpArray, center + 1, right, less_than);
        Merge(a, tmpArray, left, center + 1, right, less_than);
    }
}

// Driver for MergeSort.
// @a: input/output vector to be sorted.
// @less_than: Comparator to be used.
template <typename Comparable, typename Comparator>
void MergeSort(vector<Comparable>& a, Comparator less_than)
{
    vector<Comparable> tmpArray(a.size());

    MergeSort(a, tmpArray, 0, a.size() - 1, less_than);
}


/**
 * Return median of left, center, and right.
 * Order these according to the comparator and hide the pivot.
 */
template <typename Comparable, typename Comparator>
const Comparable& median3(vector<Comparable>& a, int left, int right, Comparator less_than)
{
    int center = (left + right) / 2;

    // Order left, center, and right
    if (less_than(a[center], a[left]))
        std::swap(a[left], a[center]);
    if (less_than(a[right], a[left]))
        std::swap(a[left], a[right]);
    if (less_than(a[right], a[center]))
        std::swap(a[center], a[right]);

    // Place pivot at position right - 1
    std::swap(a[center], a[right - 1]);
    return a[right - 1];
}


/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * less_than is the comparator to be used.
 */
template <typename Comparable, typename Comparator>
void QuickSort(vector<Comparable>& a, int left, int right, Comparator less_than)
{
    if (left + 10 <= right)
    {
        const Comparable& pivot = median3(a, left, right, less_than);

        // Begin partitioning
        int i = left, j = right - 1;
        for (; ; )
        {
            while (less_than(a[++i], pivot)) {}
            while (less_than(pivot, a[--j])) {}
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]);  // Restore pivot

        QuickSort(a, left, i - 1, less_than);     // Sort small elements
        QuickSort(a, i + 1, right, less_than);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort(a.begin() + left, a.begin() + right + 1, less_than);
}


// Driver for QuickSort (median of 3 partitioning).
// @a: input/output vector to be sorted.
// @less_than: Comparator to be used.
template <typename Comparable, typename Comparator>
void QuickSort(vector<Comparable>& a, Comparator less_than)
{
    QuickSort(a, 0, a.size() - 1, less_than);
}



/**
 * Return pivot index.
 * Pivot is middle element of subarray.
 * Partition the subarray.
 */
template <typename Comparable, typename Comparator>
int middlePivotPartition(vector<Comparable>& a, int left, int right, Comparator less_than)
{
    int center = (left + right) / 2;
    const Comparable pivot = a[center];   // Choose middle element

    std::swap(a[center], a[right]); // Hide pivot at the end of subarray

    // Adjusted i and j due to different pivot selecting algorithm
    int i = left - 1;
    int j = right;

    // Place smaller elements and larger elements into their own subarrays
    // depending on the comparator.
    while (true)
    {
        while (less_than(a[++i], pivot)) {}
        while (less_than(pivot, a[--j])) {}
        if (i < j) std::swap(a[i], a[j]);
        else break;
    }

    std::swap(a[right], a[i]);  // Place pivot on correct position
    return i;
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * less_than is the comparator to be used.
 */
template <typename Comparable, typename Comparator>
void QuickSort2(vector<Comparable>& a, int left, int right, Comparator less_than)
{
    if (left + 10 <= right)
    {
        // Begin partitioning
        const int pivot_index = middlePivotPartition(a, left, right, less_than);

        QuickSort2(a, left, pivot_index - 1, less_than);     // Sort small elements
        QuickSort2(a, pivot_index + 1, right, less_than);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort(a.begin() + left, a.begin() + right + 1, less_than);
}

// Driver for QuickSort (middle pivot).
// @a: input/output vector to be sorted.
// @less_than: Comparator to be used.
template <typename Comparable, typename Comparator>
void QuickSort2(vector<Comparable>& a, Comparator less_than)
{
    QuickSort2(a, 0, a.size() - 1, less_than);
}



/**
 * Return pivot index.
 * Pivot is first element of subarray.
 * Partition the subarray.
 */
template <typename Comparable, typename Comparator>
int firstPivotPartition(vector<Comparable>& a, int left, int right, Comparator less_than)
{
    const Comparable pivot = a[left]; // Choose leftmost element as pivot (hidden on left side of subarray)

    // Adjusted i and j to hide pivot on the left instead
    int i = left;
    int j = right + 1;

    while (true)
    {
        while (less_than(a[++i], pivot)) {}
        while (less_than(pivot, a[--j])) {}
        if (i < j) std::swap(a[i], a[j]);
        else break;
    }

    std::swap(a[left], a[j]);   // Place pivot on correct position
    return j;
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * less_than is the comparator to be used.
 */
template <typename Comparable, typename Comparator>
void QuickSort3(vector<Comparable>& a, int left, int right, Comparator less_than)
{
    if (left + 10 <= right)
    {
        // Begin partitioning
        const int pivot_index = firstPivotPartition(a, left, right, less_than);

        QuickSort3(a, left, pivot_index - 1, less_than);     // Sort small elements
        QuickSort3(a, pivot_index + 1, right, less_than);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort(a.begin() + left, a.begin() + right + 1, less_than);
}

// Driver for quicksort using first as pivot.
template <typename Comparable, typename Comparator>
void QuickSort3(vector<Comparable>& a, Comparator less_than)
{
    QuickSort3(a, 0, a.size() - 1, less_than);
}


#endif  // SORT_H

