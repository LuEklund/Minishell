/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:23:00 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/23 14:04:22 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	the_handler(t_data info)
{
	int	i;

	i = 1;
	write(1, "\x1b[A", 3);
	write(1, "\x1b[11C", 5);
	while (i != info.pos)
	{
		write(1, "\x1b[1C", 4);
		i++;
	}
	write(1, "exit\n", 5);
	get_outed(info);
	exit(0);
}

void	i_c(int signum)
{
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	(void)signum;
	return ;
}

void	history_handler(char *str)
{
	if (ft_strncmp(str, "", 1))
		add_history(str);
}

void	set_signals(t_data *info)
{
	info->pipe_amount = 0;
	sigemptyset(&info->quit.sa_mask);
	info->quit.sa_handler = i_c;
	info->buf = NULL;
	sigaction(SIGINT, &info->quit, &info->old_act);
	sigemptyset(&info->z_act.sa_mask);
	info->z_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &info->z_act, &info->old_act);
	sigaction(SIGTSTP, &info->z_act, &info->old_act);
	sigemptyset(&info->z_act.sa_mask);
}

void	init_values(t_data *info)
{
	ft_strlcpy(info->dino, "\033[0;31mDinoshell: \033[0m", 25);
	info->pos = 1;
	info->fd_in = 0;
	info->fd_out = 1;
	g_important.safe_out = dup(1);
	g_important.safe_in = dup(0);
	info->return_val = 0;
	info->exit = 0;
	tcgetattr(g_important.safe_in, &g_important.old_term);
	info->new_term = g_important.old_term;
	info->new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(g_important.safe_in, TCSAFLUSH, &info->new_term);
}

void	find_pos(t_data *info)
{
	char			buf[32];
	unsigned int	i;
	unsigned int	i2;
	char			help[10];

	i = 0;
	if (write(1, "\x1b[6n", 4) != 4)
		return ; //error
	while (i < sizeof(buf) - 1)
	{
		if (read(0, &buf[i], 1) != 1)
			break ;
		if (buf[i] == 'R')
			break ;
		i++;
	}
	buf[i] = '\0';
//	printf("'%s'\n", &buf[1]);
	i2 = 1;
	i = 1;
	while (buf[i2] && buf[i2] != 'R')
		i2++;
	while (buf[i] && buf[i] != ';')
		i++;
	ft_strlcpy(help, buf + i + 1, i2 - i + 1);
//	printf("'%s'\n", help);
	info->pos = ft_atoi(help);
//	ft_putnbr_fd(info->pos, 2);
}

int main(int ac, char **av, char **ev)
{
	t_data	info;

	if (ac != 1 || !av[2])
		return (printf("bro no need for any arguments\n"));
	make_env_file_first_time(&info, ev);
	upgrade_shell_lvl(&info, ev);
	init_values(&info);
	while (37)
	{
		set_signals(&info);
	//	find_pos(&info);
		info.buf = readline("\033[0;32mDinoshell>\033[0m ");
		if (info.buf)
		{
			handle_buf(&info);
			if (info.exit)
				break ;
			history_handler(info.history_buf);
		}
		else
			the_handler(info);
	}
	if (info.history_buf)
		free(info.history_buf);
	ft_putstr_fd("\033[0;95mexit\033[0m 🦕\n", 2);
	get_outed(info);
	return (info.return_val);
}
