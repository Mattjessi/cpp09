#ifndef  RPN_HPP
# define RPN_HPP

#include <iostream>
#include <string>
#include <ctype.h>
#include <stack>
#include <cstdlib>

class Rpn {

	public:
		Rpn( std::string arg );
		~Rpn( void );

		class NotAGoodContentException : public std::exception {
			public:
				virtual const char *what( void ) const throw();
		};

	private:
		std::string			_arg;
		std::stack<double>	_rpnStack;
		double				_result;

		Rpn( void );
		Rpn( Rpn const & src );

		Rpn &		operator=(Rpn const & rhs);

		void		_check_arg( void ) const;
		void		_calculate( void );

};

#endif
