/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:36:44 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/20 16:29:12 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	go_raw(t_data *info)
{
	tcgetattr(STDIN_FILENO, &old_term);
	info->new_term = old_term;
//	info->new_term.c_cc[VEOF] = 3;
//	info->new_term.c_cc[VINTR] = 4;
	info->new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &info->new_term);
}

void	the_handler(int signum)
{
	ioctl(0, TIOCSTI, "\n");	
//	rl_replace_line("", 0);
//	rl_on_new_line();
//	ft_putstr_fd("\n", 0);
	tcsetattr(0, TCSANOW, &old_term);
	exit(signum);
}

void	i_c(int signum)
{
	(void)signum;

	ioctl(0, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();

//	rl_redisplay();
}

int main(void)
{
	t_data	info;

	go_raw(&info);
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
			the_handler(0);
//		handle_buf(&info);
	}
	if (info.buf)
		free(info.buf);
	ft_putstr_fd("\033[0;95mexit\033[0m 🦕\n", 2);
	tcsetattr(0, TCSANOW, &old_term);
	return (0);
}
