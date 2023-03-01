/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:36:54 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/01 16:54:10 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

void	rl_replace_line(const char *mutsis, int faijas);

typedef struct s_data
{
	struct termios		old_term;
	struct termios		new_term;
	struct sigaction	quit;
	struct sigaction	old_act;
	struct sigaction	z_act;
	char				*buf;

}	t_data;

#endif
