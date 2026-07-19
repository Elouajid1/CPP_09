#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>

class RPN
{
	private:
		std::stack<int> storage;
	public:
		RPN();
		RPN(const RPN& cpy);
		RPN& operator=(const RPN& other);
		~RPN();
		void calculate(const std::string& input);
		void applyOperation(char operation);
};


#endif