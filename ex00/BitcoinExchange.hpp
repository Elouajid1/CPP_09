#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <exception>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>


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
        void processFile(const std::string& input);
        void processLine(const std::string& line);
        bool isValidDate(const std::string& date);
        bool isValidValue(double value);
        double findExchangeRate(const std::string& date);
};

#endif