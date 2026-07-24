#include "PmergeMe.hpp"

template <typename Container>
void printContainer(const std::string &label, const Container &c)
{
    std::cout << label << ": ";
    for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void printPairs(const std::string &label, const std::vector<std::pair<int, int> > &pairs)
{
    std::cout << label << ": ";
    for (size_t i = 0; i < pairs.size(); i++)
        std::cout << "(" << pairs[i].first << "," << pairs[i].second << ") ";
    std::cout << std::endl;
}

void printPairs(const std::string &label, const std::deque<std::pair<int, int> > &pairs)
{
    std::cout << label << ": ";
    for (size_t i = 0; i < pairs.size(); i++)
        std::cout << "(" << pairs[i].first << "," << pairs[i].second << ") ";
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }

    std::string input;
    for (int i = 1; i < argc; i++)
    {
        input += argv[i];
        input += " ";
    }

    PmergeMe pm;
    pm.parseInput(input);

    std::cout << "=== INPUT ===" << std::endl;
    printContainer("Vector input", pm.getVecInput());
    printContainer("Deque input ", pm.getDeqInput());

    std::cout << "\n=== VECTOR PATH ===" << std::endl;
    std::vector<std::pair<int, int> > vecPairs;
    pm.makeVectorPairs(vecPairs);
    printPairs("Pairs (raw)", vecPairs);

    pm.sortEachVectorPair(vecPairs);
    printPairs("Pairs (each swapped so first<second)", vecPairs);

    pm.sortVectorPairs(vecPairs);
    printPairs("Pairs (recursively sorted by .second)", vecPairs);

    pm.buildVectorChains(vecPairs);
    printContainer("Main chain (before insert)", pm.getMainVectorChain());
    printContainer("Pending chain", pm.getPendingVectorChain());

    pm.insertVectorPending();
    printContainer("Main chain (AFTER insert = final sorted)", pm.getMainVectorChain());

    std::cout << "\n=== DEQUE PATH ===" << std::endl;
    std::deque<std::pair<int, int> > deqPairs;
    pm.makeDequePairs(deqPairs);
    printPairs("Pairs (raw)", deqPairs);

    pm.sortEachDequePair(deqPairs);
    printPairs("Pairs (each swapped so first<second)", deqPairs);

    pm.sortDequePairs(deqPairs);
    printPairs("Pairs (recursively sorted by .second)", deqPairs);

    pm.buildDequeChains(deqPairs);
    printContainer("Main chain (before insert)", pm.getMainDequeChain());
    printContainer("Pending chain", pm.getPendingDequeChain());

    pm.insertDequePending();
    printContainer("Main chain (AFTER insert = final sorted)", pm.getMainDequeChain());

    return (0);
}