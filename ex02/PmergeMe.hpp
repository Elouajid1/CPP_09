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
		std::vector<int> mainVectorChain;
		std::deque<int> mainDequeChain;
		std::vector<int> pendingVectorChain;
		std::deque<int> pendingDequeChain;
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
		void sortEachPair(std::vector<std::pair<int, int>>& pairs);
		void sortEachPair(std::deque<std::pair<int, int>>& pairs);
		void sortPairs(std::vector<std::pair<int, int>>& pairs);
		void sortPairs(std::deque<std::pair<int, int>>& pairs);
		void buildChains(std::vector<std::pair<int, int>>& pairs);
		void buildChains(std::deque<std::pair<int, int>>& pairs);
		int findPosition(std::vector<int>& mainChain, int value);
		int findPosition(std::deque<int>& mainChain, int value);
};

#endif