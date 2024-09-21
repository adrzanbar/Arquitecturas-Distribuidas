#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix
{
private:
    std::vector<std::vector<float>> data;

public:
    Matrix(size_t rows, size_t cols);
    size_t getRows() const;
    size_t getCols() const;
    float get(size_t row, size_t col) const;
    void set(size_t row, size_t col, float value);
    static Matrix createRandomMatrix(size_t rows, size_t cols);
    void printCorners();
};

#endif
