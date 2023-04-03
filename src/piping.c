/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:11:39 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/24 10:00:24 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_duped(int read, int write)
{
	int	check;

	check = dup2(read, 0);
	if (check < 0)
		return (1);
	check = dup2(write, 1);
	if (check < 0)
		return (1);
	return (0);
}

void	the_piper(t_data *info)
{
	t_redi	*in_node;
	t_redi	*out_node;

	in_node = find_node(info, 0);
	out_node = find_node(info, 1);
	if (!in_node)
	{
		if (info->i == 0)
			info->fd_in = dup(info->fd_in);
		else
			info->fd_in = info->pipe[(info->i * 2) - 2];
	}
	else
		info->fd_in = in_node->fd;
	if (!out_node)
	{
		if (info->i == info->cmd_amount - 1)
			info->fd_out = dup(info->fd_out);
		else
			info->fd_out = info->pipe[(info->i * 2) + 1];
	}
	else
		info->fd_out = out_node->fd;
	info->check = get_duped(info->fd_in, info->fd_out);
}

void	the_kindergarden(t_data *info)
{
	the_piper(info);
	close(info->fd_in);
	close(info->fd_out);
	if (!info->check && info->pipe_amount != 0)
		close_pipeline(info);
	if (!info->check && info->built)
		exit(execute_built(info));
	if (!ft_strncmp(info->cmd_to_use, " ", 2))
		exit (0);
	if (!info->check)
	{
		execve(info->cmd_to_use, info->args, info->envs);
		info->check = 1;
	}
	exit(0);
}

void	go_through_pipeline(t_data *info)
{
	while (info->cmds[info->i])
	{
		if (arguing(info))
		{
			info->i += 1;
			continue ;
		}
		if (info->exit)
			break ;
		info->kiddo[info->i] = fork();
		if (info->kiddo[info->i] < 0)
			exit(write(2, "forking errawr🦖\n", 16));
		if (info->kiddo[info->i] == 0)
			the_kindergarden(info);
		free_commands(info);
		info->i += 1;
	}
}

int	handle_pipe(t_data *info, char *cmd_str)
{
	info->wmark_list = NULL;
	info->cmds = parse_split(cmd_str, '|', info);
	if (init_pipes(info) < 0)
		exit (2);
	find_the_paths(info);
	go_through_pipeline(info);
	close_pipeline(info);
	info->i = 0;
	while ((waitpid(info->kiddo[info->i], &info->return_val, 0)) > 0)
		info->i += 1;
	free_ar(info->envs);
	free_ar(info->cmds);
	free(info->kiddo);
	free_ar(info->paths);
	if (info->pipe)
		free(info->pipe);
	empty_redi_list(info);
	return (info->return_val);
}
