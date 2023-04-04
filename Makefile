#Target Binary Program
NAME = minishell

#Color scheme
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

#Flags
FLAGS = -Wall -Werror -Wextra -g 
READLINE = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

#Direcory locations
BUILTIN_DIR = builtins/
CMDS_DIR = commands/
CORE_DIR = core/
INPUT_DIR = input_handling/
REDIR_DIR = redirection/
OBJS_DIR = obj/

#Sources by folder
_BUILTIN :=  built.c \
				dir_utils.c \
				directory.c \
				env_export.c \
				env_unset.c \
				env_utils.c \
				environment.c \
				exit_val_calc.c \
				handle_built.c

_CMDS := finding_execs.c \
			handle_commands.c \
			kid_signals.c \
			pipe_utils.c \
			piping.c

_CORE := and_or_lists.c \
			free_lists.c \
			main.c \
			signal_handlers.c \
			trinary_tree.c \
			trinary_utils.c \
			utils.c

_INPUT := error_checks.c \
			error_parser.c \
			error_utils.c \
			expand_envs.c \
			ft_ls.c \
			lex_checks.c \
			parse_split.c \
			split_utils.c \
			wild_cards.c \
			wild_utils.c

_REDIR := here_doc.c \
			open_files.c \
			redirection.c \

ALL_SRCS :=	$(addprefix $(BUILTIN_DIR), $(_BUILTIN)) \
			$(addprefix $(CMDS_DIR), $(_CMDS)) \
			$(addprefix $(CORE_DIR), $(_CORE)) \
			$(addprefix $(INPUT_DIR), $(_INPUT)) \
			$(addprefix $(REDIR_DIR), $(_REDIR))

SRCS = $(_BUILTIN) $(_CMDS) $(_CORE) $(_INPUT) $(_REDIR) 
OBJ_FILES = $(SRCS:.c=.o)
OBJS = $(patsubst %, $(OBJS_DIR)%, $(SRCS:.c=.o))

LIB = libft/libft.a

all: $(NAME)

$(LIB):
	@make all -C libft
	@make bonus -C libft
	@echo "$(COLOUR_GREEN)libft compilation completed$(COLOUR_END)"

$(NAME): $(LIB) $(OBJS_DIR) $(OBJS)
	@cc $(FLAGS) $(OBJS) -o $@ $(READLINE) -L ./libft -lft
	@echo "$(COLOUR_GREEN)$@ created$(COLOUR_END)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "$(COLOUR_BLUE)object directory created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(BUILTIN_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(CMDS_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(CORE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(INPUT_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(REDIR_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

clean:
	@make clean -C libft
	@echo "$(COLOUR_BLUE)libft object files cleaned$(COLOUR_END)"
	@rm -f $(OBJS)
	@echo "$(COLOUR_BLUE)object directory cleaned$(COLOUR_END)"

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
