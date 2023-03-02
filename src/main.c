/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:36:44 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/02 16:26:36 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	go_raw(t_data *info)
{
	tcgetattr(STDIN_FILENO, &old_term);
	info->new_term = old_term;
	info->new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &info->new_term);
}

void	the_handler(void)
{
	write(1, "\x1b[A", 3);
	write(1, "\x1b[11C", 5);
	write(1, "exit\n", 5);
	tcsetattr(0, TCSANOW, &old_term);
	exit(0);
}

void	i_c(int signum)
{
	/////broken :(((((((
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	(void)signum;
	return ;
}

void	init_values(t_data *info)
{
	ft_strlcpy(info->dino, "\033[0;31mDinoshell:\033[0m", 25);
	info->fd_in = 0;
	info->fd_out = 1;
	info->return_val = 0;	
	go_raw(info);
	sigemptyset(&info->quit.sa_mask);
	info->quit.sa_handler = i_c;
	info->buf = NULL;
	sigaction(SIGINT, &info->quit, &info->old_act);
	sigemptyset(&info->z_act.sa_mask);
	info->z_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &info->z_act, &info->old_act);
	sigaction(SIGTSTP, &info->z_act, &info->old_act);
}

int main(int ac, char **av, char **ev)
{
	t_data	info;

	if (ac != 1)
		return (printf("bro no need for any arguments\n"));
	(void)av;
	info.envs = copy_env(ev);
	init_values(&info);
	while (37)
	{
		if (info.buf)
			free(info.buf);
		info.buf = readline("\033[0;32mDinoshell>\033[0m ");
		if (info.buf)
		{
			handle_buf(&info);
			if (info.exit)
				break ;
			add_history(info.buf);
		}
		else
			the_handler();
	}
	if (info.buf)
		free(info.buf);
	ft_putstr_fd("\033[0;95mexit\033[0m 🦕\n", 2);
	tcsetattr(0, TCSANOW, &old_term);
	return (0);
}
