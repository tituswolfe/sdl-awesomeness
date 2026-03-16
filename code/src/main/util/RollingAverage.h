//
// Created by Titus Wolfe on 3/15/26.
//

#ifndef SDLAWESOMENESS_ROLLINGAVERAGE_H
#define SDLAWESOMENESS_ROLLINGAVERAGE_H
#include <queue>


class RollingAverage {
    std::queue<double> samples;
    double total;
    int size;


public:
    explicit RollingAverage(const int size) {
        resize(size);
    }

    int getSize() {
        return size;
    }

    void addSample(const double sampleValue) {
        if (samples.size() >= size) {
            total -= samples.front();
            samples.pop();
        }

        samples.push(sampleValue);
        total += sampleValue;
    }

    double getAverage() {
        if (samples.empty()) return 0;
        return total / samples.size();
    }

    void resize(const int newSize) {
        size = newSize;

    }
    void reset() {
        samples.empty();
    }
};


#endif //SDLAWESOMENESS_ROLLINGAVERAGE_H