#include "functions.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

namespace VECTOR {
    std::vector<int> generateRandom(std::size_t size, int minVal, int maxVal) {
        static std::mt19937 rng{std::random_device{}()};   // seeded once
        std::uniform_int_distribution<int> dist(minVal, maxVal);

        std::vector<int> v;
        v.reserve(size);                                   // one allocation up front
        for (std::size_t i = 0; i < size; ++i)
            v.push_back(dist(rng));
        return v;                                          // moved, not copied
    }

    void print(const std::vector<int>& v) {
        std::cout << "[ ";
        for (int x : v) std::cout << x << ' ';
        std::cout << "]  (size " << v.size() << ")\n";
    }

    void insertAt(std::vector<int>& v, std::size_t index, int value) {
        if (index > v.size()) index = v.size();
        v.insert(v.begin() + index, value);
    }

    bool removeAt(std::vector<int>& v, std::size_t index) {
        if (index >= v.size()) return false;
        v.erase(v.begin() + index);
        return true;
    }

    void reverse(std::vector<int>& v) { std::reverse(v.begin(), v.end()); }

    int sum(const std::vector<int>& v) { return std::accumulate(v.begin(), v.end(), 0); }

    int minValue(const std::vector<int>& v) { return *std::min_element(v.begin(), v.end()); }
    int maxValue(const std::vector<int>& v) { return *std::max_element(v.begin(), v.end()); }

}
