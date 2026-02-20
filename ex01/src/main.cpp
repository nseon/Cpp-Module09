/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:59:28 by nseon             #+#    #+#             */
/*   Updated: 2026/02/20 14:02:56 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "RPN.hpp"

static bool isOp(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return (1);
	return (0);
}

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./RPN \"...\"" << std::endl;
		return (1);
	}

	RPN rpn;

	try {
		for (int i = 0; argv[1][i]; i++)
		{
			if (isdigit(argv[1][i]))
				rpn.addNumber(argv[1][i] - 48);
			else if (isOp(argv[1][i]))
				rpn.makeOperation(argv[1][i]);
			else if (argv[1][i] != ' ')
				throw BuildError(std::string("Not allowed char: ") + argv[1][i]);
		}
		rpn.print();
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
