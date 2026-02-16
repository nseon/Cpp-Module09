/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:19:04 by nseon             #+#    #+#             */
/*   Updated: 2026/02/12 13:47:49 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <deque>

class PmergeMe {
	private:
		PmergeMe();
		PmergeMe(PmergeMe const &m);
		PmergeMe &operator=(PmergeMe const &m);
		~PmergeMe();
	public:
		static void sort_vec(std::vector<int> &container);
		static void sort_deq(std::deque<int> container);
};

#include "../src/PmergeMe.cpp"
