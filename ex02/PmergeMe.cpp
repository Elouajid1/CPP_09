#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : oddElement(0), hasOdd(false)
{}

PmergeMe::PmergeMe(const PmergeMe &cpy) : first(cpy.first), second(cpy.second), mainVectorChain(cpy.mainVectorChain), mainDequeChain(cpy.mainDequeChain),
										  pendingVectorChain(cpy.pendingVectorChain), pendingDequeChain(cpy.pendingDequeChain),
										  oddElement(cpy.oddElement), hasOdd(cpy.hasOdd)
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		first = other.first;
		second = other.second;
		mainVectorChain = other.mainVectorChain;
		mainDequeChain = other.mainDequeChain;
		pendingVectorChain = other.pendingVectorChain;
		pendingDequeChain = other.pendingDequeChain;
		oddElement = other.oddElement;
		hasOdd = other.hasOdd;
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

bool PmergeMe::parseInput(const std::string& input)
{
	std::stringstream ss(input);
	std::string num;

	while (ss >> num)
	{
		if (!isnumber(num))
			return (false);
		std::stringstream convert(num);
		long token;
		convert >> token;
		if (convert.fail())
			return (false);
		if (token > std::numeric_limits<int>::max())
			return (false);
		int last = static_cast<int>(token);
		first.push_back(last);
		second.push_back(last);
	}
	return (true);
}

									/////////////////////////////////VECTOR///////////////////////////////////////

void PmergeMe::makeVectorPairs(std::vector<std::pair<int, int> >& pairs)
{
	for (size_t i = 0; i + 1 < second.size(); i+=2)
	{
		pairs.push_back(std::make_pair(second[i], second[i + 1]));
	}
	if (second.size() % 2 != 0)
	{
		hasOdd = true;
		oddElement = second[second.size() - 1];
	}
		
}

void PmergeMe::sortEachVectorPair(std::vector<std::pair<int, int> >& pairs)
{
	for (size_t i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].first > pairs[i].second)
			std::swap(pairs[i].first, pairs[i].second);
	}
}

