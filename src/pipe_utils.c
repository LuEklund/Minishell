/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:10:30 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/08 18:11:49 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_pipes(t_data *info)
{
	size_t	i;

	info->redi_list = NULL;
	info->all_red_n = 0;
	if (redirection_parser(info, 0, 0))
	{
		info->return_val = 1;
		return (-1);
	}
	i = 0;
	info->i = 0;
	info->cmd_amount = 0;
	while (info->cmds[info->cmd_amount])
		info->cmd_amount += 1;
	info->pipe_amount = (info->cmd_amount - 1) * 2;
	info->pipe = malloc(sizeof(int) * info->pipe_amount);
	if (!info->pipe)
		return (write(2, "oijoi\n", 6) - 7);
	while (i < info->cmd_amount)
	{
		if (pipe(info->pipe + 2 * i) < 0)
			return (-1);
		i++;
	}
	return (1);
}

t_redi	*find_note(t_data *info, int type)
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
	size_t	i;

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
