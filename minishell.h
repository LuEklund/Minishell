/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:36:54 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/08 18:15:19 by nlonka           ###   ########.fr       */
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

typedef struct s_redi
{
	int				type;
	size_t			pipe_n;
	size_t			red_n;
	int				i;
	int				fd;
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
	char				dino[19];
	char				**envs;
	char				**paths;
	char				*buf;
	char				**cmds;
	char				*cmd_to_use;
	char				**args;
	struct s_split		*split;
	size_t				i;
	int					fd_in;
	int					fd_out;
	size_t				pipe_amount;
	size_t				cmd_amount;
	int					*pipe;
	int					built;
	int					return_val;
	int					exit;
	int					red_n;
	int					all_red_n;
	struct s_redi		*redi_list;
	int					hd;
	int					q;
	int					sq;
	int					check;
	int					check2;
	int					safe_out;
	int					safe_in;
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
	int		check;
}	t_split;

void rl_replace_line (const char *text, int clear_undo);


/////
void	print_ar(char **ar);
////

//redirection.c
int		redirection_parser(t_data *info, int i, int i2);

//open_files.c
int		open_files(t_data *info);

//here_doc.c
void	get_hd_file(t_redi *current, t_data *info);

//expand_envs.c
int		expand_envs(const char *str, t_data *info, t_split *help, char **ans);

//handle_commands.c
void	handle_buf(t_data *info);

//finding_execs.c
void	test_access(t_data *info, char *str);
void	find_the_paths(t_data *info);
void	test_paths(t_data *info, char *str);
void	find_execs(t_data *info);
void	arguing(t_data *info);

//piping.c
int		get_duped(int read, int write);
void	the_kindergarden(t_data *info);

//pipe_utils.c
int		init_pipes(t_data *info);
t_redi	*find_note(t_data *info, int type);
void	close_pipeline(t_data *info);
void	free_commands(t_data *info);

//utils.c
void	free_ar(char **ar);
void	get_outed(t_data info);
void	empty_redi_list(t_data *info);

//parse_split.c
int		quote_check(char const *str, int i, int *q, int *sq);
char	**parse_split(char const *str, char c, t_data *info);

//Builtins

//handle_built.c
void	is_built_in(t_data *info);
int	bob_the_builtin(t_data *info);


int		display_curdir();
int		change_dir(t_data *info);
int		change_env_variable(t_data *info, char *var);
int		export_error_handler(t_data *info, char *new_var);
int		find_equal_sign(char *str);
int		env_export(t_data *info, char *manual_add);
int		unset_env(t_data *info, char *rm_var);
int		display_env(t_data *info, int export_type);
char	**copy_env(char **env_to_copy);
int		execute_built(t_data *info);
// int	display_curdir(void);
// int	change_dir(char *path);

#endif