std::vector<std::pair<int, int> > mergePairs(std::vector<std::pair<int, int> >& left,
											std::vector<std::pair<int, int> >& right)
{
	std::vector<std::pair<int, int> > result;
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

void PmergeMe::sortVectorPairs(std::vector<std::pair<int, int> >& pairs)
{
	size_t mid;
	std::vector<std::pair<int, int> > left;
	std::vector<std::pair<int, int> > right;

	if (pairs.size() <= 1)
		return ;
	
	mid = pairs.size() / 2;
	for (size_t i = 0; i < mid; i++)
		left.push_back(pairs[i]);
	for (size_t i = mid; i < pairs.size(); i++)
		right.push_back(pairs[i]);
	
	sortVectorPairs(left);
	sortVectorPairs(right);

	pairs = mergePairs(left, right);
}

void PmergeMe::buildVectorChains(std::vector<std::pair<int, int> >& pairs)
{
	if (pairs.empty())
	{
		if (hasOdd)
			mainVectorChain.push_back(oddElement);
		return ;
	}
	for (size_t i = 0; i < pairs.size(); i++)
	{
		mainVectorChain.push_back(pairs[i].second);
		pendingVectorChain.push_back(pairs[i].first);
	}
	mainVectorChain.insert(mainVectorChain.begin(), pendingVectorChain[0]);
}

int PmergeMe::findVectorPosition(int value)
{
	int left = 0;
	int right = mainVectorChain.size();

	while (left < right)
	{
		int mid = (left + right) / 2;
		if (mainVectorChain[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}

std::vector<int> PmergeMe::generateVectorJacob()
{
	std::vector<int> jacob;
	jacob.push_back(1);
	jacob.push_back(3);

	while (jacob.back() < static_cast<int>(pendingVectorChain.size()))
	{
		int next = jacob.back() + 2 * jacob[jacob.size() - 2];
		jacob.push_back(next);
	}
	return (jacob);
}

std::vector<int> PmergeMe::generateVectorInsertionOrder()
{
	std::vector<int> jacob = generateVectorJacob();

	std::vector<int> order;
	int previous = 1;
	for (size_t i = 1; i < jacob.size(); i++)
	{
		if (jacob[i] > static_cast<int>(pendingVectorChain.size()))
			jacob[i] = pendingVectorChain.size();
		int current = jacob[i];
		int value = current;
		while (value > previous)
		{
			order.push_back(value);
			value--;
		}
		previous = current;
	}
	return (order);
}

void PmergeMe::insertVectorPending()
{
	std::vector<int> order = generateVectorInsertionOrder();

	for (size_t i = 0; i < order.size(); i++)
	{
		int value = pendingVectorChain[order[i] - 1];
		int position = findVectorPosition(value);

		mainVectorChain.insert(mainVectorChain.begin() + position, value);
	}

	if (hasOdd)
	{
		int position = findVectorPosition(oddElement);
		mainVectorChain.insert(mainVectorChain.begin() + position, oddElement);
	}
}


void PmergeMe::sortVector()
{
	std::vector<std::pair<int, int> > pairs;
	makeVectorPairs(pairs);
	sortEachVectorPair(pairs);
	sortVectorPairs(pairs);
	buildVectorChains(pairs);
	insertVectorPending();
}
								///////////////////////////////////DEQUE//////////////////////////////////////////


void PmergeMe::makeDequePairs(std::deque<std::pair<int, int> >& pairs)
{
	for (size_t i = 0; i + 1 < first.size(); i+=2)
	{
		pairs.push_back(std::make_pair(first[i], first[i + 1]));
	}
	if (first.size() % 2 != 0)
	{
		hasOdd = true;
		oddElement = first[first.size() - 1];
	}
}

void PmergeMe::sortEachDequePair(std::deque<std::pair<int, int> >& pairs)
{
	for (size_t i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].first > pairs[i].second)
			std::swap(pairs[i].first, pairs[i].second);
	}
}

std::deque<std::pair<int, int> > mergePairs(std::deque<std::pair<int, int> >& left,
											std::deque<std::pair<int, int> >& right)
{
	std::deque<std::pair<int, int> > result;
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

void PmergeMe::sortDequePairs(std::deque<std::pair<int, int> >& pairs)
{
	size_t mid;
	std::deque<std::pair<int, int> > left;
	std::deque<std::pair<int, int> > right;

	if (pairs.size() <= 1)
		return ;
	
	mid = pairs.size() / 2;
	for (size_t i = 0; i < mid; i++)
		left.push_back(pairs[i]);
	for (size_t i = mid; i < pairs.size(); i++)
		right.push_back(pairs[i]);
	
	sortDequePairs(left);
	sortDequePairs(right);

	pairs = mergePairs(left, right);
}

void PmergeMe::buildDequeChains(std::deque<std::pair<int, int> >& pairs)
{
	if (pairs.empty())
	{
		if (hasOdd)
			mainDequeChain.push_back(oddElement);
		return;
	}
	for (size_t i = 0; i < pairs.size(); i++)
	{
		mainDequeChain.push_back(pairs[i].second);
		pendingDequeChain.push_back(pairs[i].first);
	}
	mainDequeChain.push_front(pendingDequeChain[0]);
}

int PmergeMe::findDequePosition(int value)
{
	int left = 0;
	int right = mainDequeChain.size();

	while (left < right)
	{
		int mid = (left + right) / 2;
		if (mainDequeChain[mid] < value)
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}

std::deque<int> PmergeMe::generateDequeJacob()
{
	std::deque<int> jacob;
	jacob.push_back(1);
	jacob.push_back(3);

	while (jacob.back() < static_cast<int>(pendingDequeChain.size()))
	{
		int next = jacob.back() + 2 * jacob[jacob.size() - 2];
		jacob.push_back(next);
	}
	return (jacob);
}

std::deque<int> PmergeMe::generateDequeInsertionOrder()
{
	std::deque<int> jacob = generateDequeJacob();

	std::deque<int> order;
	int previous = 1;
	for (size_t i = 1; i < jacob.size(); i++)
	{
		if (jacob[i] > static_cast<int>(pendingDequeChain.size()))
			jacob[i] = pendingDequeChain.size();
		int current = jacob[i];
		int value = current;
		while (value > previous)
		{
			order.push_back(value);
			value--;
		}
		previous = current;
	}
	return (order);
}

void PmergeMe::insertDequePending()
{
	std::deque<int> order = generateDequeInsertionOrder();

	for (size_t i = 0; i < order.size(); i++)
	{
		int value = pendingDequeChain[order[i] - 1];
		int position = findDequePosition(value);

		mainDequeChain.insert(mainDequeChain.begin() + position, value);
	}

	if (hasOdd)
	{
		int position = findDequePosition(oddElement);
		mainDequeChain.insert(mainDequeChain.begin() + position, oddElement);
	}
}

void PmergeMe::sortDeque()
{
	std::deque<std::pair<int, int> > pairs;
	makeDequePairs(pairs);
	sortEachDequePair(pairs);
	sortDequePairs(pairs);
	buildDequeChains(pairs);
	insertDequePending();
}

									//////////////////////////////GETTERS////////////////////////////////////

const std::vector<int> &PmergeMe::getVecInput() const
{
	return second;
}
const std::deque<int> &PmergeMe::getDeqInput() const 
{ 
	return first; 
}
const std::vector<int> &PmergeMe::getMainVectorChain() const 
{ 
	return mainVectorChain; 
}
const std::vector<int> &PmergeMe::getPendingVectorChain() const 
{ 
	return pendingVectorChain; 
}
const std::deque<int> &PmergeMe::getMainDequeChain() const 
{ 
	return mainDequeChain; 
}
const std::deque<int> &PmergeMe::getPendingDequeChain() const 
{ 
	return pendingDequeChain; 
}