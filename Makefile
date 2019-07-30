# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niguinti <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/13 18:20:24 by niguinti          #+#    #+#              #
#    Updated: 2019/02/04 14:17:25 by niguinti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fillit
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	main.c ft_move_tetri.c ft_resolv.c parse_array.c parser.c
OBJS	=	$(SRCS:.c=.o)
D_LIBFT	=	./libft
L_LIBFT	=	-Llibft
A_LIBFT	=	-lft
INC_H	=	-I ./includes

all: $(NAME)
$(NAME): $(SRCS)
	@$(MAKE) -C $(D_LIBFT)
	$(CC) -c $(CFLAGS) $(SRCS)
	$(CC) -o $(NAME) $(OBJS) $(L_LIBFT) $(A_LIBFT) $(INC_H)
clean:
	@$(MAKE) clean -C $(D_LIBFT)
	/bin/rm -f $(OBJS)

fclean: clean
	@$(MAKE) fclean -C $(D_LIBFT)
	/bin/rm -f $(NAME)

re: fclean ${NAME}
