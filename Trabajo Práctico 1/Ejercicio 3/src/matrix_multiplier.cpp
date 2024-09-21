#include "matrix_multiplier.h"
#include <thread>
#include <iostream>
#include <algorithm>

#include "matrix_multiplier.h"
#include <thread>
#include <iostream>
#include <algorithm>

MatrixMultiplier::MatrixMultiplier(const Matrix &matrix1, const Matrix &matrix2)
    : matrix1(matrix1), matrix2(matrix2), resultSequential(matrix1.getRows(), matrix2.getCols()), resultMultithreaded(matrix1.getRows(), matrix2.getCols())
{
    numThreads = systemNumTreads;
}

bool MatrixMultiplier::compatibleDimensions()
{
    return matrix1.getCols() == matrix2.getRows();
}

void MatrixMultiplier::sequentialOperation()
{
    if (!compatibleDimensions())
    {
        std::cerr << "Matrix dimensions are not compatible for multiplication." << std::endl;
        return;
    }

    for (size_t i = 0; i < matrix1.getRows(); i++)
    {
        for (size_t j = 0; j < matrix2.getCols(); j++)
        {
            double sum = 0;
            for (size_t k = 0; k < matrix1.getCols(); k++)
            {
                sum += matrix1.get(i, k) * matrix2.get(k, j);
            }
            resultSequential.set(i, j, sum);
        }
    }
}

void MatrixMultiplier::multithreadedOperation()
{
    if (!compatibleDimensions())
    {
        std::cerr << "Matrix dimensions are not compatible for multiplication." << std::endl;
        return;
    }

    auto worker = [this](size_t startRow, size_t endRow)
    {
        for (size_t i = startRow; i < endRow; i++)
        {
            for (size_t j = 0; j < matrix2.getCols(); j++)
            {
                double sum = 0;
                for (size_t k = 0; k < matrix1.getCols(); k++)
                {
                    sum += matrix1.get(i, k) * matrix2.get(k, j);
                }
                resultMultithreaded.set(i, j, sum);
            }
        }
    };

    size_t numThreads = std::thread::hardware_concurrency();
    size_t rowsPerThread = matrix1.getRows() / numThreads;
    std::vector<std::thread> threads;

    for (size_t t = 0; t < numThreads; ++t)
    {
        size_t startRow = t * rowsPerThread;
        size_t endRow = (t == numThreads - 1) ? matrix1.getRows() : startRow + rowsPerThread;
        threads.emplace_back(worker, startRow, endRow);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }
}

Matrix MatrixMultiplier::getMatrix1() const
{
    return matrix1;
}

Matrix MatrixMultiplier::getMatrix2() const
{
    return matrix2;
}

Matrix MatrixMultiplier::getResultSequential() const
{
    return resultSequential;
}

Matrix MatrixMultiplier::getResultMultithreaded() const
{
    return resultMultithreaded;
}
