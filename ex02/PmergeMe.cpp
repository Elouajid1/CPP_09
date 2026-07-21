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

bool isnumber(std::string& str)
{
	if (str.empty())
		return (false);
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
	}
	return (true);
}

void PmergeMe::parseInput(const std::string& input)
{
	std::stringstream ss(input);
	std::string num;

	while (ss >> num)
	{
		if (!isnumber(num))
		{
			std::cerr << "Error: Wrong input!" << std::endl;
			return ;
		}
		std::stringstream convert(num);
		long token;
		convert >> token;
		if (convert.fail())
		{
			std::cerr << "Error: Wrong input!" << std::endl;
			return ;
		}
		if (token > std::numeric_limits<int>::max())
		{
			std::cerr << "Error: Wrong input!" << std::endl;
			return ;
		}
		int last = static_cast<int>(token);
		first.push_back(last);
		second.push_back(last);
	}
}

void PmergeMe::makeVectorPairs(std::vector<std::pair<int, int>>& pairs)
{
	for (int i = 0; i + 1 < second.size(); i+=2)
	{
		pairs.push_back(std::make_pair(second[i], second[i + 1]));
	}
	if (second.size() % 2 != 0)
	{
		hasOdd = true;
		oddElement = second[second.size() - 1];
	}
		
}

void PmergeMe::makeDequePairs(std::deque<std::pair<int, int>>& pairs)
{
	for (int i = 0; i + 1 < first.size(); i+=2)
	{
		pairs.push_back(std::make_pair(first[i], first[i + 1]));
	}
	if (first.size() % 2 != 0)
	{
		hasOdd = true;
		oddElement = first[first.size() - 1];
	}
}