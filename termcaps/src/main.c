/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:36:44 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/17 15:16:18 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	info;

void	go_raw(void)
{
	tcgetattr(STDIN_FILENO, &info.old_term);
	info.new_term = info.old_term;
	info.new_term.c_cc[VSTART] = 3;
	info.new_term.c_cc[VINTR] = 4;
//	info.new_term.c_cc[VSTART] = 26;
//	info.new_term.c_lflag &= ~(ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &info.new_term);
}

void	the_handler(int signum)
{
	if (info.buf)
		return ;
	ft_putstr_fd("\033[0;95mexit\033[0m 🦕\n", 2);
	tcsetattr(0, TCSANOW, &info.old_term);
	exit(signum);
	return ;
}

void	zzz(int signum)
{
	/////broken :(((((((
	rl_redisplay();
	(void)signum;
	return ;
}

int main(void)
{
	go_raw();
	sigemptyset(&info.quit.sa_mask);
	info.quit.sa_handler = the_handler;
	info.buf = NULL;
	sigaction(SIGINT, &info.quit, &info.old_act);
	sigemptyset(&info.z_act.sa_mask);
	info.z_act.sa_handler = zzz;
	sigaction(SIGTSTP, &info.z_act, &info.old_act);
	while (ft_strncmp(info.buf, "exit", 5))
	{
		if (info.buf)
			free(info.buf);
		info.buf = readline("\033[0;32mDinoshell>\033[0m ");	
	}
	if (info.buf)
		free(info.buf);
	ft_putstr_fd("\033[0;95mexit\033[0m 🦕\n", 2);
	tcsetattr(0, TCSANOW, &info.old_term);
	return (0);
}
