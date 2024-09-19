#include "benchmark.h"
#include <chrono>
#include <iostream>
#include <thread>

void Benchmark::executeSequential()
{
    std::cout << "Running sequential..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    sequentialOperation();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Finished running sequential" << std::endl;
    sequentialDuration = end - start;
}

void Benchmark::executeMultithreaded()
{
    std::cout << "Running multithreaded..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    multithreadedOperation();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Finished running multithreaded" << std::endl;
    multithreadedDuration = end - start;
}

double Benchmark::getSpeedup() const
{
    return sequentialDuration.count() / multithreadedDuration.count();
}

double Benchmark::getEfficiency() const
{
    return getSpeedup() / numThreads;
}

void Benchmark::report()
{
    executeSequential();
    executeMultithreaded();

    std::cout << "Sequential Time: " << sequentialDuration.count() << " seconds" << std::endl;
    std::cout << "Multithreaded Time: " << multithreadedDuration.count() << " seconds" << std::endl;
    std::cout << "Number of Threads Used: " << numThreads << std::endl;
    std::cout << "Number of Threads Available on System: " << systemNumTreads << std::endl;
    std::cout << "Speedup: " << getSpeedup() << std::endl;
    std::cout << "Efficiency: " << getEfficiency() << std::endl;
}

void Benchmark::setNumThreads(unsigned int numThreads)
{
    this->numThreads = numThreads;
}

unsigned int Benchmark::getSystemNumTreads()
{
    return systemNumTreads;
}