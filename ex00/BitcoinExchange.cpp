/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcordes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:04:08 by mcordes           #+#    #+#             */
/*   Updated: 2023/07/15 20:20:11 by mcordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//////////////////////////////Contuctor | Destructor

//Contuctor

BitcoinExchange::BitcoinExchange( std::string file ) : _file(file) {
	this->_dataBaseChecker();
	this->_dataFileChecker();
	return;
}

BitcoinExchange::BitcoinExchange( void ) {
	return;
}

BitcoinExchange::BitcoinExchange( BitcoinExchange const & src ) {
	static_cast<void>(src);
	return;
}

//Destructor

BitcoinExchange::~BitcoinExchange( void ) {
	return;
}

//////////////////////////////Member function

void	BitcoinExchange::_dataBaseFormatChecker( std::string str ) const {

	if (!(isdigit(str[0]) && isdigit(str[1]) && isdigit(str[2])
			&& isdigit(str[3]) && str[4] == '-' && isdigit(str[5])
			&& isdigit(str[6]) && str[7] == '-' && isdigit(str[8])
			&& isdigit(str[9]) && str[10] == ',' && (isdigit(str[11])
				|| str[11] == '.')))
		throw BitcoinExchange::DataBaseContentException();

	return;
}

void	BitcoinExchange::_dataBaseDateChecker( std::string date ) const {

	int	year = atoi(date.substr(0, 4).c_str());
	int	month = atoi(date.substr(5, 2).c_str());
	int	day = atoi(date.substr(8, 2).c_str());

	if (year > _year_now || (year == _year_now && month > _month_now)
			|| (year == _year_now && month == _month_now
				&& day > _day_now) || month > 12)
		throw BitcoinExchange::DataBaseContentException();

	if ((month == 1 || month == 3 || month == 5 || month == 7
				|| month == 8 || month == 10 || month == 12) && day > 31)
		throw BitcoinExchange::DataBaseContentException();

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		throw BitcoinExchange::DataBaseContentException();

	if (month == 2 && this->_leapMonthChecker(year, day))
		throw BitcoinExchange::DataBaseContentException();

	return;
}

int	BitcoinExchange::_leapMonthChecker( int year, int day ) const {

	if (day <= 29 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		return 0;
	else if (day <= 28)
		return 0;

	return 1;
}

void	BitcoinExchange::_dataBaseValueChecker( std::string value ) const {

	int	i = 0;
	int	digit = 0;
	int	dot = 0;
	while (value[i]) {
		if (isdigit(value[i]) == 0 && value[i] != '.')
			throw BitcoinExchange::DataBaseContentException();
		if (isdigit(value[i]))
			digit++;
		if (value[i] == '.')
			dot++;
		i++;
	}

	if (digit == 0 || dot > 1)
		throw BitcoinExchange::DataBaseContentException();

	return;
}

void	BitcoinExchange::_dataBaseChecker( void ) {

	std::ifstream	data("data.csv");
	if (!data) {
		data.close();
		throw BitcoinExchange::DataBaseFileException();
	}

	int	i = 0;
	std::string	str;

	while (std::getline(data, str)) {
		if (i == 0 && str.compare("date,exchange_rate") == 0) {
			i++;
			continue ;
		} else if (i == 0) {
			data.close();
			throw BitcoinExchange::DataBaseContentException();
		}
		this->_dataBaseFormatChecker(str);
		std::istringstream iss(str);
		std::string date;
		std::string value;
		if (std::getline(iss, date, ',') && std::getline(iss >> std::ws, value)) {
			this->_dataBaseDateChecker(date);
			this->_dataBaseValueChecker(value);
			this->_dataMap[date] = atof(value.c_str());
		} else {
			data.close();
			throw BitcoinExchange::DataBaseContentException();
		}
	}

	data.close();

	return;
}

void	BitcoinExchange::_dataFileChecker( void ) {

	std::ifstream	file(this->_file.c_str());
	if (!file) {
		file.close();
		throw BitcoinExchange::FileException();
	}

	int	i = 0;
	std::string	str;

	while (std::getline(file, str)) {
		if (i == 0 && str.compare("date | value") == 0) {
			i++;
			continue ;
		} else if (i == 0) {
			std::cout << "Error: header of input file is not ok.";
			file.close();
			throw BitcoinExchange::FileContentException();
		}
		if (this->_dataFileFormatChecker( str ))
			continue;
		std::istringstream iss(str);
		std::string date;
		std::string value;
		if (std::getline(iss, date, '|') && std::getline(iss >> std::ws, value)) {
			if (this->_dataFileDateChecker( date ))
				continue;
			if (this->_dataFileValueChecker( value ))
				continue;

			std::map<std::string, float>::iterator it;

			if (this->_nearestValueFinder(date, it))
				continue;

			this->_print(date, value, it);
		}
	}

	file.close();

	return;
}

int	BitcoinExchange::_nearestValueFinder( std::string date,
		std::map<std::string, float>::iterator& it ) {

	it = this->_dataMap.find(date.substr(0, 10));
	if (it == this->_dataMap.end()) {
		std::map<std::string, float>::reverse_iterator rit;
		rit = _dataMap.rbegin();
		while (rit != _dataMap.rend()) {
			if (atoi(rit->first.substr(0, 4).c_str()) <= atoi(date.substr(0, 4).c_str())) {
				if (atoi(rit->first.substr(5, 2).c_str()) <= atoi(date.substr(5, 2).c_str())) {
					if (atoi(rit->first.substr(8, 2).c_str()) <= atoi(date.substr(8, 2).c_str())) {
						it->second = rit->second;
						break ;
					}
				}
			}
			rit++;
		}
		if (rit == _dataMap.rend()) {
			std::cout << "Error: date is to low." << std::endl;
			return 1;
		}
	}

	return 0;
}

void	BitcoinExchange::_print( std::string date, std::string value,
		std::map<std::string, float>::iterator& it ) {

	int	i = 0;

	while (value[i]) {
		if (value[i] == '.') {
			std::cout << date << "=> " << value << " = " << it->second * atof(value.c_str()) << std::endl;
			break ;
		}
		i++;
	}
	if (value[i] == '\0')
		std::cout << date << "=> " << value << " = " << it->second * atoi(value.c_str()) << std::endl;

	return;
}

int	BitcoinExchange::_dataFileFormatChecker( std::string str ) {
	if (!(isdigit(str[0]) && isdigit(str[1]) && isdigit(str[2])
			&& isdigit(str[3]) && str[4] == '-' && isdigit(str[5])
			&& isdigit(str[6]) && str[7] == '-' && isdigit(str[8])
			&& isdigit(str[9]) && str[10] == ' ' && str[11] == '|'
			&& str[12] == ' ' && (isdigit(str[13]) || str[13] == '.'
				|| str[13] == '-'))) {
		std::cout << "Error: bad input => " << str << std::endl;
		return 1;
	}

	return 0;
}

int	BitcoinExchange::_dataFileDateChecker( std::string date ) {

	int	year = atoi(date.substr(0, 4).c_str());
	int	month = atoi(date.substr(5, 2).c_str());
	int	day = atoi(date.substr(8, 2).c_str());

	if (month > 12) {
		std::cout << "Error: bad input => " << date << std::endl;
		return 1;
	}

	if ((month == 1 || month == 3 || month == 5 || month == 7
				|| month == 8 || month == 10 || month == 12) && day > 31) {
		std::cout << "Error: bad input => " << date << std::endl;
		return 1;
	}

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
		std::cout << "Error: bad input => " << date << std::endl;
		return 1;
	}

	if (month == 2 && this->_leapMonthChecker(year, day)) {
		std::cout << "Error: bad input => " << date << std::endl;
		return 1;
	}

	return 0;
}

int	BitcoinExchange::_dataFileValueChecker( std::string value ) {

	int	i = 0;
	int	digit = 0;
	int	dot = 0;
	while (value[i]) {
		if (i == 0 && value[0] == '-') {
			i++;
			continue ;
		}
		if (isdigit(value[i]) == 0 && value[i] != '.') {
			std::cout << "Error: bad input => " << value << std::endl;
			return 1;
		}
		if (isdigit(value[i]))
			digit++;
		if (value[i] == '.')
			dot++;
		i++;
	}

	if (digit == 0 || dot > 1) {
		std::cout << "Error: bad input => " << value << std::endl;
		return 1;
	}

	if (value[0] == '-') {
		std::cout << "Error: not a positive number." << std::endl;
		return 1;
	}

	if (dot == 0 && (value.length() > 4 ||(value.length() == 4 && atoi(value.c_str()) > 1000))) {
		std::cout << "Error: too large a number." << std::endl;
		return 1;
	}

	if (dot == 1) {
		std::string	str;
		std::istringstream iss(value);
		std::getline(iss, str, '.');
		if (dot == 1 && (str.length() > 4 || (str.length() == 4 && atof(value.c_str()) > 1000.0))) {
			std::cout << "Error: too large a number." << std::endl;
			return 1;
		}
	}

	return 0;
}

//////////////////////////////Accessor

//getters

std::map<std::string, float>	BitcoinExchange::getMap( void ) const {
	return this->_dataMap;
}

std::string	BitcoinExchange::getFile( void ) const {
	return this->_file;
}

//////////////////////////////Error handler

const char *BitcoinExchange::DataBaseFileException::what( void ) const throw() {
	return "Error: could not open data.csv file.";
}

const char *BitcoinExchange::FileException::what( void ) const throw() {
	return "Error: could not open file.";
}

const char *BitcoinExchange::DataBaseContentException::what( void ) const throw() {
	return "Error: content of data.csv is not ok.";
}

const char *BitcoinExchange::FileContentException::what( void ) const throw() {
	return "";
}

//////////////////////////////Operator overload

//Assignment operator

BitcoinExchange &	BitcoinExchange::operator=( BitcoinExchange const & rhs ) {
	static_cast<void>(rhs);
	return *this;
}

time_t	BitcoinExchange::_now = time(0);
tm*		BitcoinExchange::_local_time = localtime(&_now);
int		BitcoinExchange::_year_now = 1900 + _local_time->tm_year;
int		BitcoinExchange::_month_now = 1 + _local_time->tm_mon;
int		BitcoinExchange::_day_now = _local_time->tm_mday;
