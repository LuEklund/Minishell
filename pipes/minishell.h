/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:36:54 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/21 20:16:39 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

struct termios		old_term;

typedef struct s_data
{
	struct termios		new_term;
	struct sigaction	quit;
	struct sigaction	old_act;
	struct sigaction	z_act;
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
	int					check;
}	t_data;

/////
void	print_ar(char **ar);
////

void	handle_buf(t_data *info);

void	is_built_in(t_data *info);
void	test_access(t_data *info, char *str);
void	the_kindergarden(t_data *info);
void	free_commands(t_data *info);

void	close_pipeline(t_data *info);

#endif
