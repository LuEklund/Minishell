/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:36:54 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/07 20:18:57 by nlonka           ###   ########.fr       */
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

struct termios		g_old_term;

typedef struct s_redi
{
	int				type;
	int				pipe_n;
	int				red_n;
	int				i;
	int				fd;
	char			*file_name;
	struct s_redi	*next;
}	t_redi;

typedef struct s_data
{
	struct termios		new_term;
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
	int					q;
	int					sq;
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
	int		check;
}	t_split;

void rl_replace_line (const char *text, int clear_undo);


/////
void	print_ar(char **ar);
////

//redirection.c
int		redirection_parser(t_data *info, int i, int i2);

//redirection2.c
int		continue_redir(t_data *info);

void	bob_the_builtin(t_data *info);

int		expand_envs(const char *str, t_data *info, t_split *help, char **ans);

void	handle_buf(t_data *info);

void	is_built_in(t_data *info);
void	test_access(t_data *info, char *str);
void	the_kindergarden(t_data *info);
void	free_commands(t_data *info);

//utils.c
void	free_ar(char **ar);
void	close_pipeline(t_data *info);
void	empty_redi_list(t_data *info);

int		quote_check(char const *str, int i, int *q, int *sq);
char	**parse_split(char const *str, char c, t_data *info);

//Builtins
int		display_curdir();
int		change_dir(char *path);

int		env_export(t_data *info, char *new_var);
int		unset_env(t_data *info, char *rm_var);
int		display_env(t_data *info, int export_type);
char	**copy_env(char **env_to_copy);
int		execute_built(t_data *info);
// int	display_curdir(void);
// int	change_dir(char *path);

#endif
