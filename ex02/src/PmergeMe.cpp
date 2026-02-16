/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:19:16 by nseon             #+#    #+#             */
/*   Updated: 2026/02/16 13:27:18 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utility>
#include <string>
#include <algorithm>

#include "PmergeMe.hpp"

/* --------------------------------------- */
/* -----------------UTILS----------------- */
/* --------------------------------------- */

template <typename T>
T generate_jacobsthal(size_t n)
{
	T sequence;

	sequence.push_back(1);
	sequence.push_back(3);
	
	int next_val = 3;
	while (next_val < static_cast<int>(n))
	{
		next_val = 2 * sequence[sequence.size() - 2] + sequence[sequence.size() - 1];
		sequence.push_back(next_val);
	}
	return (sequence);
}

/* --------------------------------------- */
/* ----------------VECTOR----------------- */
/* --------------------------------------- */

void PmergeMe::sort_vec(std::vector<int> &container)
{
	if (container.size() <= 1)
		return ;
	int leftover = -1;
	if (container.size() % 2)
	{
		leftover = container.back();
		container.pop_back();
	}
	
	std::vector<std::pair<int, int> > pairs;
	std::vector<int> mainChain;
	
	for (size_t i = 0; i < container.size(); i += 2)
	{
		int first = container[i];
		int second = container[i + 1];
		
		if (first < second)
			std::swap(first, second);
		pairs.push_back(std::make_pair(first, second));
		mainChain.push_back(first);
	}
	sort_vec(mainChain);
	
	std::vector<bool> used(pairs.size(), false);
	std::vector<int> pendChain;
	for (size_t i = 0; i < mainChain.size(); i++)
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (!used[j] && pairs[j].first == mainChain[i])
			{
				pendChain.push_back(pairs[j].second);
				used[j] = true;
			}
		}
	}
	mainChain.insert(mainChain.begin(), pendChain[0]);
	
	std::vector<int> jacobsthal_sequence = generate_jacobsthal< std::vector<int> >(pendChain.size());
	size_t insertedCount = 1;
	size_t i = 0;
	while(insertedCount < pendChain.size())
	{
		size_t sequenceIndex = static_cast<size_t>(jacobsthal_sequence[i]);
		if (sequenceIndex >= pendChain.size())
        	sequenceIndex = pendChain.size() - 1;
		for (size_t j = sequenceIndex; j >= insertedCount; j--)
		{
			int valueToInsert = pendChain[j];
			int originalLeader;
			
			for (size_t k = 0; k < pairs.size(); ++k)
			{
				if (pairs[k].second == valueToInsert)
				{
					originalLeader = pairs[k].first;
					break ;
				}
			}
			std::vector<int>::iterator itLeader = std::find(mainChain.begin(), mainChain.end(), originalLeader);
			std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), itLeader, valueToInsert);
			mainChain.insert(pos, valueToInsert);
		}
		insertedCount = sequenceIndex + 1;
		i++;
	}
	if (leftover != -1)
	{
		std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), leftover);
		mainChain.insert(pos, leftover);
	}
	container = mainChain;
}

/* --------------------------------------- */
/* -----------------DEQUE----------------- */
/* --------------------------------------- */

void PmergeMe::sort_deq(std::deque<int> container)
{
	if (container.size() <= 1)
		return ;
	int leftover = -1;
	if (container.size() % 2)
	{
		leftover = container.back();
		container.pop_back();
	}
	
	std::deque<std::pair<int, int> > pairs;
	std::deque<int> mainChain;
	
	for (size_t i = 0; i < container.size(); i += 2)
	{
		int first = container[i];
		int second = container[i + 1];
		
		if (first < second)
			std::swap(first, second);
		pairs.push_back(std::make_pair(first, second));
		mainChain.push_back(first);
	}
	sort_deq(mainChain);
	
	std::vector<bool> used(pairs.size(), false);
	std::deque<int> pendChain;
	for (size_t i = 0; i < mainChain.size(); i++)
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (!used[j] && pairs[j].first == mainChain[i])
			{
				pendChain.push_back(pairs[j].second);
				used[j] = true;
			}
		}
	}
	mainChain.insert(mainChain.begin(), pendChain[0]);
	
	std::deque<int> jacobsthal_sequence = generate_jacobsthal< std::deque<int> >(pendChain.size());
	size_t insertedCount = 1;
	size_t i = 0;
	while(insertedCount < pendChain.size())
	{
		size_t sequenceIndex = static_cast<size_t>(jacobsthal_sequence[i]);
		if (sequenceIndex >= pendChain.size())
			sequenceIndex = pendChain.size() - 1;
		for (size_t j = sequenceIndex; j >= insertedCount; j--)
		{
			int valueToInsert = pendChain[j];
			int originalLeader;
			
			for (size_t k = 0; k < pairs.size(); ++k)
			{
				if (pairs[k].second == valueToInsert)
				{
					originalLeader = pairs[k].first;
					break ;
				}
			}
			std::deque<int>::iterator itLeader = std::find(mainChain.begin(), mainChain.end(), originalLeader);
			std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), itLeader, valueToInsert);
			mainChain.insert(pos, valueToInsert);
		}
		insertedCount = sequenceIndex + 1;
		i++;
	}
	if (leftover != -1)
	{
		std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), leftover);
		mainChain.insert(pos, leftover);
	}
	container = mainChain;
}

/* --------------------------------------- */
/* --------------CONSTRUCTORS------------- */
/* --------------------------------------- */

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(PmergeMe const &)
{}

PmergeMe &PmergeMe::operator=(PmergeMe const &)
{
	return (*this);
}

PmergeMe::~PmergeMe()
{}
