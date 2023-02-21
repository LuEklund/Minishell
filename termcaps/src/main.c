/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:36:44 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/20 15:56:34 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	info;

void	go_raw(void)
{
	tcgetattr(STDIN_FILENO, &info.old_term);
	info.new_term = info.old_term;
	info.new_term.c_cc[VEOF] = 3;
	info.new_term.c_cc[VINTR] = 4;
	info.new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &info.new_term);
}

void	the_handler(int signum)
{
	rl_on_new_line();
	rl_replace_line("exit", 0);
	rl_redisplay();
	ft_putstr_fd("\n", 2);
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
	size_t	test = 0;
	go_raw();
	sigemptyset(&info.quit.sa_mask);
	info.quit.sa_handler = the_handler;
	info.buf = NULL;
	sigaction(SIGINT, &info.quit, &info.old_act);
	sigemptyset(&info.z_act.sa_mask);
	info.z_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &info.z_act, &info.old_act);
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
