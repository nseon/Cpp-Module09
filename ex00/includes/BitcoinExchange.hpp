/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:52:44 by nseon             #+#    #+#             */
/*   Updated: 2026/01/30 14:31:50 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>

#define DATAFILE "data.csv"

class BitcoinExchange {
	private:
		std::map<std::string, double> _map;
	public:
		BitcoinExchange();
		BitcoinExchange(char *input_file);
		BitcoinExchange(BitcoinExchange const &m);
		BitcoinExchange &operator=(BitcoinExchange const &m);
		~BitcoinExchange();
};
