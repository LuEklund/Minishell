/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:36:54 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/21 16:47:43 by nlonka           ###   ########.fr       */
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
	char				*buf;
	char				**cmds;
	char				*work_cmd;
	size_t				i;
	size_t				last_i;
	int					fd_in;
	int					fd_out;
	int					pipe_amount;
	int					cmd_amount;
	int					*pipe;
	int					built;
	int					check;
}	t_data;

void	handle_buf(t_data *info);

void	is_built_in(t_data *info);
size_t	when_does_it_end(char *str, size_t start);

#endif
