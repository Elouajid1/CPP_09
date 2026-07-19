#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN& cpy) : storage(cpy.storage)
{
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		storage = other.storage;
	return (*this);
}

RPN::~RPN()
{
}

void RPN::applyOperation(char operation)
{
	int right;
	int left;
	int res;

	right = storage.top();
	storage.pop();
	left = storage.top();
	storage.pop();
	switch (operation)
	{
	case '+':
		res = left + right;
		break;
	case '-':
		res = left - right;
		break;
	case '*':
		res = left * right;
		break;
	case '/':
		if (right == 0)
			return;
		res = left / right;
		break;
	default:
		return ;
	}
	storage.push(res);
}

void RPN::calculate(const std::string& input)
{
	std::stringstream ss(input.c_str());
	std::string token;
	while (ss >> token)
	{
		if (token.size() == 1 && token[0] >= '0' && token[0] <= '9')
		{
			int res = token[0] - '0';
			storage.push(res);
		}
		else if (token.size() == 1 && (token == "+" || token == "-" || token == "*" || token == "/"))
		{
			if (storage.size() < 2)
			{
				std::cerr << "Error: Insufficient number to apply operation!" << std::endl;
				return ;
			}
			applyOperation(token[0]);
		}
		else
		{
			std::cerr << "Error: Invalid input!" << std::endl;
			return ;
		}
	}
	if (storage.size() != 1)
	{
		std::cerr << "Error: Invalid expression!" << std::endl;
		return;
	}
	else
		std::cout << storage.top() << std::endl;
}