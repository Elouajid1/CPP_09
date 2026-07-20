#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <deque>
#include <vector>

class PmergeMe
{
	private :
		std::deque<int> first;
		std::vector<int> second;
	
	public :
		PmergeMe();
		PmergeMe(const PmergeMe& cpy);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();
};

#endif