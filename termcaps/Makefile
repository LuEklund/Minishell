NAME = minishell

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

SRC_PATH = src

SRC_NAME = main.c

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

LIB_PATH = ../libft/

LIB_NAME = libft.a

LIB = $(addprefix $(LIB_PATH)/,$(LIB_NAME))

all: $(NAME)

$(LIB):
	@make all -C $(LIB_PATH)
	@make bonus -C $(LIB_PATH)
	@echo "$(COLOUR_GREEN)libft compilation completed$(COLOUR_END)"

$(NAME): $(LIB) $(SRC)
	@cc -Wall -Werror -Wextra -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -o $@ $^
	@echo "$(COLOUR_GREEN)$@ created$(COLOUR_END)"

clean:
	@make clean -C $(LIB_PATH)
	@echo "$(COLOUR_BLUE)libft object files cleaned$(COLOUR_END)"

fclean: clean
	@rm -f $(LIB)
	@echo "$(COLOUR_RED)$(LIB_NAME) removed$(COLOUR_END)"
	@rm -f $(NAME)
	@echo "$(COLOUR_RED)$(NAME) removed$(COLOUR_END)"

re: fclean all

bonus: fclean all
