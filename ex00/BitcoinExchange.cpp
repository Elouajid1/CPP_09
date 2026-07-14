#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& cpy): _database(cpy._database)
{}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		_database = other._database;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{}

void BitcoinExchange::loadData()
{
	std::ifstream data("data.csv");
	if (!data.is_open())
		throw std::exception();
	
	std::string line;
	std::getline(data, line);
	while (std::getline(data, line))
	{
		std::string key;
		double value;
		size_t n = line.find(',');
		if (n == std::string::npos)
			throw std::exception();
		key = line.substr(0, n);
		value = std::stod(line.substr(n + 1, line.size()));
		_database.insert({key, value});
	}
}

void BitcoinExchange::processLine(std::string& line)
{
	std::string key;
	double value;
	size_t n = line.find('|');
	if (n == std::string::npos)
		throw std::exception();
	key = line.substr(0, n);
	value = std::stod(line.substr(n + 1));

}

void BitcoinExchange::processFile(std::string& input)
{
	std::ifstream file(input);
	if (!file.is_open())
	{
		fprintf(stderr, "can't open file\n");
		throw std::exception();
	}
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{

	}
}

bool isnum(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
	}
	return (true);
}

bool BitcoinExchange::isValidDate(std::string& date)
{
	if (date.size() != 10)
		return (false);
	std::string year = date.substr(0, 4);
	std::string month = date.substr(5, 2);
	std::string day = date.substr(8, 2);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	if (!isnum(year) || !isnum(month) || !isnum(day))
		return (false);
	int mo = std::atoi(month.c_str());
	if (mo < 1 || mo > 12)
		return (false);
	int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int ye = std::atoi(year.c_str());
	if (ye % 400 == 0 || (ye % 4 == 0 && ye % 100 != 0))
		monthDays[2] = 29;
	int da = std::atoi(day.c_str());
	if (da < 1 || da > monthDays[mo])
		return (false);
	return (true);
}

bool BitcoinExchange::isValidValue(double value)
{
	
}