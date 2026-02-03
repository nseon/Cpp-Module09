/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:52:53 by nseon             #+#    #+#             */
/*   Updated: 2026/02/03 10:48:29 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <time.h>
#include <algorithm>
#include <limits>
#include <utility>

#include "BitcoinExchange.hpp"

/* -------------------------------- */
/* --------------UTILS------------- */
/* -------------------------------- */

template <typename T>
static bool is_in(T elem, T *array, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (elem == array[i])
			return (1);
	}
	return (0);
}

static bool isALeapYear(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

static std::map<std::string, double>::iterator prev(std::map<std::string, double>::iterator i)
{
	std::advance(i, -1);
	return (i);
}

static std::logic_error BuildError(int nb_line, std::string err_msg, std::string file_name)
{
	std::stringstream ss;
	
	ss << file_name << ":" << nb_line << ": " << "\033[31m" << "error: " << "\033[0m" << err_msg;
	return (std::logic_error(ss.str()));
}

/* -------------------------------------- */
/* ----------------PARSING--------------- */
/* -------------------------------------- */

static std::string parse_date(std::string line, int nb_line, std::string file_name)
{
	tm t;
	int littlesmonths[] = {4, 6, 9, 11};
	char *end = strptime(line.c_str(), "%Y-%m-%d", &t);

	if (!end)
		throw BuildError(nb_line, "Date is poorly formatted: " + line, file_name);
	if (t.tm_mday > 30 && is_in<int>(t.tm_mon + 1, littlesmonths, 4))
		throw BuildError(nb_line, "This month has only 30 days: " + line, file_name);
	if (t.tm_mon == 1)
	{
		if (t.tm_mday > 28 && !isALeapYear(t.tm_year + 1900))
			throw BuildError(nb_line, "This month has only 28 days (this is'nt a leap year): " + line, file_name);
		if (t.tm_mday > 29 && isALeapYear(t.tm_year + 1900))
			throw BuildError(nb_line, "This month has only 28 days (this is'nt a leap year): " + line, file_name);
	}
	for (size_t i = 0; line[i] != *end; i++)
	{
		if (line[i + 1] == *end)
			line.resize(i + 1);
	}
	return (line);
}

static double parse_nb(std::string line, int nb_line, std::string file_name)
{
	std::stringstream ss(line);
	double nb;
	size_t i = line.find_first_not_of("0123456789");
	
	if (i != std::string::npos)
	{
		std::string line_cpy(line.substr(i + 1));
		if ((line[i] != '.' && !(line[i] == '-' && i == 0)) || line_cpy.find_first_not_of("0123456789") != std::string::npos)
			throw BuildError(nb_line, "Not a number: " + line, file_name);
	}
	ss >> nb;
	if (ss.fail())
		throw BuildError(nb_line, "Don't fit in a double: " + line, file_name);
	if (nb > std::numeric_limits<int>::max())
		throw BuildError(nb_line, "Number is too big: " + line, file_name);
	if (nb < 0)
		throw BuildError(nb_line, "Not a positive number: " + line, file_name);
	return (nb);
}

static std::pair<std::string, double> parse_line(std::string line, int nb_line, std::string sep, std::string file_name)
{
	std::string date = parse_date(line, nb_line, file_name);
	
	for (size_t i = 0; i < sep.size(); i++)
	{
		if (line[date.size() + i] != sep[i])
			throw BuildError(nb_line, "Invalid separator: " + line, file_name);
	}
	std::pair<std::string, double> p(date, parse_nb(line.substr(date.size() + sep.size()), nb_line, file_name));
	return (p);
}

static void parse_csv(std::map<std::string, double> &m)
{
	std::ifstream file(DATAFILE);
	std::string line;
	
	if (!file.is_open())
		throw std::logic_error("Failed to open: " + std::string(DATAFILE));
	std::getline(file, line);
	if (line != "date,exchange_rate")
			throw BuildError(1, "line is poorly formatted: " + line, DATAFILE);
	for (int i = 2; std::getline(file, line); i++)
		m.insert(parse_line(line, i, ",", DATAFILE));
}

static void parse_and_convert_to_btc(std::map<std::string, double> &data_m, std::string file_to_parse)
{
	std::ifstream file(file_to_parse.c_str());
	std::string line;
	std::pair<std::string, double> p;
	
	if (!file.is_open())
		throw std::logic_error("Failed to open: " + std::string(file_to_parse));
	std::getline(file, line);
	if (line != "date | value")
		throw BuildError(1, "line is poorly formatted: " + line, file_to_parse);
	for (int i = 2; std::getline(file, line); i++)
	{
		try {
			p = parse_line(line, i, " | ", file_to_parse);
			for (std::map<std::string, double>::iterator it = data_m.begin(); it != data_m.end(); it++)
			{
				if (p.first == (*it).first)
				{
					std::cout << p.first << " => " << p.second << " = " << p.second * (*it).second << std::endl;
					break;
				}
				if (p.first < (*it).first)
				{
					std::cout << p.first << " => " << p.second << " = " << p.second * (*prev(it)).second << std::endl;
					break;
				}
			}
		}
		catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
	}
}

/* --------------------------------------- */
/* --------------CONSTRUCTORS------------- */
/* --------------------------------------- */

BitcoinExchange::BitcoinExchange()
{
	parse_csv(_map);
}

BitcoinExchange::BitcoinExchange(char *input_file)
{
	parse_csv(_map);
	parse_and_convert_to_btc(_map, input_file);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &m) : _map(m._map)
{}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &m)
{
	if (this != &m)
		_map = m._map;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{}
