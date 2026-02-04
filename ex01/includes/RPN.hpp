/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:59:19 by nseon             #+#    #+#             */
/*   Updated: 2026/02/04 15:58:29 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>

class RPN {
	private:
		std::stack<int> _stack;
	public:
		RPN();
		RPN(RPN const &m);
		RPN &operator=(RPN const &m);
		~RPN();
	
		void addNumber(int nb);
		void makeOperation(char op);
		void print();
};

std::logic_error BuildError(std::string err_msg);
