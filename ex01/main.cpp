#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2) {
	std::cout << "There must be a single parameter" << std::endl;
		return 1;
	}
	Rpn(*(argv + 1));
	return 0;
}
