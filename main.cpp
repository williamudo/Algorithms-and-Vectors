#include <iostream>
#include <limits>
#include <chrono>
#include <string>

#include "vector-operations/functions.h"
#include "algorithm-methods/functions.h"

namespace {

    int readInt(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::cin.clear();                                                   // reset error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad line
            std::cout << "Invalid input. Try again.\n";
        }
    }
}

template <typename Func>
double timeMs(Func f) {
    auto start = std::chrono::steady_clock::now();
    f();
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

void printMenu() {
    std::cout << "\n=== Search & Sort Demo ===\n"
                 " 1. Generate random vector\n"
                 " 2. Print vector\n"
                 " 3. Sort (choose algorithm)\n"
                 " 4. Search (choose algorithm)\n"
                 " 5. Insert element\n"
                 " 6. Remove element\n"
                 " 7. Reverse\n"
                 " 8. Stats (sum / min / max)\n"
                 " 0. Quit\n";
}

// namespace

int main() {
    std::vector<int> data;
    bool sorted = false;
    bool running = true;

    while (running) {
        printMenu();
        int choice = readInt("Choice: ");

        switch (choice) {
        case 1: {
            int n = readInt("Vector size: ");
            if (n < 0) { std::cout << "Size must be non-negative.\n"; break; }
            data = VECTOR::generateRandom(static_cast<std::size_t>(n));
            sorted = false;
            VECTOR::print(data);
            break;
        }
        case 2:
            VECTOR::print(data);
            break;
        case 3: {
            std::cout << "1) Bubble  2) Selection  3) Insertion  4) Merge  5) Quick\n";
            int a = readInt("Algorithm: ");
            double ms = 0;
            switch (a) {
                case 1: ms = timeMs([&]{ ALGORITHM::bubbleSort(data); });    break;
                case 2: ms = timeMs([&]{ ALGORITHM::selectionSort(data); }); break;
                case 3: ms = timeMs([&]{ ALGORITHM::insertionSort(data); }); break;
                case 4: ms = timeMs([&]{ ALGORITHM::mergeSort(data); });     break;
                case 5: ms = timeMs([&]{ ALGORITHM::quickSort(data); });     break;
                default: std::cout << "Unknown algorithm.\n"; continue;
            }
            sorted = true;
            std::cout << "Sorted in " << ms << " ms. Verified: "
                      << (ALGORITHM::isSorted(data) ? "yes" : "NO") << "\n";
            break;
        }
        case 4: {
            int target = readInt("Value to find: ");
            std::cout << "1) Linear  2) Binary\n";
            int a = readInt("Algorithm: ");
            int idx = -1;
            if (a == 2) {
                if (!sorted) { std::cout << "Binary search needs a sorted vector. Sort first.\n"; break; }
                idx = ALGORITHM::binarySearch(data, target);
            } else {
                idx = ALGORITHM::linearSearch(data, target);
            }
            if (idx >= 0) std::cout << "Found at index " << idx << "\n";
            else          std::cout << "Not found.\n";
            break;
        }
        case 5: {
            int i = readInt("Index: ");
            int v = readInt("Value: ");
            if (i < 0) { std::cout << "Bad index.\n"; break; }
            VECTOR::insertAt(data, static_cast<std::size_t>(i), v);
            sorted = false;               // insertion may break ordering
            break;
        }
        case 6: {
            int i = readInt("Index to remove: ");
            if (i < 0 || !VECTOR::removeAt(data, static_cast<std::size_t>(i)))
                std::cout << "Invalid index.\n";
            break;
        }
        case 7:
            VECTOR::reverse(data);
            sorted = false;               // now descending
            break;
        case 8:
            if (data.empty()) { std::cout << "Vector is empty.\n"; break; }
            std::cout << "Sum: " << VECTOR::sum(data)
                      << "  Min: " << VECTOR::minValue(data)
                      << "  Max: " << VECTOR::maxValue(data) << "\n";
            break;
        case 0:
            running = false;
            break;
        default:
            std::cout << "Unknown option.\n";
        }
    }
    return 0;
}