#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./btc input.txt" << std::endl;
        return (1);
    }

    BitcoinExchange btc;
    btc.loadData();
    btc.processFile(argv[1]);

    return (0);
}