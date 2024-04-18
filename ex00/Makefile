# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcordes <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 09:03:35 by mcordes           #+#    #+#              #
#    Updated: 2023/07/15 20:20:11 by mcordes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.cpp\
		BitcoinExchange.cpp

OBJ = $(SRC:%.cpp=%.o)

NAME = btc

CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
RM = /bin/rm -f

.PHONY:all clean fclean re

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(CPP) $(CPPFLAGS) $^ -o $@

clean:
			@$(RM) $(OBJ)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all
