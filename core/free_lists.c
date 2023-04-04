/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:19:48 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/30 19:19:51 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	empty_redi_list(t_data *info)
{
	t_redi	*latter;
	t_redi	*current;

	current = info->redi_list;
	while (current)
	{
		close(current->fd);
		if (current->file_name)
			free(current->file_name);
		latter = current;
		current = current->next;
		free(latter);
	}
}

void	empty_wild_list(t_data *info)
{
	t_wild	*latter;
	t_wild	*current;

	current = info->wild_list;
	while (current)
	{
		latter = current;
		current = current->next;
		free(latter);
	}
}

void	empty_whelp_list(t_data *info)
{
	t_whelp	*latter;
	t_whelp	*current;

	current = info->wmark_list;
	while (current)
	{
		latter = current;
		current = current->next;
		free(latter);
	}
}

void	empty_args_list(t_data *info)
{
	t_args	*latter;
	t_args	*current;

	current = info->args_list;
	while (current)
	{
		latter = current;
		free(current->arg);
		current = current->next;
		free(latter);
	}
}

void	empty_doc(t_redi *current)
{
	t_redi	*latter;

	while (current)
	{
		latter = current;
		current = current->next;
		close(latter->fd);
		unlink(latter->hd_file);
		free(latter->hd_file);
		free(latter->file_name);
		free(latter);
	}
}
