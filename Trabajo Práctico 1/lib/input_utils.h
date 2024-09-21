#include <iostream>
#include <string>
#include <type_traits>
#include <stdexcept>

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
        else if (std::is_same<T, long long int>::value)
        {
            return std::stoll(input);
        }
        else
        {
            throw std::invalid_argument("Unsupported type");
        }
    }
    catch (const std::invalid_argument &)
    {
        std::cerr << "Invalid input. Using default value." << std::endl;
        return defaultValue;
    }
    catch (const std::out_of_range &)
    {
        std::cerr << "Input out of range. Using default value." << std::endl;
        return defaultValue;
    }
}