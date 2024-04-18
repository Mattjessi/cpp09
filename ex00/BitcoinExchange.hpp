/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcordes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:04:08 by mcordes           #+#    #+#             */
/*   Updated: 2023/07/15 20:20:11 by mcordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <map>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <ctime>

class BitcoinExchange {

	public:
		BitcoinExchange( std::string file );
		~BitcoinExchange( void );

		std::map<std::string, float>	getMap( void ) const;
		std::string						getFile( void ) const;

		class DataBaseFileException : public std::exception {
			public:
				virtual const char *what( void ) const throw();
		};

		class FileException : public std::exception {
			public:
				virtual const char *what( void ) const throw();
		};

		class DataBaseContentException : public std::exception {
			public:
				virtual const char *what( void ) const throw();
		};

		class FileContentException : public std::exception {
			public:
				virtual const char *what( void ) const throw();
		};

	private:
		std::map<std::string, float>	_dataMap;
		std::string						_file;
		static time_t					_now;
		static tm*						_local_time;
		static int						_year_now;
		static int						_month_now;
		static int						_day_now;

		BitcoinExchange( void );
		BitcoinExchange( BitcoinExchange const & src );

		BitcoinExchange &	operator=( BitcoinExchange const & rhs );

		void				_dataBaseChecker( void );
		void				_dataBaseFormatChecker( std::string str ) const;
		void				_dataBaseDateChecker( std::string date ) const;
		int					_leapMonthChecker( int year, int day ) const;
		void				_dataBaseValueChecker( std::string value ) const;
		void				_dataFileChecker( void );
		int					_dataFileFormatChecker( std::string str );
		int					_dataFileDateChecker( std::string date );
		int					_dataFileValueChecker( std::string value );
		void				_print( std::string date, std::string value,
								std::map<std::string, float>::iterator& it );
		int					_nearestValueFinder( std::string date,
								std::map<std::string, float>::iterator& it );

};

#endif
