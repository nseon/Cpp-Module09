/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:19:23 by nseon             #+#    #+#             */
/*   Updated: 2026/02/12 17:21:38 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <deque>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <ctime>

#include "PmergeMe.hpp"

static std::logic_error BuildError(std::string elem, std::string err_msg)
{
	std::stringstream ss;
	
	ss << "\033[31m" << "error: " << "\033[0m" << "\033[1;97m" << elem << "\033[0m" << ' ' << err_msg;
	return (std::logic_error(ss.str()));
}

static void parse_nb(char *input)
{
	std::stringstream ss(input);
	int nb;
	
	ss >> nb;
	if (ss.fail() || (std::string(input).find_first_not_of("0123456789") != std::string::npos))
		throw BuildError(input, "is not a positiv int");
}

static int parse_input(int argc, char **argv)
{
	int is_good = 1;

	for (int i = 0; i < argc; i++)
	{
		try {
			parse_nb(argv[i]);
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
			is_good = 0;
		}
	}
	return (is_good);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Not enough args\nUsage: ./PmergeMe numbers" << std::endl;
		return (1);
	}
	if (!parse_input(argc - 1, argv + 1))
		return (1);

	std::vector<int> vec;
	std::deque<int> deq;

	std::cout << "\033[1;97m" << "Before:" << "\033[0m";
	for (int i = 1; argv[i]; ++i)
	{
		std::cout << " " << argv[i];
		vec.push_back(std::atoi(argv[i]));
		deq.push_back(std::atoi(argv[i]));
	}
	std::cout << std::endl;
	clock_t start = clock();
	PmergeMe::sort_vec(vec);
	clock_t end = clock();
	std::cout << "\033[1;97m" << "After:" << "\033[0m";
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << ' ' << vec[i];
	std::cout << std::endl;
	std::cout << "\033[1;97m" << "Time to process a range of " << argc - 1 << " elements with std::vector: " << "\033[0m" << (end - start) << " µs" << std::endl;
	start = clock();
	PmergeMe::sort_deq(deq);
	end = clock();
	std::cout << "\033[1;97m" << "Time to process a range of " << argc - 1 << " elements with std::deque: " << "\033[0m" << (end - start) << " µs" << std::endl;
	return (0);
}
