#include "pattern_searcher.h"
#include <iostream>
#include <iomanip>

int main()
{
    PatternSearcher ps;

    ps.setText("data/texto.txt");
    ps.setPatterns("data/patrones.txt");

    // Report the results
    ps.report();

    // Print occurrences in a table format
    const auto &seqOccurrences = ps.getOccurrencesSequential();
    const auto &multiOccurrences = ps.getOccurrencesMultithreaded();

    // Print occurrences using getters
    std::cout << std::setw(20) << std::left << "Pattern"
              << std::setw(20) << "Occurrences (Seq)"
              << std::setw(20) << "Occurrences (Multi)"
              << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (const auto &pair : seqOccurrences)
    {
        std::string pattern = pair.first;
        unsigned int seqCount = pair.second;
        unsigned int multiCount = multiOccurrences.at(pattern); // Safe access

        std::cout << std::setw(30) << std::left << pattern
                  << std::setw(30) << seqCount
                  << std::setw(30) << multiCount
                  << std::endl;
    }
}
