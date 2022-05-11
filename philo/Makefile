# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adratini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/08 19:36:09 by adratini          #+#    #+#              #
#    Updated: 2022/05/08 19:36:10 by adratini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS		= philo.c threads.c utils.c mutexes.c actions.c input.c helpers.c

OBJS		= $(SRCS:.c=.o)

NAME		= philo

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra

RM			= rm -f

OPTFLAGS	= -O3

%.o: %.c	philo.h
			$(CC) $(CFLAGS) ${OPTFLAGS}  -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
