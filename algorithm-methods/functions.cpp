#include "functions.h"

#include <iostream>
#include <utility>    // std::swap
#include <algorithm>  // std::copy

namespace ALGORITHM {
    // ---------- SEARCHES ----------

    // ---------- Linear Search ----------
    int linearSearch(const std::vector<int>& v, int target) {
        for (std::size_t i = 0; i < v.size(); ++i)
            if (v[i] == target) return static_cast<int>(i);
        return -1;
    }
    // ---------- Binary Search ---------- 
    int binarySearch(const std::vector<int>& v, int target) {
        int lo = 0, hi = static_cast<int>(v.size()) - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;          // avoids overflow of (lo+hi)
            if (v[mid] == target)      return mid;
            else if (v[mid] < target)  lo = mid + 1;
            else                       hi = mid - 1;
        }
        return -1;
    }

    // ---------- SIMPLE SORTS ----------

    // ---------- Bubble Sort -----------
    void bubbleSort(std::vector<int>& v) {
        for (std::size_t i = 0; i + 1 < v.size(); ++i) {
            bool swapped = false;
            for (std::size_t j = 0; j + 1 < v.size() - i; ++j) {
                if (v[j] > v[j + 1]) { std::swap(v[j], v[j + 1]); swapped = true; }
            }
            if (!swapped) break;                   // already sorted
        }
    }

    // ---------- Selection Sort ----------
    void selectionSort(std::vector<int>& v) {
        for (std::size_t i = 0; i + 1 < v.size(); ++i) {
            std::size_t minIdx = i;
            for (std::size_t j = i + 1; j < v.size(); ++j)
                if (v[j] < v[minIdx]) minIdx = j;
            if (minIdx != i) std::swap(v[i], v[minIdx]);
        }
    }
    
    // ---------- Insertion Sort ---------- 
    void insertionSort(std::vector<int>& v) {
        for (std::size_t i = 1; i < v.size(); ++i) {
            int key = v[i];
            std::size_t j = i;
            while (j > 0 && v[j - 1] > key) { v[j] = v[j - 1]; --j; }
            v[j] = key;
        }
    }

    // ---------- Merge sort ----------
    namespace {   // anonymous namespace = private to this file

    void merge(std::vector<int>& v, int left, int mid, int right) {
        std::vector<int> temp;
        temp.reserve(right - left + 1);
        int i = left, j = mid + 1;
        while (i <= mid && j <= right)
            temp.push_back(v[i] <= v[j] ? v[i++] : v[j++]);   // <= keeps it stable
        while (i <= mid)   temp.push_back(v[i++]);
        while (j <= right) temp.push_back(v[j++]);
        std::copy(temp.begin(), temp.end(), v.begin() + left);
    }

    void mergeSortRec(std::vector<int>& v, int left, int right) {
        if (left >= right) return;                 // base case
        int mid = left + (right - left) / 2;
        mergeSortRec(v, left, mid);
        mergeSortRec(v, mid + 1, right);
        merge(v, left, mid, right);
    }

    // ---------- Quick sort (Lomuto partition) ----------
    int partition(std::vector<int>& v, int low, int high) {
        int pivot = v[high];
        int i = low - 1;
        for (int j = low; j < high; ++j)
            if (v[j] <= pivot) std::swap(v[++i], v[j]);
        std::swap(v[i + 1], v[high]);
        return i + 1;
    }

    void quickSortRec(std::vector<int>& v, int low, int high) {
        if (low >= high) return;
        int p = partition(v, low, high);
        quickSortRec(v, low, p - 1);
        quickSortRec(v, p + 1, high);
    }

    }  // end anonymous namespace

    void mergeSort(std::vector<int>& v) {
        if (v.size() > 1) mergeSortRec(v, 0, static_cast<int>(v.size()) - 1);
    }

    void quickSort(std::vector<int>& v) {
        if (v.size() > 1) quickSortRec(v, 0, static_cast<int>(v.size()) - 1);
    }

    bool isSorted(const std::vector<int>& v) {
        for (std::size_t i = 1; i < v.size(); ++i)
            if (v[i - 1] > v[i]) return false;
        return true;
    }

}