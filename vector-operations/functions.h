// MODIFIED WITH HEAVY USE OF LLM: CHATGPT

#pragma once
#ifndef VECTORS_H
#define VECTORS_H

#include <vector>
#include <cstddef>

namespace VECTOR {
    std::vector<int> generateRandom(std::size_t size, int minVal = 0, int maxVal = 20);
    void print(const std::vector<int>& v);
    void insertAt(std::vector<int>& v, std::size_t index, int value);
    bool removeAt(std::vector<int>& v, std::size_t index);
    void reverse(std::vector<int>& v);
    int  sum(const std::vector<int>& v);
    int  minValue(const std::vector<int>& v);
    int  maxValue(const std::vector<int>& v);
}
#endif
