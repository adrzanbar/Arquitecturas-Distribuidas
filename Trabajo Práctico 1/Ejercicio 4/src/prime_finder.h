#ifndef PRIME_FINDER_BENCHMARK_H
#define PRIME_FINDER_BENCHMARK_H

#include <vector>
#include "benchmark.h"

class PrimeFinder : public Benchmark
{
public:
    PrimeFinder();

    long long int getN() const;
    void setN(long long int N);

    std::vector<long long int> getResultSequential() const;
    std::vector<long long int> getResultMultithreaded() const;

private:
    long long int N;
    std::vector<long long int> resultSequential;
    std::vector<long long int> resultMultithreaded;

    bool isPrime(long long int num) const;

    void sequentialOperation() override;
    void multithreadedOperation() override;
};

#endif