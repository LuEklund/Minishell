/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:10:30 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/24 09:56:39 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_first(t_data *info)
{
	info->pipe = NULL;
	info->redi_list = NULL;
	info->all_red_n = 0;
	if (redirection_parser(info, 0, 0))
	{
		info->return_val = 1;
		return (1);
	}
	info->i = 0;
	info->cmd_amount = 0;
	while (info->cmds[info->cmd_amount])
		info->cmd_amount += 1;
	return (0);
}

int	init_pipes(t_data *info)
{
	int	i;

	i = 0;
	if (init_first(info))
		return (-1);
	info->pipe_amount = (info->cmd_amount - 1) * 2;
	if (sizeof(pid_t) * info->cmd_amount > 0)
		info->kiddo = malloc(sizeof(pid_t) * info->cmd_amount);
	if (info->pipe_amount < 0)
		return (-1);
	if (info->pipe_amount > 0)
	{
		info->pipe = malloc(sizeof(int) * info->pipe_amount);
		if (!info->pipe)
			exit(write(2, "memory errawr🦖\n", 16));
	}
	else
		return (1);
	while (i < info->cmd_amount && info->cmd_amount > 1)
	{
		if (pipe(info->pipe + 2 * i) < 0)
			return (-1);
		i++;
	}
	return (1);
}

t_redi	*find_node(t_data *info, int type)
{
	t_redi	*current;
	t_redi	*ans;

	current = info->redi_list;
	while (current && current->pipe_n != info->i)
		current = current->next;
	ans = NULL;
	while (current && current->pipe_n == info->i)
	{
		if ((current->type < 0 && type) || (!type && current->type > 0))
			ans = current;
		current = current->next;
	}
	return (ans);
}

void	close_pipeline(t_data *info)
{
	int	i;

	i = 0;
	while (i != info->pipe_amount)
	{
		close(info->pipe[i]);
		i++;
	}
}

void	free_commands(t_data *info)
{
	free_ar(info->args);
	free(info->cmd_to_use);
}
