#Target Binary Program
NAME = minishell

#Color scheme
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

#Flags
FLAGS = -Wall -Werror -Wextra

#Direcory locations
SRCS_DIR = src/
BUILTIN_DIR = builtins/
OBJS_DIR = obj/

#Sources by folder
_SRCS :=  main.c \
			handle_commands.c \
			pipe_utils.c \
			parse_split.c \
			utils.c

ALL_SRCS :=	$(addprefix $(SRCS_DIR), $(_SRCS))


SRCS = $(_SRCS)
OBJ_FILES = $(SRCS:.c=.o)
OBJS = $(patsubst %, $(OBJS_DIR)%, $(SRCS:.c=.o))

LIB = libft/libft.a

all: $(NAME)

$(LIB):
	@make all -C libft
	@make bonus -C libft
	@echo "$(COLOUR_GREEN)libft compilation completed$(COLOUR_END)"

$(NAME): $(LIB) $(OBJS_DIR) $(OBJS)
	@cc $(FLAGS) $(OBJS) -o $@ -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -L ./libft -lft
	@echo "$(COLOUR_GREEN)$@ created$(COLOUR_END)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@make clean -C libft
	@rm -f $(OBJS)
	@echo "$(COLOUR_BLUE)libft object files cleaned$(COLOUR_END)"

fclean: clean
	@rm -rf $(OBJS_DIR)
	@rm -f $(LIB)
	@echo "$(COLOUR_RED)libft.a removed$(COLOUR_END)"
	@rm -f $(NAME)
	@echo "$(COLOUR_RED)$(NAME) removed$(COLOUR_END)"

re: fclean all

bonus: fclean all



# SRC_PATH = src

# SRC_NAME = main.c handle_commands.c pipe_utils.c parse_split.c utils.c

# SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

# LIB = libft/libft.a

# all: $(NAME)

# $(LIB):
# 	@make all -C libft
# 	@make bonus -C libft
# 	@echo "$(COLOUR_GREEN)libft compilation completed$(COLOUR_END)"

# $(NAME): $(LIB) $(SRC)
# 	@cc $(FLAGS) -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -o $@ $^
# 	@echo "$(COLOUR_GREEN)$@ created$(COLOUR_END)"

# clean:
# 	@make clean -C libft
# 	@echo "$(COLOUR_BLUE)libft object files cleaned$(COLOUR_END)"

# fclean: clean
# 	@rm -f $(LIB)
# 	@echo "$(COLOUR_RED)libft.a removed$(COLOUR_END)"
# 	@rm -f $(NAME)
# 	@echo "$(COLOUR_RED)$(NAME) removed$(COLOUR_END)"

# re: fclean all

# bonus: fclean all
