/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:35:48 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/31 12:35:50 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	the_handler(t_data info)
{
	write(1, "\x1b[A", 3);
	write(1, "\x1b[11C", 5);
	write(1, "exit\n", 5);
	get_outed(info);
	exit(info.return_val);
}

void	i_c(int signum)
{
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	(void)signum;
	return ;
}

void	slashing(int signum)
{
	(void)signum;
	exit(131);
}

void	kid_c(int signum)
{
	(void)signum;
	exit(130);
}
