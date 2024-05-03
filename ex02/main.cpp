/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcordes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:05:33 by mcordes           #+#    #+#             */
/*   Updated: 2023/07/15 20:20:11 by mcordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int argc, char **argv) {
	if (argc == 1) {
		std::cout << "There must be at least one parameter." << std::endl;
		return 1;
	}
	PmergeMe	pmergeMe(argv + 1);
	return 0;
}
