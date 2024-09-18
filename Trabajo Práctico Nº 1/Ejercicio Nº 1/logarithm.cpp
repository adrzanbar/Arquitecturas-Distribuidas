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

class TaylorSeriesCalculator
{
public:
    TaylorSeriesCalculator(long double x, int numTerms) : x(x), numTerms(numTerms)
    {
        numThreads = std::thread::hardware_concurrency();
        if (numThreads == 0)
            numThreads = 2;
    }

    long double sequential() const
    {
        long double result = 0.0;
        long double term;
        long double y = (x - 1) / (x + 1);

        for (int n = 0; n < numTerms; ++n)
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

        auto worker = [&](int threadIndex)
        {
            long double localResult = 0.0;
            int chunkSize = numTerms / numThreads;
            int start = threadIndex * chunkSize;
            int end = (threadIndex == numThreads - 1) ? numTerms : start + chunkSize;
            long double y = (x - 1) / (x + 1);

            for (int n = start; n < end; ++n)
            {
                long double term = 1.0 / (2 * n + 1) * std::pow(y, 2 * n + 1);
                localResult += term;
            }

            std::lock_guard<std::mutex> guard(resultMutex);
            results[threadIndex] = localResult;
        };

        for (int i = 0; i < numThreads; ++i)
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

// Logging function with precision parameter
template <typename Func>
void log(const std::string &funcName, Func &&func, int precision)
{
    // Default precision to 1 if it is 0 or negative
    if (precision <= 0)
        precision = 1;

    std::cout << "Running: " << funcName << std::endl;
    auto startTime = std::chrono::high_resolution_clock::now();

    long double result = func();

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;

    // Set precision for the result output
    std::cout << std::fixed << std::setprecision(precision);
    std::cout << "Result: " << result << std::endl;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds." << std::endl;
}

int main()
{
    long double x = 1500000.0;
    int numTerms = 10000000;
    int precision = 15;

    std::cout << "Enter the value of x (default " << x << "): ";
    std::string xInput;
    std::getline(std::cin, xInput);
    if (!xInput.empty())
        x = std::stold(xInput);

    std::cout << "Enter the number of terms (default " << numTerms << "): ";
    std::string numTermsInput;
    std::getline(std::cin, numTermsInput);
    if (!numTermsInput.empty())
        numTerms = std::stoi(numTermsInput);

    TaylorSeriesCalculator calculator(x, numTerms);

    log("sequential", [&calculator]()
        { return calculator.sequential(); }, precision);
    std::cout << "Number of Threads: " << calculator.getNumThreads() << std::endl;
    log("multithreaded", [&calculator]()
        { return calculator.multithreaded(); }, precision);

    return 0;
}
