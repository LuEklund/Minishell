/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:00:10 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/11 19:45:47 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(t_data *info, int var)
{
	info->return_val = 258;
	ft_putstr_fd(info->dino, 2);
	if (var)
		ft_putendl_fd("syntax error near unexpected token `||'", 2);
	else
	{
		empty_redi_list(info);
		free(info->cmds);
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
	}
	exit(69);
}

void	handle_pipe(t_data *info)
{
	info->cmds = parse_split(info->buf, '|', info);
	if (!info->cmds || !info->cmds[0])
		return (syntax_error(info, 1));
	if (init_pipes(info) < 0)
		return (syntax_error(info, 0));
	find_the_paths(info);
	while (info->cmds[info->i] && !info->check)
	{
		arguing(info);
		if (info->check || info->exit)
			break ;
		info->kiddo[info->i] = fork();
		if (info->kiddo[info->i] < 0)
			return (ft_putendl_fd("stillbirth?????\n", 2));
		if (info->kiddo[info->i] == 0)
			the_kindergarden(info);
		free_commands(info);
		info->i += 1;
	}
	close_pipeline(info);
	info->i = 0;
	while ((waitpid(info->kiddo[info->i], &info->return_val, 0)) > 0)
		info->i += 1;
	free(info->kiddo);
	info->return_val = WEXITSTATUS(info->return_val);
	empty_redi_list(info);
}

void	handle_buf(t_data *info)
{
	int		i;
	pid_t	kiddo;

	i = 0;
	kiddo = fork();
	if (kiddo)
	{
		mute_signals(info);
		while ((wait(&info->return_val)) > 0)
			;
		if (info->return_val == 33280)
		{
			printf("^C\n");
			info->return_val = 130;
		}
		else if (info->return_val == 33536)
		{
			printf("Quit: 3\n");
			info->return_val = 131;
		}
		else if (info->return_val == 17664)
			info->return_val = 258;
		return ;
	}
	mute_signals(info);
	sigemptyset(&info->quit.sa_mask);
	info->quit.sa_handler = kid_c;
	sigaction(SIGINT, &info->quit, &info->old_act);
	sigemptyset(&info->z_act.sa_mask);
	info->z_act.sa_handler = slashing;
	sigaction(SIGQUIT, &info->z_act, &info->old_act);
	while (info->buf[i] && (info->buf[i] == ' ' || \
				(info->buf[i] > 8 && info->buf[i] < 14)))
		i++;
	if (!info->buf[i])
		exit (0);
	handle_pipe(info);
	get_outed(*info);
	printf("jouuu\n");
	exit(info->return_val);
}
