#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <deque>
#include <vector>
#include <sstream>
#include <limits>

class PmergeMe
{
	private :
		std::deque<int> first;
		std::vector<int> second;
		int oddElement;
		bool hasOdd;
	
	public :
		PmergeMe();
		PmergeMe(const PmergeMe& cpy);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();
		void parseInput(const std::string& input);
		void makeDequePairs(std::deque<std::pair<int, int>>& pairs);
		void makeVectorPairs(std::vector<std::pair<int, int>>& pairs);
};

#endif