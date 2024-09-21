#include "matrix.h"
#include <random>
#include <ctime>
#include <iostream>

Matrix::Matrix(size_t rows, size_t cols)
    : data(rows, std::vector<float>(cols, 0.0f))
{
}

size_t Matrix::getRows() const
{
    return data.size();
}

size_t Matrix::getCols() const
{
    return data[0].size();
}

float Matrix::get(size_t row, size_t col) const
{
    return data[row][col];
}

void Matrix::set(size_t row, size_t col, float value)
{
    data[row][col] = value;
}

std::default_random_engine generator(static_cast<unsigned int>(std::time(0)));
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

Matrix Matrix::createRandomMatrix(size_t rows, size_t cols)
{
    Matrix matrix(rows, cols);

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix.set(i, j, distribution(generator));
        }
    }

    return matrix;
}

void Matrix::printCorners()
{
    if (getRows() == 0 || getCols() == 0)
    {
        std::cout << "Matrix is empty." << std::endl;
        return;
    }

    size_t rows = getRows();
    size_t cols = getCols();

    std::cout << get(0, 0) << " ... " << get(0, cols - 1) << std::endl;
    if (rows > 2)
    {
        std::cout << "... ... ..." << std::endl;
    }
    if (rows > 1)
    {
        std::cout << get(rows - 1, 0) << " ... " << get(rows - 1, cols - 1) << std::endl;
    }
}
