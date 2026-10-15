#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>

namespace ALGORITHM {
    // Search: return index of target, or -1 if not found
    int linearSearch(const std::vector<int>& v, int target);
    int binarySearch(const std::vector<int>& v, int target);   // requires sorted input

    // Sorts: in-place, ascending
    void bubbleSort(std::vector<int>& v);
    void selectionSort(std::vector<int>& v);
    void insertionSort(std::vector<int>& v);
    void mergeSort(std::vector<int>& v);
    void quickSort(std::vector<int>& v);

    bool isSorted(const std::vector<int>& v);
}
#endif
