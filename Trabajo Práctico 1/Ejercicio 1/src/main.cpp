#include "ln_taylor_series.h"
#include <string>
#include <iomanip>
#include "input_utils.h"

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