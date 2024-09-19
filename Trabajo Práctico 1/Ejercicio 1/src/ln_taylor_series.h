#ifndef TAYLOR_SERIES_H
#define TAYLOR_SERIES_H

#include "benchmark.h"

class LnTaylorSeries : public Benchmark
{
public:
    void sequentialOperation() override;
    void multithreadedOperation() override;
    void setX(long double x);
    void setNumTerms(unsigned int numTerms);
    long double getResultSequential();
    long double getResultMultithreaded();

private:
    long double calculateTerm(unsigned int n) const;
    long double x;
    long double auxTerm;
    unsigned int numTerms;
    long double resultSequential;
    long double resultMultithreaded;
};

#endif
