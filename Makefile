# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carmeno <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 22:34:39 by carmeno           #+#    #+#              #
#    Updated: 2024/02/15 17:10:25 by deordone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                               SO_LONG                                        #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  
NAME        = minishell
OS = $(shell uname)
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE_PATH) -MMD -MF $(@:.o=.d) 

# ╔══════════════════════════════════════════════════════════════════════════╗ #  
#                               SOURCES                                        #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  

SOURCES_PATH    = ./src
OBJECTS_PATH    = ./obj
INCLUDE_PATH    = ./inc
LIBRARY_PATH	= ./library
LIBFT_PATH	= $(LIBRARY_PATH)/Libft
DPRINTF_PATH	= $(LIBRARY_PATH)/ft_dprintf

LIBFT = $(LIBFT_PATH)/libft.a
DPRINTF = $(DPRINTF_PATH)/libftdprintf.a

HEADER = $(INCLUDE_PATH)/minishell.h
SOURCES = minishell.c

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
#                               RULES                                          #
# ╚══════════════════════════════════════════════════════════════════════════╝ #  

all: header make_libs $(NAME)

make_libs:
	@make -C $(LIBFT_PATH) > /dev/null
#	@printf "$(CYAN)Compiling $(LIBFT_PATH)$(NC)\n";
	@make -C $(DPRINTF_PATH) > /dev/null
#	@printf "$(CYAN)Compiling $(DPRINTF_PATH)$(NC)\n";

-include $(DEPS)
$(NAME): $(OBJECTS) $(LIBFT) $(DPRINTF) 
	@printf "$(CYAN)$@ Compiled$(NC)\n";
	@$(CC) $(CFLAGS) $^ -o $(NAME)

$(OBJECTS_PATH)/%.o: $(SOURCES_PATH)/%.c $(HEADER) Makefile
		@printf "$(CYAN)Compiling $@$(NC)\n";
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@ 

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
	@printf "$(RED)		  ══════════════════════════$(WHITE)「₪」$(RED)══════════════════════════$(GREEN)\n";
	@echo
	@printf "     	          $(YELLOW)                      ▒▒▒▒▒▒▒▒▒   ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n";
	@printf "	     	                      ▒▒▒▒▒▒▒▒▒     ▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒\n";
	@printf "	     	                    ▒▒▒▒▒▒▒▒▒       ▒▒▒▒     ▒▒▒▒▒▒▒\n";
	@printf "	     	                  ▒▒▒▒▒▒▒▒▒         ▒▒      ▒▒▒▒▒▒▒\n";
	@printf "	     	                ▒▒▒▒▒▒▒▒▒                  ▒▒▒▒▒▒▒▒\n";
	@printf "	     	              ▒▒▒▒▒▒▒▒▒                  ▒▒▒▒▒▒▒▒\n";
	@printf "	     	            ▒▒▒▒▒▒▒▒                  ▒▒▒▒▒▒▒▒\n";
	@printf "	     	          ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒     ▒▒▒▒▒▒▒▒     ▒▒\n";
	@printf "	     	          ▒▒▒▒▒▒ Droied$(YELLOW) ▒▒▒▒▒▒▒   ▒▒▒▒▒▒▒▒    ▒▒▒▒\n";
	@printf "	     	          ▒▒▒▒▒▒▒ Pacman ▒▒▒▒▒▒   ▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒\n";
	@printf "	     	          ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒   ▒▒ Barcelona ▒▒▒\n";
	@printf "	     	          ░░░░░ $(BLUE)  ░░░░░ $(YELLOW) ▒▒▒▒▒▒▒▒   ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n";
	@printf "	     	         ░░░░$(WHITE)▀$(YELLOW)░░$(BLUE) ░$(WHITE)▄ $(BLUE)░$(WHITE)▄ $(BLUE)░ $(YELLOW)▒▒▒▒▒▒▒▒      |\n";
	@printf "	    	         ░░░░░  $(BLUE) ░░░░░░░$(YELLOW) ▒▒▒▒▒▒▒▒      ╰┈➤$(NAME) \n";
	@printf "	     	          ░░░░░ $(BLUE) ░ ░ ░ ░$(YELLOW) ▒▒▒▒▒▒▒▒$(NC)\n";
	@echo
	@printf "\n $(RED)	   ╔══════════════════════════════════════════════════════════════════════════╗$(NC)\n"
	@printf "$(WHITE)      	       • • ᗣ • • • • • • • • ᗧ • • ᗣ • • • • • • • • • • ᗣ • • • • • • • •$(NC)\n"
	@printf "  $(RED)	   ╚══════════════════════════════════════════════════════════════════════════╝$(NC)\n"
	@echo
 
help: 
	@printf "\n";  
	@printf "	▂▃▅▆█▆▅▃▂ Commands ▂▃▅▆█▆▅▃▂\n";
	@printf "$(BLUE)		  ► help \n";
	@printf "		  ► clean \n";
	@printf "		  ► fclean \n";
	@printf "		  ► re \n";
	@printf "		  ► author $(NC)  \n";
	@printf "\n"; 

author: 
	@printf "\n";
	@printf "$(CYAN)	 	         	Created by 𝗗𝗿𝗼𝗶e𝗱 -大卫\n";
	@printf "$(RED)		  ══════════════════════════「₪」══════════════════════════\n";
	@printf "$(CYAN)		        	https://github.com/Droied4 \n";
	@printf "\n";

.PHONY: all clean fclean re
