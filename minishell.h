/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:36:54 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/24 13:09:05 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/stat.h>

typedef struct s_cond
{
	int				type;
	int				ret;
	int				hd_n;
	char			*content;
	struct s_cond	*up;
	struct s_cond	*first_cond;
	struct s_cond	*sec_cond;
	struct s_cond	*back;
	struct s_cond	*next;
}	t_cond;

typedef struct s_args
{
	char			*arg;
	int				i;
	struct s_args	*next;
}	t_args;

typedef struct s_wild
{
	int				i;
	struct s_wild	*next;
}	t_wild;

typedef struct s_whelp
{
	int				n;
	int				h;
	int				valid;
	struct s_whelp	*next;
}	t_whelp;

typedef struct s_redi
{
	int				type;
	size_t			pipe_n;
	size_t			red_n;
	int				i;
	int				cmd_n;
	int				fd;
	int				used;
	char			*hd_file;
	char			*file_name;
	struct s_redi	*next;
}	t_redi;

typedef struct s_data
{
	struct termios		new_term;
	struct termios		old_term;
	struct sigaction	quit;
	struct sigaction	old_act;
	struct sigaction	z_act;
	struct sigaction	seg_act;
	struct sigaction	terminate;
	char				dino[19];
	char				**envs;
	char				**paths;
	char				*buf;
	char				*history_buf;
	char				**cmds;
	char				*cmd_to_use;
	char				**args;
	struct s_args		*args_list;
	struct s_split		*split;
	size_t				i;
	int					fd_in;
	int					fd_out;
	size_t				pipe_amount;
	size_t				cmd_amount;
	int					*pipe;
	pid_t				*kiddo;
	int					built;
	int					return_val;
	int					exit;
	int					red_n;
	int					all_red_n;
	struct s_redi		*redi_list;
	struct s_redi		*hd_list;
	int					hd;
	int					hd_n;
	int					hd_error;
	int					cmd_n;
	int					q;
	int					sq;
	struct s_cond		*trinary_tree;
	struct s_whelp		*wmark_list;
	struct s_wild		*wild_list;
	struct s_error		*error;
	int					built_exec;
	int					check;
	int					check2;
}	t_data;

typedef struct s_split
{
	int		h;
	int		h2;
	int		i;
	int		i2;
	int		i3;
	int		l;
	int		q;
	int		sq;
	char	c;
	int		expand_type;
	int		check;
}	t_split;

typedef struct s_error
{
	size_t	i;
	int		plus_yes;
	int		rm_par;
	int		space;
	int		token;
	int		q;
	int		sq;
	int		pipe;
	int		or;
	int		amper;
	int		and;
	int		par;
	int		in_o;
	int		out_o;
	int		in_t;
	int		out_t;
	int		special;
}	t_error;

void		rl_replace_line(const char *text, int clear_undo);

//signal_handlers.c
void		the_handler(t_data info);
void		i_c(int signum);

//error_parser.c
int			error_parser(t_data *info);

//error_utils.c
void		reset_token_val(t_error *help, char *str, int var);
void		get_tokenized(t_error *help, char *str, int var);
int			parenthesee(t_error *he, char *str);
int			redi_syntax(t_error *he, char *str);

//and_or_lists.c
void		empty_tree(t_cond *head);
void		traveler(t_cond *current, t_data *info);
int			go_through_list(t_data *info);

//trinary_tree.c
t_cond		*create_level(char *str, t_cond *back, t_cond *up, int var);

//trinary_utils.c
int			check_for_logic(char *str, int var);
char		*par_ser(char *str, t_error *help);
t_cond		*check_content(char *str, t_cond *up, t_error help);

//kid_signals.c
void		slashing(int signum);
void		kid_c(int signum);
void		kid_signals(t_data *info);
void		parent_signals(t_data *info, int var);

//redirection.c
int			redirection_parser(t_data *info, int i, int i2);

//wild_cards.c
void		wild_card_check(t_data *info, int i, int i2);

//wild_utils.c
void		add_to_list(char *str, t_args *current, int i);
void		remove_from_list(t_data *info, char *str, t_args *current);
t_args		*new_arg(char *str, int i);
t_args		*copy_ar_to_list(char **ar);
char		**copy_list_to_ar(t_args *current);

//ft_ls.c
char		**ft_ls(void);

//open_files.c
int			find_file(t_redi *current, t_data *info);
int			open_files(t_data *info);

//here_doc.c
t_redi		*copy_hd_node(t_redi *hd, int red_n);
int			find_hd(char *str, t_data *info, int i, int i2);

//expand_envs.c
int			expand_envs(const char *s, t_data *in, t_split *he, char **a);

//handle_commands.c
int			handle_pipe(t_data *info, char *cmd_str);
int			work_pipe(t_data *info, char *cmd_chain);
void		handle_buf(t_data *info);

//finding_execs.c
void		test_access(t_data *info, char *str);
void		find_the_paths(t_data *info);
void		test_paths(t_data *info, char *str);
void		find_execs(t_data *info);
int			arguing(t_data *info);

//piping.c
int			get_duped(int read, int write);
void		the_kindergarden(t_data *info);

//pipe_utils.c
int			init_pipes(t_data *info);
t_redi		*find_node(t_data *info, int type);
void		close_pipeline(t_data *info);
void		free_commands(t_data *info);

//utils.c
void		free_help(char *str);
void		free_ar(char **ar);
void		get_outed(t_data info);
int			redir_input_parser(const char *str, t_split *help, int var);

//free_lists.c
void		empty_redi_list(t_data *info);
void		empty_wild_list(t_data *info);
void		empty_whelp_list(t_data *info);
void		empty_args_list(t_data *info);
void		empty_doc(t_redi *current);

//parse_split.c
char		**parse_split(char const *str, char c, t_data *info);

//split_utils.c
int			red_c(char const *str, t_split *help, int i);
void		wild_marker(char const *str, t_split help, t_data *info);
void		init_help(t_data *info, t_split *help, char c, char const *str);

//lex_checks.c
int			quote_check(char const *str, int i, int *q, int *sq);
int			quote_see(char const *str, t_split help);
int			expand_check(char const *str, t_split *help);

//Builtins

//bulit.c
long long	built_exit(t_data *info);
int			execute_built(t_data *info);

//dir_utils.c
int			changde_dir_success(t_data *info, char *curr_dir);
void		changde_dir_error(t_data *info, char *curr_dir);
int			apply_change(t_data *info, char *path);

//directory.c
int			display_curdir(void);
char		*get_curdir(void);
int			change_dir(t_data *info);

//env_export
int			env_error_handler(t_data *info, char *new_var, char *type);
int			env_export(t_data *info, char *manual_add);

//env_unset
int			env_unset(t_data *info, char *manual_remove);

//env_utils.c
int			upgrade_shell_lvl(t_data *ifno, char **env_to_copy);
int			find_sign(char *str, char c);
int			change_env_variable(t_data *info, char *var);

//environment.c
char		**copy_env(char **env_to_copy);
int			display_env(t_data *info, int export_type);

//exit_val_calc.c
long long	exit_atoi(t_data *info, int *sign);

//handle_built.c
void		work_built(t_data *info, char **args);
void		is_built_in(t_data *info, char *arg);

#endif