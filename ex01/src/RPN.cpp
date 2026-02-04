/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:59:33 by nseon             #+#    #+#             */
/*   Updated: 2026/02/04 15:58:19 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <stdexcept>
#include <iostream>

#include "RPN.hpp"

std::logic_error BuildError(std::string err_msg)
{
	std::stringstream ss;
	
	ss << "\033[31m" << "error: " << "\033[0m" << err_msg;
	return (std::logic_error(ss.str()));
}

void RPN::addNumber(int nb)
{
	_stack.push(nb);
}

void RPN::makeOperation(char op)
{
	if (_stack.size() < 2)
		throw BuildError(std::string("Not enought numbers in stack to make the following operation: ") + op);
	int nb2 = _stack.top();
	_stack.pop();
	int nb1 = _stack.top();
	_stack.pop();
	switch (op)
	{
		case '+':
		{
			_stack.push(nb1 + nb2);
			break;
		}
		case '-':
		{
			_stack.push(nb1 - nb2);
			break;
		}
		case '/':
		{
			if (nb2 == 0)
				throw BuildError("Division by 0 not allowed");
			_stack.push(nb1 / nb2);
			break ;
		}
		case '*':
		{
			_stack.push(nb1 * nb2);
			break;
		}
	}
}

void RPN::print()
{
	std::cout << _stack.top() << std::endl;
}

/* --------------------------------------- */
/* --------------CONSTRUCTORS------------- */
/* --------------------------------------- */

RPN::RPN()
{}

RPN::RPN(RPN const &m) : _stack(m._stack)
{}

RPN &RPN::operator=(RPN const &m)
{
	if (this != &m)
		_stack = m._stack;
	return (*this);
}

RPN::~RPN()
{}
