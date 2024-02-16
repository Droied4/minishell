# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 21:16:09 by avolcy            #+#    #+#              #
#    Updated: 2023/11/29 15:43:06 by avolcy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variable que contiene el nombre de la biblio estatica
NAME = libft.a
CC = cc 
RM = rm -rf
TMP = libft.h.gch 
CFLAGS = -Wall -Wextra -Werror #-gopciones de compilacion adicionales
HEADER = libft.h
BUILT_LIB = ar rcs
#variable que contiene la lista de archivos fuente que se deben compilar
SRC = ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	  ft_tolower.c ft_toupper.c ft_memcmp.c ft_memmove.c ft_memcpy.c \
	  ft_memset.c ft_memchr.c ft_strlen.c ft_strchr.c ft_strrchr.c \
	  ft_strlcpy.c ft_strlcat.c ft_bzero.c ft_strnstr.c ft_strncmp.c \
	  ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	  get_next_line.c  get_next_line_utils.c 

SRC_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

#variable que contiene la lista de archivos objeto para la biblioteca.
OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)

all : $(NAME) bonus
#------------------------------------------------------------------------------
#___$@ means the target which is in that case below $(NAME)___ \
___$< means the 1s dependency of a rule refer to the 1s item of the list of \
prerequisites or dependencies, below it represents $(OBJ) in %.o...= $(HEADER)\
---$^ is an automatic variable that means all the dependencies of a \
target in a rule it can means all the objects files if were used below🙂
#------------------------------------------------------------------------------
$(NAME) : $(OBJ) $(HEADER)
	$(BUILT_LIB) $@ $^

bonus : .bonus

.bonus : $(OBJ_B) $(HEADER)
	$(BUILT_LIB) $@ $^
	@touch .bonus

%.o: %.c $(HEADER) 
	$(CC) $(CFLAGS) -c $^ 

.PHONY : clean fclean re all

clean :
	@$(RM) $(OBJ) $(OBJ_B) $(TMP)

fclean : clean
	@$(RM) $(NAME) .bonus

re : fclean all

