#ifndef PATTERNSEARCHER_H
#define PATTERNSEARCHER_H

#include "benchmark.h"
#include <string>
#include <vector>
#include <map>
#include <mutex>

class PatternSearcher : public Benchmark
{
private:
    std::string text;
    std::map<std::string, unsigned int> occurrencesSequential;
    std::map<std::string, unsigned int> occurrencesMultithreaded;
    unsigned int search(const std::string &pattern);

public:
    PatternSearcher() = default;

    void setPatterns(const std::string &fileName);
    void setText(const std::string &fileName);

    void sequentialOperation() override;
    void multithreadedOperation() override;

    const std::map<std::string, unsigned int> &getOccurrencesSequential() const;
    const std::map<std::string, unsigned int> &getOccurrencesMultithreaded() const;
};

#endif
