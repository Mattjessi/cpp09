/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcordes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:05:21 by mcordes           #+#    #+#             */
/*   Updated: 2023/07/15 20:20:11 by mcordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//////////////////////////////Contuctor | Destructor

//Contuctor

PmergeMe::PmergeMe(char **range) : _range(range) {
	try
	{
		this->_check_arg();
		this->_check_duplicate();

		std::cout << "Before:" << "\033[38;5;163m";
		this->_print_range();
		std::cout << "\033[0m" << std::endl;

		this->_merge_insert_vector();
		this->_merge_insert_deque();

		std::cout << "After:" << "\033[38;5;154m";
		print_container(this->_v_range);
		std::cout << "\033[0m" << std::endl;

		std::cout << "Time to process a range of " << "\033[38;5;111m" << this->_range_size << "\033[0m"
			<< " elements with std::vector : " << "\033[38;5;111m" << this->_v_timer << "\033[0m" << " us"
			<< std::endl;

		std::cout << "Time to process a range of " << "\033[38;5;111m" << this->_range_size << "\033[0m"
			<< " elements with std::deque : " << "\033[38;5;111m" << this->_d_timer << "\033[0m" << " us"
			<< std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}

//Destructor

PmergeMe::~PmergeMe() {
}

//////////////////////////////Member function 

void	PmergeMe::_trim( void ) const {
	int	i = 0;

	while (this->_range[i]) {
		while (*this->_range[i] == ' ' || *this->_range[i] == '\t') {
			this->_range[i]++;
		}
		i++;
	}

	int	j;

	while (--i >= 0) {
		j = strlen(this->_range[i]);
		while (j - 1 > 0 && (this->_range[i][j - 1] == ' ' || this->_range[i][j - 1] == '\t'))
			j--;
		this->_range[i][j] = '\0';
	}
}

void	PmergeMe::_check_arg( void ) const {
	int	i = 0;
	int	j = 0;

	this->_trim();
	while (this->_range[i]) {
		if (strlen(this->_range[i]) == 0)
			throw PmergeMe::NotAGoodContentException();
		while (this->_range[i][j]) {
			if (strlen(this->_range[i]) > 10 || this->_range[i][j] < '0' || this->_range[i][j] > '9')
				throw PmergeMe::NotAGoodContentException();
			if (atol(this->_range[i]) > INT_MAX)
				throw PmergeMe::NotAGoodContentException();
			j++;
		}
		j = 0;
		i++;
	}
}

void	PmergeMe::_check_duplicate( void ) {
	int	i = 0;
	std::set<int>	set;

	while (this->_range[i]) {
		if (set.find(atoi(this->_range[i])) != set.end())
			throw PmergeMe::NotAGoodContentException();
		set.insert(atoi(this->_range[i]));
		i++;
	}
	set.clear();
}

void	PmergeMe::_print_range( void ) {
	int	i = 0;

	while (this->_range[i]) {
		std::cout << " ";
		std::cout << this->_range[i];
		i++;
	}
	this->_range_size = i;
}

bool	IsOdd(int n) {
	return (n % 2);
}

void	PmergeMe::_merge_insert_vector( void ) {
	clock_t	start = clock();
	int	i = 0;
	std::vector<int>	even;

	while (this->_range[i])
		even.push_back(atoi(this->_range[i++]));

	std::vector<int>::iterator	odd = std::stable_partition(even.begin(), even.end(), IsOdd);
	std::sort(even.begin(), odd);
	std::sort(odd, even.end());

	std::vector<int>	merge(this->_range_size);
	std::merge(even.begin(), odd, odd, even.end(), merge.begin());
	this->_v_range = merge;
	merge.clear();
	clock_t	end = clock();
	this->_v_timer = (double)(end - start) / (CLOCKS_PER_SEC / 1000000.0);
}

void	PmergeMe::_merge_insert_deque( void ) {
	clock_t	start = clock();
	int	i = 0;
	std::deque<int>	even;

	while (this->_range[i])
		even.push_back(atoi(this->_range[i++]));

	std::deque<int>::iterator	odd = std::stable_partition(even.begin(), even.end(), IsOdd);
	std::sort(even.begin(), odd);
	std::sort(odd, even.end());

	std::deque<int>	merge(this->_range_size);
	std::merge(even.begin(), odd, odd, even.end(), merge.begin());
	this->_d_range = merge;
	merge.clear();
	clock_t	end = clock();
	this->_d_timer = (double)(end - start) / (CLOCKS_PER_SEC / 1000000.0);
}

//////////////////////////////Error handler

const char *PmergeMe::NotAGoodContentException::what( void ) const throw() {
	return "Error";
}
