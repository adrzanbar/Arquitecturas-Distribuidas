#include "ln_taylor_series.h"
#include <cmath>
#include <vector>
#include <thread>
#include <mutex>
#include <numeric>

long double LnTaylorSeries::calculateTerm(unsigned int n) const
{
    return 1.0 / (2 * n + 1) * std::pow(auxTerm, 2 * n + 1);
}

void LnTaylorSeries::sequentialOperation()
{
    resultSequential = 0.0;
    for (unsigned int n = 0; n < numTerms; ++n)
    {
        resultSequential += calculateTerm(n);
    }

    resultSequential *= 2;
}

void LnTaylorSeries::multithreadedOperation()
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

        for (unsigned int n = start; n < end; ++n)
        {
            localResult += calculateTerm(n);
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

    resultMultithreaded = 2 * std::accumulate(results.begin(), results.end(), 0.0);
}

void LnTaylorSeries::setX(long double x)
{
    this->x = x;
    this->auxTerm = (x - 1) / (x + 1);
}

void LnTaylorSeries::setNumTerms(unsigned int numTerms)
{
    this->numTerms = numTerms;
}

long double LnTaylorSeries::getResultSequential()
{
    return resultSequential;
}

long double LnTaylorSeries::getResultMultithreaded()
{
    return resultMultithreaded;
}
