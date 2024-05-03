# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcordes <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 17:10:10 by mcordes           #+#    #+#              #
#    Updated: 2024/04/18 17:32:54 by mcordes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.cpp\
		PmergeMe.cpp

OBJ = $(SRC:%.cpp=%.o)

NAME = PmergeMe

CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
RM = /bin/rm -f

.PHONY:all clean fclean re

%.o: %.cpp
	${CPP} ${CPPFLAGS} -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(CPP) $(CPPFLAGS) $^ -o $@

clean:
			@$(RM) $(OBJ)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all
