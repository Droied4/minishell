# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 12:12:27 by deordone          #+#    #+#              #
#    Updated: 2024/03/11 19:03:16 by avolcy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftdprintf.a

SOURCES = \
	ft_dprintf.c ft_dputchar.c ft_dputstr.c ft_dputnbr.c ft_dputunsnbr.c \
	ft_dputhxanbr.c ft_dputhxanbr_up.c ft_dputhxaptr.c

HEADER = ft_dprintf.h
INCLUDE = -I

OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER) Makefile
	$(AR) $(NAME) $(OBJECTS) 

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCLUDE)/$(HEADER) -c $<

clean: Makefile
	rm -f $(OBJECTS)

fclean: clean Makefile
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
