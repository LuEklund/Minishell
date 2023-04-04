/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:23:00 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/24 11:50:37 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	history_handler(char *str)
{
	if (ft_strncmp(str, "", 1))
		add_history(str);
	free(str);
}

void	set_signals(t_data *info)
{
	info->hd = 0;
	info->hd_list = NULL;
	info->wmark_list = NULL;
	info->args_list = NULL;
	info->buf = NULL;
	info->pipe_amount = 0;
	info->quit.sa_handler = i_c;
	sigemptyset(&info->quit.sa_mask);
	info->quit.sa_flags = 0;
	info->z_act.sa_handler = SIG_IGN;
	sigemptyset(&info->z_act.sa_mask);
	info->z_act.sa_flags = 0;
	sigaction(SIGINT, &info->quit, &info->old_act);
	sigaction(SIGQUIT, &info->z_act, &info->old_act);
	sigaction(SIGTSTP, &info->z_act, &info->old_act);
}

void	init_values(t_data *info)
{
	ft_strlcpy(info->dino, "\033[0;31mDinoshell: \033[0m", 25);
	info->fd_in = 0;
	info->fd_out = 1;
	info->return_val = 0;
	info->history_buf = NULL;
	info->split = NULL;
	info->exit = 0;
	tcgetattr(info->fd_in, &info->old_term);
	tcgetattr(info->fd_in, &info->new_term);
	info->new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(info->fd_in, TCSAFLUSH, &info->new_term);
}

int	main(int ac, char **av, char **ev)
{
	t_data	info;

	if (ac != 1 || !av[2])
		return (ft_putstr_fd("no arguments accepted\n", 2), 127);
	info.envs = copy_env(ev);
	upgrade_shell_lvl(&info, info.envs);
	init_values(&info);
	while (37)
	{
		set_signals(&info);
		info.buf = readline("\033[0;32mDinoshell>\033[0m ");
		if (info.buf)
		{
			handle_buf(&info);
			history_handler(info.history_buf);
			if (info.exit)
				break ;
		}
		else
			the_handler(info);
	}
	get_outed(info);
	return (info.return_val);
}
