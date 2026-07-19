#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& cpy): _database(cpy._database)
{}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_database = other._database;
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
		std::string value;
		size_t n = line.find(',');
		if (n == std::string::npos)
		{
			std::cout << "Error: Invalid format" << std::endl;
			return ;
		}
		key = line.substr(0, n);
		value = line.substr(n + 1, line.size());
		std::stringstream ss(value);
		double dvalue;
		ss >> dvalue;
		if (!ss.eof() || ss.fail())
		{
			std::cout << "Error : Invalid rate" << std::endl;
			return ;
		}
		_database.insert(std::make_pair(key, dvalue));
	}
}

std::string trimming(std::string& str)
{
	std::string res;
	size_t fpos = str.find_first_not_of(" \t");
	if (fpos == std::string::npos)
		return ("");
	size_t lpos = str.find_last_not_of(" \t");
	if (lpos == std::string::npos)
		return ("");
	res = str.substr(fpos, (lpos - fpos + 1));
	return (res);
}

double BitcoinExchange::findExchangeRate(const std::string& date)
{
	std::map<std::string, double>::iterator it = _database.lower_bound(date);
	if (it == _database.end())
	{
		--it;
		return (it->second);
	}
	else if (it->first == date)
		return (it->second);
	else
	{
		if (it == _database.begin())
			return (-1);
		--it;
		return (it->second);
	}
}

void BitcoinExchange::processLine(const std::string& line)
{
	std::string key;
	std::string value;
	size_t n = line.find('|');
	if (n == std::string::npos)
	{
		std::cout << "Error: bad Input => " << line << std::endl;
		return ;
	}
	key = line.substr(0, n);
	key = trimming(key);
	value = line.substr(n + 1);
	value = trimming(value);
	std::stringstream ss(value);
	double dvalue;
	ss >> dvalue;
	if (ss.fail() || !ss.eof())
	{
		std::cout << "Error : Invalid value" << std::endl;
		return ;
	}
	if (!isValidDate(key))
		return ;
	if (!isValidValue(dvalue))
	{
		return ;
	}
	double rate = findExchangeRate(key);
	double result = rate * dvalue;
	if (rate == -1)
	{
		std::cout << "Error: bad input" << std::endl;
		return ;
	}
	std::cout << key << " => " << dvalue << " = " << result << std::endl;
}

void BitcoinExchange::processFile(const std::string& input)
{
	std::ifstream file(input.c_str());
	if (!file.is_open())
	{
		fprintf(stderr, "can't open file\n");
		throw std::exception();
	}
	std::string line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		processLine(line);
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

bool BitcoinExchange::isValidDate(const std::string& date)
{
	if (date.size() != 10)
	{
		std::cout << "Error: Invalid date format!" << std::endl;
		return (false);
	}
	std::string year = date.substr(0, 4);
	std::string month = date.substr(5, 2);
	std::string day = date.substr(8, 2);
	if (date[4] != '-' || date[7] != '-')
	{
		std::cout << "Error: Invalid date format!" << std::endl;
		return (false);
	}
	if (!isnum(year) || !isnum(month) || !isnum(day))
	{
		std::cout << "Error: Invalid format!" << std::endl;
		return (false);
	}
	int mo = std::atoi(month.c_str());
	if (mo < 1 || mo > 12)
	{
		std::cout << "Error: Invalid month!" << std::endl;
		return (false);
	}
	int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int ye = std::atoi(year.c_str());
	if (ye % 400 == 0 || (ye % 4 == 0 && ye % 100 != 0))
		monthDays[2] = 29;
	int da = std::atoi(day.c_str());
	if (da < 1 || da > monthDays[mo])
	{
		std::cout << "Error: Invalid day" << std::endl;
		return (false);
	}
	return (true);
}

bool BitcoinExchange::isValidValue(double value)
{
	if (value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return (false);
	}
	if (value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return (false);
	}
	return (true);
}