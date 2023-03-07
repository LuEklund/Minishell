/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:36:54 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/02 14:23:13 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
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

struct termios		old_term;

typedef struct s_data
{
	struct termios		new_term;
	struct sigaction	quit;
	struct sigaction	old_act;
	struct sigaction	z_act;
	char				dino[18];
	char				**envs;
	char				**paths;
	char				*buf;
	char				**cmds;
	char				*cmd_to_use;
	char				**args;
	size_t				i;
	int					fd_in;
	int					fd_out;
	size_t				pipe_amount;
	size_t				cmd_amount;
	int					*pipe;
	int					built;
	int					return_val;
	int					exit;
	int					check;
}	t_data;


void rl_replace_line (const char *text, int clear_undo);

typedef struct s_split
{
	int	h;
	int	h2;
	int	i;
	int	i2;
	int	i3;
	int	l;
	int	h2i;
	int	q;
	int	sq;
}	t_split;


/////
void	print_ar(char **ar);
////

void	bob_the_builtin(t_data *info);


void	handle_buf(t_data *info);

void	is_built_in(t_data *info);
void	test_access(t_data *info, char *str);
void	the_kindergarden(t_data *info);
void	free_commands(t_data *info);

void	free_ar(char **ar);
void	close_pipeline(t_data *info);
char	**parse_split(char const *str, char c);

//Builtins
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
