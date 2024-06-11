# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avolcy <avolcy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 22:34:39 by carmeno           #+#    #+#              #
#    Updated: 2024/06/11 12:17:47 by avolcy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                               MINISHELL                                      #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  
#
NAME        = minishell
OS = $(shell uname)
CC = cc
CFLAGS = -Wall -Werror -Wextra -I $(INCLUDE_PATH) -MMD -MF $(@:.o=.d) -g -fsanitize=address

# Paths
SOURCES_PATH    = ./src
OBJECTS_PATH    = ./obj
INCLUDE_PATH    = ./inc
LIBRARY_PATH	= ./library
LIBFT_PATH	= $(LIBRARY_PATH)/libft
DPRINTF_PATH	= $(LIBRARY_PATH)/dprintf
READLINE_PATH = $(LIBRARY_PATH)/readline
LOCAL_INSTALL_PATH = ./library

# Libraries
LIBFT = $(LIBFT_PATH)/libft.a
DPRINTF = $(DPRINTF_PATH)/libftdprintf.a
READLINE_LIBS = $(READLINE_PATH)/libreadline.a $(READLINE_PATH)/libhistory.a

# Headers
HEADER = $(INCLUDE_PATH)/minishell.h $(INCLUDE_PATH)/struct.h $(INCLUDE_PATH)/macros.h

# Sources

SOURCES = minishell.c  signals.c

LEXER = lexer.c new_lexer1.c lexer_aux.c lexer_aux2.c 

EXECUTOR = executor.c exec_redir.c exec_cmds.c exec_conec.c

PARSER = parser.c parser_input.c parser_entry.c word_lst.c \
		parser_cmd.c redir_lst.c parser_redir.c

AUX = aux_dei.c aux_archly.c is_something.c aux_arch.c manage.c \
			aux_sig.c

BUILTINS = builtins.c built_export.c built_pwd_cd.c built_unset.c \
		built_echo.c built_env.c

EXPANSOR = expansor.c expansor_utils1.c expansor_utils2.c \
		expansor_utils3.c expansor_utils4.c

# Objects and dependencies
OBJECTS = $(addprefix $(OBJECTS_PATH)/, ${SOURCES:.c=.o})
OBJECTS += $(addprefix $(OBJECTS_PATH)/aux/, ${AUX:.c=.o})
OBJECTS += $(addprefix $(OBJECTS_PATH)/lexer/, ${LEXER:.c=.o})
OBJECTS += $(addprefix $(OBJECTS_PATH)/parser/, ${PARSER:.c=.o})
OBJECTS += $(addprefix $(OBJECTS_PATH)/builtins/, ${BUILTINS:.c=.o})
OBJECTS += $(addprefix $(OBJECTS_PATH)/expansor/, ${EXPANSOR:.c=.o})
OBJECTS += $(addprefix $(OBJECTS_PATH)/executor/, ${EXECUTOR:.c=.o})

DEPS = $(addprefix $(OBJECTS_PATH)/, ${SOURCES:.c=.d})

# Colors
G = \033[1;32m
O = \033[38;5;208m
C = \033[1;36m
B = \033[34m
M = \033[35m
RED=\033[0;31m
CYAN=\033[0;36m
GREEN=\033[0;32m
YELLOW=\033[0;33m
WHITE=\033[0;97m
BLUE=\033[0;34m
NC=\033[0m # No color

# Rules
all: header $(NAME) author

make_libs:
	@make -C $(LIBFT_PATH) > /dev/null
	@printf "$(CYAN)Compiling $(LIBFT_PATH)$(NC)\n";
	@make -C $(DPRINTF_PATH) > /dev/null
	@printf "$(CYAN)Compiling $(DPRINTF_PATH)$(NC)\n";

-include $(DEPS)

$(NAME): $(OBJECTS) $(LIBFT) $(DPRINTF) $(READLINE_LIBS)
	@printf "$(CYAN)$@ has been$(NC)$(G)Successfully$(NC)$(CYAN)Compiled$(NC)\n\n";
	@$(CC) $(CFLAGS) $^ -lcurses -o $(NAME)  

$(OBJECTS_PATH)/%.o: $(SOURCES_PATH)/%.c $(HEADER) Makefile
		@mkdir -p $(dir $@)
		@printf "$(CYAN)Compiling $@$(NC)\r";
		@$(CC) -DREADLINE_LIBRARY $(CFLAGS) -c $< -o $@ 

$(LIBFT) :
	@printf "$(CYAN)Compiling $@$(NC)\n";
	@make -C $(LIBFT_PATH) > /dev/null 
	@make -C $(READLINE_PATH) static 

$(DPRINTF) :
	@printf "$(CYAN)Compiling $@$(NC)\n";
	@make -C $(DPRINTF_PATH) > /dev/null

$(READLINE_LIBS): $(READLINE_PATH)/Makefile
	@make -C $(READLINE_PATH) static

$(READLINE_PATH)/Makefile:
		echo "$(YELLOW)READLINE WILL BE CONFIGURED$(DEFAULT)"; \
		cd $(READLINE_PATH) && ./configure; \
	
clean:
	@printf "$(CYAN)Cleaning objects and libraries$(NC)\n";
	@rm -rf $(OBJECTS_PATH) 
	@make clean -C $(LIBFT_PATH) > /dev/null
	@make clean -C $(DPRINTF_PATH) > /dev/null
	clear

fclean : clean
	@printf "$(CYAN)Cleaning objects, libraries and executable$(NC)\n";
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH) > /dev/null
	@make fclean -C $(DPRINTF_PATH) > /dev/null
	clear

re: fclean all 

vg: all
	valgrind --show-leak-kinds=all --track-origins=yes --leak-check=full --track-fds=yes --suppressions=.readline.supp ./$(NAME)

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
	@printf	"  \t\t         !____________________________! \n\n";
	@echo

author: 
	@echo;
	@printf "$(O)			    https://github.com/Droied4 \n";
	@printf "$(RED)	    ══════════════════════════「₪」══════════════════════════\n";
	@printf "$(O)			   https://github.com/ZenitsuTHB\n";
	@echo;

.PHONY: all clean fclean re vg 
