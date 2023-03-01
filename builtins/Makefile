NAME = minishell

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

SRC_PATH = src
OBJ_PATH = obj

SRC_NAME = main.c pwd.c
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIB = libft/libft.a
PRINTF = ft_printf/libftprintf.a

all: $(NAME)

$(LIB):
	@make all -C libft
	@make bonus -C libft
	@echo "$(COLOUR_GREEN)libft compilation completed$(COLOUR_END)"

$(NAME): $(LIB) $(OBJ)
	@cc -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -o $@ $^
	@echo "$(COLOUR_GREEN)$@ created$(COLOUR_END)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH) 2> /dev/null
	@cc -Wall -Werror -Wextra -o $@ -c $<
	@echo "$(COLOUR_BLUE)object file created$(COLOUR_END)"

clean:
	@make fclean -C libft
	@echo "$(COLOUR_RED)libft cleaned$(COLOUR_END)"
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "$(COLOUR_RED)object files removed$(COLOUR_END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOUR_RED)$(NAME) removed$(COLOUR_END)"

re: fclean all

bonus: fclean all
