#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <vector>

#include "./structs/path.hpp"

class QuickSort {
    private:
        std::vector<Path> keyVec;

        void qSort(int lowerBound, int upperBound, std::string criteria) {
            int i = lowerBound;
            int j = upperBound;
            float pivot;
            if (criteria == "Time") {
                pivot = keyVec[lowerBound + (upperBound - lowerBound) / 2].t;
            } else if (criteria == "Cost") {
                pivot = keyVec[lowerBound + (upperBound - lowerBound) / 2].c;
            }
            

            while (i <= j) {
                if (criteria == "Time") {
                    while (keyVec[i].t < pivot) {
                        i++;
                    }
                    while (keyVec[j].t > pivot) {
                        j--;
                    }
                } else if (criteria == "Cost") {
                    while (keyVec[i].c < pivot) {
                        i++;
                    }
                    while (keyVec[j].c > pivot) {
                        j--;
                    }
                }
                if (i <= j) {
                    std::swap(keyVec[i], keyVec[j]);
                    i++;
                    j--;
                }
            }

            if (lowerBound < j) {
                qSort(lowerBound, j, criteria);
            }
            if (i < upperBound) {
                qSort(i, upperBound, criteria);
            }
        }

    public:
        std::vector<Path> sort(std::vector<Path> toSort, std::string criteria) {
            keyVec = toSort;
            qSort(0, toSort.size() - 1, criteria);
            return keyVec;
        }
};
#endif
