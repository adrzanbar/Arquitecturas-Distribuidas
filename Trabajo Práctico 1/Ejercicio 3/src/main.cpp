#include "input_utils.h"
#include "matrix_multiplier.h"

int main()
{

    unsigned int defaultN = 3000;
    unsigned int n = getInput("Enter the size of the matrix", defaultN);

    unsigned int defaultNumThreads = std::thread::hardware_concurrency();
    unsigned int numThreads = getInput("Enter the number of threads", defaultNumThreads);

    Matrix matrixA = Matrix::createRandomMatrix(n, n);
    Matrix matrixB = Matrix::createRandomMatrix(n, n);

    std::cout << "Matrix A:" << std::endl;
    matrixA.printCorners();

    std::cout << "Matrix B:" << std::endl;
    matrixB.printCorners();

    MatrixMultiplier multiplier(matrixA, matrixB);
    multiplier.setNumThreads(numThreads);
    multiplier.report();

    std::cout << "Result sequential:" << std::endl;
    multiplier.getResultSequential().printCorners();

    std::cout << "Result multithreaded:" << std::endl;
    multiplier.getResultMultithreaded().printCorners();

    return 0;
}