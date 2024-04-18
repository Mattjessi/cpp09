/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcordes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:04:08 by mcordes           #+#    #+#             */
/*   Updated: 2023/07/15 20:20:11 by mcordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main( int argc, char **argv ) {

	if ( argc != 2 )
		std::cerr << "Error: could not open file." << std::endl;
	else {
		try
		{
			BitcoinExchange	btc(argv[1]);
		}
		catch (std::exception & e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	return 0;
}
