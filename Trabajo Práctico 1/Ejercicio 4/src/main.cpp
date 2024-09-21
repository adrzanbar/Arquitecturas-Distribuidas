#include "prime_finder.h"
#include "input_utils.h"
#include <iostream>
#include <vector>

int main()
{
    long long int defaultN = 10e7;

    long long int N = getInput("Enter N", defaultN);

    if (N < 10e7)
    {
        std::cout << "N must be greater than 10e7" << std::endl;
        return 1;
    }

    PrimeFinder primeFinder;
    primeFinder.setN(N);

    primeFinder.report();

    std::vector<long long int> sequentialResult = primeFinder.getResultSequential();
    std::vector<long long int> last10Sequential(sequentialResult.end() - 10, sequentialResult.end());

    std::cout << "Top 10 prime numbers (sequential): ";
    for (const auto &prime : last10Sequential)
    {
        std::cout << prime << " ";
    }
    std::cout << std::endl;

    std::vector<long long int> multithreadedResult = primeFinder.getResultMultithreaded();
    std::vector<long long int> last10Multithreaded(multithreadedResult.end() - 10, multithreadedResult.end());

    std::cout << "Top 10 prime numbers (multithreaded): ";
    for (const auto &prime : last10Multithreaded)
    {
        std::cout << prime << " ";
    }
    std::cout << std::endl;

    return 0;
}