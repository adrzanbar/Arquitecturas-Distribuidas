#ifndef MATRIX_MULTIPLIER_H
#define MATRIX_MULTIPLIER_H

#include <vector>
#include "benchmark.h"
#include "matrix.h"

class MatrixMultiplier : public Benchmark
{
private:
    Matrix matrix1;
    Matrix matrix2;
    Matrix resultSequential;
    Matrix resultMultithreaded;
    bool compatibleDimensions();

public:
    MatrixMultiplier(const Matrix &matrix1, const Matrix &matrix2);
    void sequentialOperation() override;
    void multithreadedOperation() override;
    Matrix getMatrix1() const;
    Matrix getMatrix2() const;
    Matrix getResultSequential() const;
    Matrix getResultMultithreaded() const;
};

#endif
