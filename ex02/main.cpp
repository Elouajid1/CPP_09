#include "PmergeMe.hpp"
#include <iomanip>

template <typename Container>
void printContainer(const Container &c)
{
    for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

double getMicroSeconds(const struct timeval& start, const struct timeval& end)
{
    return ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
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
    if (!pm.parseInput(input))
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }
    
    std::cout << "Before : ";
    printContainer(pm.getVecInput());

    struct timeval start_vec, end_vec, start_deq, end_deq;
    gettimeofday(&start_vec, NULL);
    pm.sortVector();
    gettimeofday(&end_vec, NULL);

    gettimeofday(&start_deq, NULL);
    pm.sortDeque();
    gettimeofday(&end_deq, NULL);

    std::cout << "After : ";
    printContainer(pm.getMainVectorChain());

    double vect_duration = getMicroSeconds(start_vec, end_vec);
    double Deq_duration = getMicroSeconds(start_deq, end_deq);
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << pm.getVecInput().size() << " elements with std::vector : " << vect_duration << " us" << std::endl;
    std::cout << "Time to process a range of " << pm.getDeqInput().size() << " elements with std::deque : " << Deq_duration << " us" << std::endl;
}