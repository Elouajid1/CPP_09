#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe& cpy) : first(cpy.first), second(cpy.second)
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        first = other.first;
        second = other.second;
    }
    return (*this);
}

PmergeMe::~PmergeMe()
{}

