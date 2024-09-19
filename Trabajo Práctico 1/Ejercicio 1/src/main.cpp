#include "ln_taylor_series.h"
#include <string>
#include <iomanip>

// Template function for getting user input with default values
template <typename T>
T getInput(const std::string &prompt, T defaultValue)
{
    std::cout << prompt << " (default: " << defaultValue << "): ";
    std::string input;
    std::getline(std::cin, input);
    if (input.empty())
    {
        return defaultValue;
    }
    try
    {
        if (std::is_same<T, int>::value)
        {
            return std::stoi(input);
        }
        else if (std::is_same<T, long double>::value)
        {
            return std::stod(input);
        }
        else if (std::is_same<T, unsigned int>::value)
        {
            return std::stoul(input);
        }
        else
        {
            throw std::invalid_argument("Unsupported type");
        }
    }
    catch (const std::invalid_argument &)
    {
        std::cerr << "Invalid input. Using default value: " << defaultValue << std::endl;
        return defaultValue;
    }
}

int main()
{
    LnTaylorSeries ln;

    long double defaultX = 1500000;
    unsigned int defaultNumTerms = 10000000;
    unsigned int defaultNumThreads = ln.getSystemNumTreads();

    long double x = getInput("Enter value of x", defaultX);
    unsigned int numTerms = getInput("Enter number of terms", defaultNumTerms);
    unsigned int numThreads = getInput("Enter number of threads", defaultNumThreads);

    ln.setX(x);
    ln.setNumTerms(numTerms);
    ln.setNumThreads(numThreads);
    ln.report();

    std::cout << std::fixed << std::setprecision(15);
    std::cout << "Sequential result: " << ln.getResultSequential() << std::endl;
    std::cout << "Multithreaded result: " << ln.getResultMultithreaded() << std::endl;

    return 0;
}