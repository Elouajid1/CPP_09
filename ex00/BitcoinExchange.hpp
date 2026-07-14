#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <exception>
#include <map>
#include <fstream>
#include <sstream>

class BitcoinExchange
{
    private :
        std::map<std::string, double> _database;
    public :
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& cpy);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();
        void loadData();
        void processFile(std::string& input);
        void processLine(std::string& line);
        bool isValidDate(std::string& date);
        bool isValidValue(double value);
};

#endif