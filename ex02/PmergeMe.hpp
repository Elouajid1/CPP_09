#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <deque>
#include <vector>
#include <sstream>
#include <limits>
#include <sys/time.h>

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

		void makeDequePairs(std::deque<std::pair<int, int> >& pairs);
		void sortEachDequePair(std::deque<std::pair<int, int> >& pairs);
		void sortDequePairs(std::deque<std::pair<int, int> >& pairs);
		void buildDequeChains(std::deque<std::pair<int, int> >& pairs);
		int findDequePosition(int value);
		std::deque<int> generateDequeJacob();
		std::deque<int> generateDequeInsertionOrder();
		void insertDequePending();

		void makeVectorPairs(std::vector<std::pair<int, int> >& pairs);
		void sortEachVectorPair(std::vector<std::pair<int, int> >& pairs);
		void sortVectorPairs(std::vector<std::pair<int, int> >& pairs);
		void buildVectorChains(std::vector<std::pair<int, int> >& pairs);
		int findVectorPosition(int value);
		std::vector<int> generateVectorJacob();
		std::vector<int> generateVectorInsertionOrder();
		void insertVectorPending();

	public :
		PmergeMe();
		PmergeMe(const PmergeMe& cpy);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();
		bool parseInput(const std::string& input);

		const std::vector<int> &getVecInput() const;
		const std::deque<int> &getDeqInput() const;
		const std::vector<int> &getMainVectorChain() const;
		const std::vector<int> &getPendingVectorChain() const;
		const std::deque<int> &getMainDequeChain() const;
		const std::deque<int> &getPendingDequeChain() const;

		void sortVector();
		void sortDeque();
};

#endif