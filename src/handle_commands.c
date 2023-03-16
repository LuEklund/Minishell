/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:00:10 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/16 16:06:39 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(t_data *info)
{
	t_error	*help;

	help = info->error;
	if (!info->buf)
		return ;
	info->return_val = 258;
	ft_putstr_fd(info->dino, 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (!info->buf[help->i])
		ft_putstr_fd("newline", 2);
	else
		write(2, &info->buf[help->i], 1);	
	if (help->and || help->or || help->out_t || help->in_t)
		write(2, &info->buf[help->i + 1], 1);
	ft_putendl_fd("'", 2);
	free(info->buf);
	free(help);
}

void	handle_pipe(t_data *info)
{
	info->cmds = parse_split(info->buf, '|', info);
	if (init_pipes(info) < 0)
		exit (2);	
	find_the_paths(info);
	while (info->cmds[info->i])
	{
		if (arguing(info))
		{
			info->i += 1;
			continue ;
		}
		if (info->exit || info->built_exec)
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
	empty_redi_list(info);
}



void	handle_buf(t_data *info)
{
	int		i;
	pid_t	kiddo;

	i = 0;
	info->history_buf = ft_strdup(info->buf);
	if (!info->history_buf)
		exit(write(2, "memory error\n", 13));
	if (error_parser(info))
		return (syntax_error(info));
	free(info->error);
	kiddo = fork();
	if (kiddo < 0)
		exit(write(2, "child process error\n", 19));
	if (kiddo)
	{
		parent_signals(info);
		close_pipeline(info); //////does it work????
		free(info->buf);
		return ;
	}
	kid_signals(info);
	if (!info->buf[i])
		exit (0);
	handle_pipe(info);
	get_outed(*info);
	exit(info->return_val);
}
