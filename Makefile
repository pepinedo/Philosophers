# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppinedo- <ppinedo-@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 14:50:06 by ppinedo-          #+#    #+#              #
#    Updated: 2024/09/11 18:54:47 by ppinedo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variables

NAME = philosophers
USER = ppinedo-
B_NAME = none
INCLUDE = include/
SRC_DIR = src/
B_SRC_DIR = src/bonus/
OBJ_DIR = obj/
CC = clang
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Sources
	
SRC_FILES = main checks init_data ft_atoi ft_calloc

B_SRC_FILES = 

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
B_SRC = $(addprefix $(B_SRC_DIR), $(addsuffix _bonus.c, $(B_SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
B_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix _bonus.o, $(B_SRC_FILES)))
OBJF = .cache_exists

###

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -I./$(INCLUDE) $(CFLAGS) $(OBJ) -o $(NAME) -Iinclude -ldl -lglfw -pthread -lm -lreadline
	@echo "$(GREEN)✅$(NAME) COMPILED!✅$(DEF_COLOR)"


$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@echo "$(YELLOW)Compiling:$(DEF_COLOR) $<"
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(CFLAGS) -I./$(INCLUDE) -c $< -o $@

clean:
			@rm -rf $(OBJ_DIR)
			@echo "$(RED)Object files$(DEF_COLOR) $(NAME) $(RED)cleaned!🧼$(DEF_COLOR)"

fclean:	clean	
			@rm -f $(NAME)
			@rm -f $(B_NAME)
			@echo "$(RED)Executable$(DEF_COLOR) $(NAME) $(RED)cleaned!🧼$(DEF_COLOR)"

re:			fclean all
			@echo "$(MAGENTA)📦$(NAME) recompiled!📦$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(B_SRC) $(INCLUDE) $(LIBFT)
			@echo "$(GREEN) ✅NORMINETTE OK!✅$(DEF_COLOR)"

bonus: $(B_OBJ)
			@$(CC) $(CFLAGS) $(B_OBJ) -o $(B_NAME)
			@echo "$(MAGENTA)$(B_NAME) ✅compiled!✅$(DEF_COLOR)"

.PHONY: all clean fclean re norm bonus