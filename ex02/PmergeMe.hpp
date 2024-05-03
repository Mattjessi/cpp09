/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcordes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:05:13 by mcordes           #+#    #+#             */
/*   Updated: 2023/07/15 20:20:11 by mcordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <set>
#include <vector>
#include <deque>
#include <ctime>

class PmergeMe {
	public:
		PmergeMe(char **range);
		~PmergeMe();

		class NotAGoodContentException : public std::exception {
			public:
				virtual const char *what( void ) const throw();
		};

	private:
		char				**_range;
		int					_range_size;
		std::vector<int>	_v_range;
		std::deque<int>		_d_range;
		double				_v_timer;
		double				_d_timer;

		PmergeMe();
		PmergeMe(PmergeMe const & src);

		PmergeMe &			operator=(PmergeMe const & rhs);

		void				_check_arg( void ) const;
		void				_check_duplicate( void );
		void				_trim( void ) const;
		void				_print_range( void );
		void				_merge_insert_vector( void );
		void				_merge_insert_deque( void );
};

template< typename T >

void	print_container( T & container ) {
	for (typename T::iterator it = container.begin(); it != container.end(); ++it)
		std::cout << " " << *it;
}
