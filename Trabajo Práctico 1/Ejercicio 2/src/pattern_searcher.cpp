#include "pattern_searcher.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

unsigned int PatternSearcher::search(const std::string &pattern)
{
    unsigned int count = 0;
    size_t pos = text.find(pattern);
    while (pos != std::string::npos)
    {
        ++count;
        pos = text.find(pattern, pos + 1);
    }
    return count;
}

void PatternSearcher::setPatterns(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    occurrencesSequential.clear();    // Clear existing data
    occurrencesMultithreaded.clear(); // Clear existing data

    std::string pattern;
    while (std::getline(file, pattern))
    {
        if (!pattern.empty())
        {
            occurrencesSequential[pattern] = 0;    // Initialize for sequential
            occurrencesMultithreaded[pattern] = 0; // Initialize for multithreaded
        }
    }
    file.close();

    numThreads = occurrencesMultithreaded.size(); // Update number of threads based on patterns
}

void PatternSearcher::setText(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }
    text.assign((std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
}

void PatternSearcher::sequentialOperation()
{
    for (auto &entry : occurrencesSequential)
    {
        entry.second = 0;
    }

    for (auto &entry : occurrencesSequential)
    {
        entry.second = search(entry.first);
    }
}

void PatternSearcher::multithreadedOperation()
{
    for (auto &entry : occurrencesMultithreaded)
    {
        entry.second = 0;
    }

    std::vector<std::thread> threads;
    std::mutex mtx;

    auto searchAndUpdate = [this, &mtx](const std::string &pattern)
    {
        unsigned int count = search(pattern);
        std::lock_guard<std::mutex> guard(mtx);
        occurrencesMultithreaded[pattern] = count;
    };

    for (const auto &entry : occurrencesMultithreaded)
    {
        threads.emplace_back(searchAndUpdate, entry.first);
    }

    for (auto &t : threads)
    {
        t.join();
    }
}

const std::map<std::string, unsigned int> &PatternSearcher::getOccurrencesSequential() const
{
    return occurrencesSequential;
}

const std::map<std::string, unsigned int> &PatternSearcher::getOccurrencesMultithreaded() const
{
    return occurrencesMultithreaded;
}
