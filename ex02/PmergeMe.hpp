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

		void makeDequePairs(std::deque<std::pair<int, int> >& pairs);
		void sortEachDequePair(std::deque<std::pair<int, int> >& pairs);
		void sortDequePairs(std::deque<std::pair<int, int> >& pairs);
		void buildDequeChains(std::deque<std::pair<int, int> >& pairs);
		int findDequePosition(int value);

		void makeVectorPairs(std::vector<std::pair<int, int> >& pairs);
		void sortEachVectorPair(std::vector<std::pair<int, int> >& pairs);
		void sortVectorPairs(std::vector<std::pair<int, int> >& pairs);
		void buildVectorChains(std::vector<std::pair<int, int> >& pairs);
		int findVectorPosition(int value);
		std::vector<int> generateJacob();
		std::vector<int> generateInsertionOrder();
		void insertVectorPending();

		// PmergeMe.hpp — add to public section
		const std::vector<int> &getVecInput() const;
		const std::deque<int> &getDeqInput() const;
		const std::vector<int> &getMainVectorChain() const;
		const std::vector<int> &getPendingVectorChain() const;
		const std::deque<int> &getMainDequeChain() const;
		const std::deque<int> &getPendingDequeChain() const;
		void insertDequePending();
};

#endif