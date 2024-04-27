# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 22:34:39 by carmeno           #+#    #+#              #
#    Updated: 2024/04/27 10:50:39 by avolcy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                               MINISHELL                                      #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  
NAME        = minishell
OS = $(shell uname)
CC = cc
CFLAGS = -Wall -Werror -Wextra -I $(INCLUDE_PATH) -MMD -MF $(@:.o=.d) 
# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                               SOURCES                                        #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  

SOURCES_PATH    = ./src
OBJECTS_PATH    = ./obj
INCLUDE_PATH    = ./inc
LIBRARY_PATH	= ./library
LIBFT_PATH	= $(LIBRARY_PATH)/libft
DPRINTF_PATH	= $(LIBRARY_PATH)/dprintf
LIBFT = $(LIBFT_PATH)/libft.a
DPRINTF = $(DPRINTF_PATH)/libftdprintf.a
READLINE_PATH = $(LIBRARY_PATH)/readline/

HEADER = $(INCLUDE_PATH)/minishell.h
HEADER += $(INCLUDE_PATH)/struct.h
HEADER += $(INCLUDE_PATH)/macros.h

SOURCES = minishell.c aux_dei.c aux_archly.c is_something.c aux_arch.c \
		  manage.c \
		  lexer.c new_lexer1.c lexer_aux.c lexer_aux2.c \
		  parser.c parser_input.c parser_entry.c \
		  expansor.c expansor_utils.c expansor_utils2.c \
		  word_lst.c parser_cmd.c redir_lst.c parser_redir.c \
		  executor.c exec_redir.c exec_cmds.c exec_conec.c\
		  builtins.c built_export.c built_pwd_cd.c built_unset.c built_echo.c\
		  built_env.c \

# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                               OBJECTS                                        #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  

OBJECTS = $(addprefix $(OBJECTS_PATH)/, ${SOURCES:.c=.o})
DEPS = $(addprefix $(OBJECTS_PATH)/, ${SOURCES:.c=.d})

# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                               COLORS                                         #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  
RED=\033[0;31m
CYAN=\033[0;36m
GREEN=\033[0;32m
YELLOW=\033[0;33m
WHITE=\033[0;97m
BLUE=\033[0;34m
NC=\033[0m # No color

# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                                RULES                                         #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  

all: header $(NAME) author
make_libs:
	@make -C $(LIBFT_PATH) > /dev/null
	@printf "$(CYAN)Compiling $(LIBFT_PATH)$(NC)\n";
	@make -C $(DPRINTF_PATH) > /dev/null
	@printf "$(CYAN)Compiling $(DPRINTF_PATH)$(NC)\n";

-include $(DEPS)

$(NAME): $(OBJECTS) $(LIBFT) $(DPRINTF) 
	@printf "$(CYAN)$@ Compiled$(NC)\n";
	@$(CC) $(CFLAGS) $^ -o $(NAME) -lreadline -L $(READLINE_PATH)lib -I $(READLINE_PATH)include

$(OBJECTS_PATH)/%.o: $(SOURCES_PATH)/%.c $(HEADER) Makefile
		@printf "$(CYAN)Compiling $@$(NC)\n";
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(READLINE_PATH)include


$(LIBFT) :
	@printf "$(CYAN)Compiling $@$(NC)\n";
	@make -C $(LIBFT_PATH) > /dev/null

$(DPRINTF) :
	@printf "$(CYAN)Compiling $@$(NC)\n";
	@make -C $(DPRINTF_PATH) > /dev/null

clean:
	@printf "$(CYAN)Cleaning objects and libraries$(NC)\n";
	@rm -rf $(OBJECTS_PATH) 
	@make clean -C $(LIBFT_PATH) > /dev/null
	@make clean -C $(DPRINTF_PATH) > /dev/null

fclean : clean
	@printf "$(CYAN)Cleaning objects, libraries and executable$(NC)\n";
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH) > /dev/null
	@make fclean -C $(DPRINTF_PATH) > /dev/null

re: fclean all 
# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                              MY RULES                                        #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  
header: 
	@echo
	@printf	"  \t\t  _____________________________________________\n";
	@printf	"  \t\t/                                               \\ \n";
	@printf	" \t\t|   _________________________________________    | \n";
	@printf	" \t\t|  /                                         \   | \n";
	@printf	" \t\t| |$(WHITE)           _       _     _          _ _ $(NC) |   | \n";
	@printf	" \t\t| |$(WHITE)     /\/\ (_)_ __ (_)___| |__   ___| | |$(NC) |   | \n";
	@printf	" \t\t| |$(WHITE)    /    \| | '_ \| / __| '_ \ / _ \ | |$(NC) |   | \n";
	@printf	" \t\t| |$(RED)   / /\/\ \ | | | | \__ \ | | |  __/ | |$(NC) |   | \n";
	@printf " \t\t| |$(RED)   \/    \/_|_| |_|_|___/_| |_|\___|_|_|$(NC) |   | \n";
	@printf	" \t\t|  \_________________________________________/   | \n";
	@printf	" \t\t|     avolcy /|\ deordone                    ⚬   | \n";
	@printf	"  \t\t\______________________________________________/   \n";
	@printf	"  \t\t         !____________________________! \n";
	@echo

author: 
	@echo;
	@printf "$(WHITE)			   https://github.com/Droied4 \n";
	@printf "$(RED)	    ══════════════════════════「₪」══════════════════════════\n";
	@printf "$(WHITE)			  https://github.com/ZenitsuTHB\n";
	@echo;

.PHONY: all clean fclean re
