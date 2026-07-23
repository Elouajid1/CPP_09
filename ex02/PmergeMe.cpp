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

void PmergeMe::sortEachPair(std::vector<std::pair<int, int>>& pairs)
{
	for (int i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].first > pairs[i].second)
			std::swap(pairs[i].first, pairs[i].second);
	}
}

void PmergeMe::sortEachPair(std::deque<std::pair<int, int>>& pairs)
{
	for (int i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].first > pairs[i].second)
			std::swap(pairs[i].first, pairs[i].second);
	}
}

std::vector<std::pair<int, int>> mergePairs(std::vector<std::pair<int, int>>& left,
											std::vector<std::pair<int, int>>& right)
{
	std::vector<std::pair<int, int>> result;
	size_t i = 0;
	size_t j = 0;

	while (i < left.size() && j < right.size())
	{
		if (left[i].second < right[j].second)
		{
			result.push_back(left[i]);
			i++;
		}
		else
		{
			result.push_back(right[j]);
			j++;
		}
	}
	while (i < left.size())
	{
		result.push_back(left[i]);
		i++;
	}
	while (j < right.size())
	{
		result.push_back(right[j]);
		j++;
	}
	return (result);
}

std::deque<std::pair<int, int>> mergePairs(std::deque<std::pair<int, int>>& left,
											std::deque<std::pair<int, int>>& right)
{
	std::deque<std::pair<int, int>> result;
	size_t i = 0;
	size_t j = 0;

	while (i < left.size() && j < right.size())
	{
		if (left[i].second < right[j].second)
		{
			result.push_back(left[i]);
			i++;
		}
		else
		{
			result.push_back(right[j]);
			j++;
		}
	}
	while (i < left.size())
	{
		result.push_back(left[i]);
		i++;
	}
	while (j < right.size())
	{
		result.push_back(right[j]);
		j++;
	}
	return (result);
}

void PmergeMe::sortPairs(std::vector<std::pair<int, int>>& pairs)
{
	size_t mid;
	std::vector<std::pair<int, int>> left;
	std::vector<std::pair<int, int>> right;

	if (pairs.size() <= 1)
		return ;
	
	mid = pairs.size() / 2;
	for (size_t i = 0; i < mid; i++)
		left.push_back(pairs[i]);
	for (size_t i = mid; i < pairs.size(); i++)
		right.push_back(pairs[i]);
	
	sortPairs(left);
	sortPairs(right);

	pairs = mergePairs(left, right);
}

void PmergeMe::sortPairs(std::deque<std::pair<int, int>>& pairs)
{
	size_t mid;
	std::deque<std::pair<int, int>> left;
	std::deque<std::pair<int, int>> right;

	if (pairs.size() <= 1)
		return ;
	
	mid = pairs.size() / 2;
	for (size_t i = 0; i < mid; i++)
		left.push_back(pairs[i]);
	for (size_t i = mid; i < pairs.size(); i++)
		right.push_back(pairs[i]);
	
	sortPairs(left);
	sortPairs(right);

	pairs = mergePairs(left, right);
}

void PmergeMe::buildChains(std::vector<std::pair<int, int>>& pairs)
{
	for (int i = 0; i < pairs.size(); i++)
	{
		mainVectorChain.push_back(pairs[i].second);
		pendingVectorChain.push_back(pairs[i].first);
	}
	mainVectorChain.insert(mainVectorChain.begin(), pendingVectorChain[0]);
}

void PmergeMe::buildChains(std::deque<std::pair<int, int>>& pairs)
{
	for (int i = 0; i < pairs.size(); i++)
	{
		mainDequeChain.push_back(pairs[i].second);
		pendingDequeChain.push_back(pairs[i].first);
	}
	mainDequeChain.push_front(pendingDequeChain[0]);
}

int findPosition(std::vector<int>& mainChain, int value)
{
	int left = 0;
	int right = mainChain.size();

	while (left < right)
	{
		int mid = (left + right) / 2;
		if (mainChain[value] < mid)
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}