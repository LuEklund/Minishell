/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:36:44 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/01 17:30:35 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	info;

void	go_raw(void)
{
	tcgetattr(STDIN_FILENO, &info.old_term);
	info.new_term = info.old_term;	
	info.new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &info.new_term);
}

void	the_handler(t_data *info)
{
//	(void)info;
//	rl_redisplay();
//	write(1, "\x1b[2J", 4);
//	write(1, "exit", 5);
	write(1, "\x1b[A", 3);
	write(1, "\x1b[11C", 5);
	write(1, "exit\n", 5);
	tcsetattr(0, TCSANOW, &info->old_term);
	exit(0);
}

void	i_c(int signum)
{	
	(void)signum;
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	return ;
}

int main(void)
{
	go_raw();
	sigemptyset(&info.quit.sa_mask);
	info.quit.sa_handler = i_c;
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
		if (!info.buf)
			the_handler(&info);
		else
			add_history(info.buf);
	}
	if (info.buf)
		free(info.buf);
	ft_putstr_fd("\033[0;95mexit\033[0m 🦕\n", 2);
	tcsetattr(0, TCSANOW, &info.old_term);
	return (0);
}
