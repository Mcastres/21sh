# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmadad <hmadad@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/12 14:56:33 by hmadad            #+#    #+#              #
#    Updated: 2017/04/28 14:13:41 by mcastres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRC_PATH = ./srcs

SRCS_NAME = ft_21sh.c \
			ft_env.c \
			ft_find_last_pwd.c \
			ft_arrow_key.c \
			ft_init_term.c \
			ft_lst_history.c \
			ft_ltos.c \
			ft_prompt.c \
			ft_read_commande.c \
			ft_realloc.c \
			ft_print_char.c \
			ft_termcap_delete.c \
			ft_strtrimb.c \
			ft_exec_commande.c \
			ft_change_home_sign.c \
			ft_exit.c \
			ft_commande.c \
			ft_echo.c \
			ft_prepare_cd.c \
			ft_cd.c \
			ft_cd_error.c \
			ft_trim.c \
			ft_get_pwd.c \
			ft_pipette.c \
			ft_quote.c \
			ft_redirection.c \
			main.c \

# COLORS
C_NO =	"\033[00m"
C_OK =	"\033[35m"
C_GOOD = "\033[32m"
C_ERROR = "\033[31m"
C_WARN = "\033[33m"

# DBG MESSAGE
SUCCESS	= $(C_GOOD)SUCCESS$(C_NO)
OK = $(C_OK)OK$(C_NO)

SRC = $(addprefix $(SRC_PATH)/, $(SRCS_NAME))

OBJECTS = $(SRCS_NAME:.c=.o)

FLAGS = -Wall -Wextra -Werror -O3

all: $(NAME)

$(NAME):
	@make -C ./libft
	@gcc $(FLAGS) -I ./includes -c $(SRC)
	@gcc -o $(NAME) -lreadline -ltermcap $(OBJECTS) -lft -L libft
	@clear
	@echo "Compiling" [$(NAME)] $(SUCCESS)

.PHONY: clean
clean:
	@rm -f $(OBJECTS)
	@make clean -C ./libft
	@echo "Cleaning" [$(NAME)] "..." $(OK)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft
	@echo "Delete" [$(NAME)] $(OK)

re: fclean all
