#include "RPN.hpp"

//////////////////////////////Contuctor | Destructor

//Contuctor

Rpn::Rpn( void ) {
	return;
}

Rpn::Rpn( Rpn const & src ) {
	*this = src;
	return;
}

Rpn::Rpn( std::string arg ) : _arg(arg) {
	try
	{
		this->_check_arg();
		this->_calculate();
		std::cout << this->_result << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	return;
}

//Destructor

Rpn::~Rpn( void ) {
	return;
}

//////////////////////////////Member function

void	Rpn::_check_arg( void ) const {
	int	i = 0;

	while (this->_arg[i]) {
		if (this->_arg[i] < '\t' || (this->_arg[i] > '\t' && this->_arg[i] < ' ')
			|| (this->_arg[i] > ' ' && this->_arg[i] < '*')
			|| (this->_arg[i] > '+' && this->_arg[i] < '-')
			|| (this->_arg[i] > '-' && this->_arg[i] < '/') || this->_arg[i] > '9')
			throw Rpn::NotAGoodContentException();
		if (isdigit(this->_arg[i]) && isdigit(this->_arg[i + 1]))
			throw Rpn::NotAGoodContentException();
		i++;
	}

	i = 0;
	int	numberOfDigit = 0;
	int	numberOfSign = 0;

	while (this->_arg[i]) {
		if (isdigit(this->_arg[i]))
			numberOfDigit++;
		if (this->_arg[i] == '+' || this->_arg[i] == '-' || this->_arg[i] == '*' || this->_arg[i] == '/')
			numberOfSign++;
		i++;
	}

	if (numberOfDigit != numberOfSign + 1)
		throw Rpn::NotAGoodContentException();

	i = 0;

	if (numberOfDigit == 1) {
		while (this->_arg[i]) {
			if (isdigit(this->_arg[i]))
				std::cout << this->_arg[i] << std::endl;
			i++;
		}
		exit(EXIT_SUCCESS);
	}

	i = this->_arg.size();

	while (--i >= 0) {
		if (isdigit(this->_arg[i]) || this->_arg[i] == '+' || this->_arg[i] == '-'
				|| this->_arg[i] == '*' || this->_arg[i] == '/') {
			if (isdigit(this->_arg[i]))
				throw Rpn::NotAGoodContentException();
			break ;
		}
	}
}

void	Rpn::_calculate( void ) {
	int	i = 0;

	while (this->_arg[i]) {
		if (this->_arg[i] == '\t' || this->_arg[i] == ' ') {
			i++;
			continue ;
		}
		if (isdigit(this->_arg[i]))
			this->_rpnStack.push(atof(&this->_arg[i]));
		else {
			double	operand_1 = this->_rpnStack.top();
			this->_rpnStack.pop();
			double	operand_2 = this->_rpnStack.top();
			this->_rpnStack.pop();

			if (this->_arg[i] == '+')
				this->_rpnStack.push(operand_2 + operand_1);
			else if (this->_arg[i] == '-')
				this->_rpnStack.push(operand_2 - operand_1);
			else if (this->_arg[i] == '*')
				this->_rpnStack.push(operand_2 * operand_1);
			else if (this->_arg[i] == '/')
				this->_rpnStack.push(operand_2 / operand_1);

			this->_result = this->_rpnStack.top();
		}
		i++;
	}
}

//////////////////////////////Error handler

const char *Rpn::NotAGoodContentException::what( void ) const throw() {
	return "Error";
}

//////////////////////////////Operator overload

//Assignment operator

Rpn &	Rpn::operator=(Rpn const & rhs) {
	if( this != &rhs )
		this->_arg = rhs._arg;;
	return *this;
}
