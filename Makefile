# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/08 10:43:38 by mouassit          #+#    #+#              #
#    Updated: 2021/09/30 10:35:35 by mouassit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

LIB = pipex.h \

SRC = pipex.c \
	get_next_line.c \
	get_next_line_utils.c \
	libft.c

all : $(NAME)

$(NAME): $(SRC) $(LIB)
	@gcc -Wall -Wextra -Werror -I /Users/mouassit/Desktop/push_swap $(SRC) -D BUFFER_SIZE=1 -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean:
	@rm -rf $(NAME)

re: fclean all