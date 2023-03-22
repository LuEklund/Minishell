/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:11:39 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/22 12:22:36 by nlonka           ###   ########.fr       */
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
			info->fd_in = dup(g_important.safe_in);
		else
			info->fd_in = info->pipe[(info->i * 2) - 2];
	}
	else
		info->fd_in = in_node->fd;
	if (!out_node)
	{
		if (info->i == info->cmd_amount - 1)
			info->fd_out = dup(g_important.safe_out);
		else
			info->fd_out = info->pipe[(info->i * 2) + 1];
	}
	else
		info->fd_out = out_node->fd;
	info->check = get_duped(info->fd_in, info->fd_out);
}

//	if (info->pipe_amount == 0)
//		info->check = get_duped(info->fd_in, info->fd_out);
//	else if (info->i == 0)
//		info->check = get_duped(info->fd_in, info->pipe[1]);
///	else if (info->i == info->cmd_amount - 1)
//		info->check = get_duped(info->pipe[(info->i * 2) - 2], info->fd_out);
//	else
//		info->check = get_duped(info->pipe[(info->i * 2) - 2], \
//				info->pipe[(info->i * 2) + 1]);

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
	exit(1);
}
