#include "prime_finder.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <algorithm>
#include <mutex>

PrimeFinder::PrimeFinder() : N(0) {
    numThreads = systemNumTreads;
}

long long int PrimeFinder::getN() const
{
    return N;
}

void PrimeFinder::setN(long long int N)
{
    this->N = N;
}

bool PrimeFinder::isPrime(long long int num) const
{
    if (num % 2 == 0 || num % 3 == 0)
        return false;
    for (long long int i = 5; i * i <= num; i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

void PrimeFinder::sequentialOperation()
{
    resultSequential.clear();

    if (N <= 2)
    {
        return;
    }

    resultSequential.push_back(2);

    for (long long int i = 3; i < N; i += 2)
    {
        if (isPrime(i))
        {
            resultSequential.push_back(i);
        }
    }
}

void PrimeFinder::multithreadedOperation()
{
    resultMultithreaded.clear();

    if (N <= 2)
    {
        return;
    }

    resultMultithreaded.push_back(2);

    std::vector<std::thread> threads;
    std::mutex mtx;

    auto worker = [this, &mtx](long long int start, long long int end)
    {
        std::vector<long long int> localPrimes;
        for (long long int i = start; i < end; i += 2)
        {
            if (isPrime(i))
            {
                localPrimes.push_back(i);
            }
        }
        std::lock_guard<std::mutex> lock(mtx);
        resultMultithreaded.insert(resultMultithreaded.end(), localPrimes.begin(), localPrimes.end());
    };

    long long int range = (N - 3) / numThreads;
    for (long long int t = 0; t < numThreads; ++t)
    {
        long long int start = 3 + t * range;
        if (start % 2 == 0)
        {
            start++;
        }
        long long int end = (t == numThreads - 1) ? N : start + range;
        threads.emplace_back(worker, start, end);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    std::sort(resultMultithreaded.begin(), resultMultithreaded.end());
}

std::vector<long long int> PrimeFinder::getResultSequential() const
{
    return resultSequential;
}

std::vector<long long int> PrimeFinder::getResultMultithreaded() const
{
    return resultMultithreaded;
}
