#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>
#include <iostream>
#include <thread>

class Benchmark
{
protected:
    std::chrono::duration<double> sequentialDuration;
    std::chrono::duration<double> multithreadedDuration;
    unsigned int systemNumTreads = std::thread::hardware_concurrency();
    unsigned int numThreads = 1;
    void executeSequential();
    void executeMultithreaded();

public:
    virtual void sequentialOperation() = 0;
    virtual void multithreadedOperation() = 0;
    double getSpeedup() const;
    double getEfficiency() const;
    void report();
    void setNumThreads(unsigned int);
    unsigned int getSystemNumTreads();
};

#endif
