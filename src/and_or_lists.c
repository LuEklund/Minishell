/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 21:04:12 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/24 12:34:27 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	empty_tree(t_cond *head)
{
	if (!head)
		return ;
	empty_tree(head->first_cond);
	empty_tree(head->sec_cond);
	empty_tree(head->next);
	if (!head->type)
		free_help(head->content);
	free(head);
}

void	look_for_heredocs(t_cond *head, t_data *info)
{
	if (!head || info->hd_error)
		return ;
	look_for_heredocs(head->first_cond, info);
	if (!head->type)
	{
		info->hd_error = find_hd(head->content, info, 0, 0);
		info->hd += 1;
		head->hd_n = info->hd;
	}
	look_for_heredocs(head->sec_cond, info);
	look_for_heredocs(head->next, info);
}

void	exec_node(t_cond *current, t_data *info)
{
	current->ret = work_pipe(info, current->content);
	info->cmd_n += 1;
	info->return_val = current->ret;
	while (current->up)
	{
		current->up->ret = current->ret;
		current = current->up;
	}
}

void	traveler(t_cond *current, t_data *info)
{
	if (!current)
		return ;
	traveler(current->first_cond, info);
	if (!current->type)
		exec_node(current, info);
	if ((current->ret && current->type == 1) || (!current->ret && \
		current->type == 2))
		traveler(current->sec_cond, info);
	if (current->next)
	{
		current->next->ret = current->ret;
		traveler(current->next, info);
	}
}

void	print_tree(t_cond *head, int b, int sub_b, int level);

int	go_through_list(t_data *info)
{
	t_cond	*head;
	char	*str;
	size_t	i;

	i = 0;
	str = ft_strdup(info->buf);
	if (!str)
		exit(write(2, "memory errawr🦖\n", 15));
	while (str[i] && (str[i] == '(' || str[i] == ')'))
		i++;
	if (!str[i])
		head = NULL;
	else
		head = create_level(str, NULL, NULL, 1);
	info->hd = 0;
	info->hd_n = 0;
	info->hd_error = 0;
	print_tree(head, 0, 0, 0);
	look_for_heredocs(head, info);
	info->trinary_tree = head;
	return (1);
}
