#include <iostream>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <vector>
#include <thread>
#include <mutex>
#include <numeric>
#include <functional>
#include <string>
#include <fstream>
#include <sstream>

class TaylorSeriesCalculator
{
public:
    // Constructor that accepts x, numTerms, and numThreads
    TaylorSeriesCalculator(long double x, unsigned int numTerms, unsigned int numThreads)
        : x(x), numTerms(numTerms), numThreads(numThreads)
    {
    }

    long double sequential() const
    {
        long double result = 0.0;
        long double term;
        long double y = (x - 1) / (x + 1);

        for (unsigned int n = 0; n < numTerms; ++n)
        {
            term = 1.0 / (2 * n + 1) * std::pow(y, 2 * n + 1);
            result += term;
        }

        return 2 * result;
    }

    long double multithreaded() const
    {
        std::vector<std::thread> threads;
        std::vector<long double> results(numThreads, 0.0);
        std::mutex resultMutex;

        auto worker = [&](unsigned int threadIndex)
        {
            long double localResult = 0.0;
            unsigned int chunkSize = numTerms / numThreads;
            unsigned int start = threadIndex * chunkSize;
            unsigned int end = (threadIndex == numThreads - 1) ? numTerms : start + chunkSize;
            long double y = (x - 1) / (x + 1);

            for (unsigned int n = start; n < end; ++n)
            {
                long double term = 1.0 / (2 * n + 1) * std::pow(y, 2 * n + 1);
                localResult += term;
            }

            std::lock_guard<std::mutex> guard(resultMutex);
            results[threadIndex] = localResult;
        };

        for (unsigned int i = 0; i < numThreads; ++i)
        {
            threads.emplace_back(worker, i);
        }

        for (auto &thread : threads)
        {
            thread.join();
        }

        long double finalResult = 2 * std::accumulate(results.begin(), results.end(), 0.0);
        return finalResult;
    }

    unsigned int getNumThreads() const
    {
        return numThreads;
    }

private:
    long double x;
    unsigned int numTerms;
    unsigned int numThreads;
};

class RunLogger
{
public:
    RunLogger() {}

    void log(long double elapsedTime)
    {
        runs.emplace_back(elapsedTime); // Append the elapsed time of the run
    }

    long double average() const
    {
        if (runs.empty())
            return 0.0;

        return std::accumulate(runs.begin(), runs.end(), 0.0) / runs.size();
    }

private:
    std::vector<long double> runs; // Stores elapsed times
};

// Template function for getting user input with default values
template <typename T>
T getInput(const std::string &prompt, T defaultValue)
{
    std::cout << prompt << " (default: " << defaultValue << "): ";
    std::string input;
    std::getline(std::cin, input);
    if (input.empty())
    {
        return defaultValue;
    }
    try
    {
        if (std::is_same<T, int>::value)
        {
            return std::stoi(input);
        }
        else if (std::is_same<T, long double>::value)
        {
            return std::stod(input);
        }
        else if (std::is_same<T, unsigned int>::value)
        {
            return std::stoul(input);
        }
        else
        {
            throw std::invalid_argument("Unsupported type");
        }
    }
    catch (const std::invalid_argument &)
    {
        std::cerr << "Invalid input. Using default value: " << defaultValue << std::endl;
        return defaultValue;
    }
}

unsigned int getOptimalNumThreads()
{
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0)
        numThreads = 1; // Default to 1 if hardware_concurrency is not available
    return numThreads;
}

int main()
{
    // Default values
    long double defaultX = 1.5e5;
    unsigned int defaultNumTerms = 1e7;
    unsigned int defaultNumRuns = 10;
    unsigned int defaultNumThreads = getOptimalNumThreads();

    // Use the abstracted input function
    long double x = getInput("Enter value of x", defaultX);
    unsigned int numTerms = getInput("Enter number of terms", defaultNumTerms);
    unsigned int numRuns = getInput("Enter number of runs", defaultNumRuns);
    unsigned int numThreads = getInput("Enter number of threads", defaultNumThreads);

    // Create an instance of TaylorSeriesCalculator with user-specified number of threads
    TaylorSeriesCalculator calculator(x, numTerms, numThreads);

    // Create instances of RunLogger
    RunLogger sequentialLogger;
    RunLogger multithreadedLogger;

    std::cout << "Running sequential version" << std::endl;
    for (unsigned int i = 0; i < numRuns; ++i)
    {
        auto start = std::chrono::high_resolution_clock::now();
        calculator.sequential();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<long double> elapsed = end - start;
        sequentialLogger.log(elapsed.count());
    }

    std::cout << "Running multithreading version" << std::endl;
    for (unsigned int i = 0; i < numRuns; ++i)
    {
        auto start = std::chrono::high_resolution_clock::now();
        calculator.multithreaded();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<long double> elapsed = end - start;
        multithreadedLogger.log(elapsed.count());
    }

    // Calculate average times
    long double avgSequentialTime = sequentialLogger.average();
    long double avgMultithreadedTime = multithreadedLogger.average();

    // Calculate speedup
    long double speedup = avgSequentialTime / avgMultithreadedTime;

    // Calculate efficiency
    long double efficiency = speedup / numThreads;

    // Print the results
    std::cout << "\nPerformance Metrics:\n";
    std::cout << "Average Sequential Time: " << avgSequentialTime << " seconds\n";
    std::cout << "Average Multithreaded Time: " << avgMultithreadedTime << " seconds\n";
    std::cout << "Speedup: " << speedup << "\n";
    std::cout << "Efficiency: " << efficiency << "\n";

    return 0;
}
