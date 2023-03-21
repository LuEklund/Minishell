/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 21:04:12 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/21 14:42:58 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_node(t_cond *node, int b, int sub_b, int level)
{
	printf("level [%d] branch[%d][%d] node type %d\n", level, b, sub_b, node->type);
	if (!node->type)
		printf("content:\n%s\n", node->content);
}

void	print_tree(t_cond *head, int b, int sub_b, int level)
{
	if (!head)
		return ;
	print_tree(head->first_cond, b, sub_b, level + 1);
	print_node(head, b, sub_b, level);
	print_tree(head->sec_cond, b, sub_b + 1, level);
	print_tree(head->next, b + 1, sub_b, level);
}

void	exec_node(t_cond *current, t_data *info)
{
	current->ret = handle_pipe(info, current->content);
	current->up->ret = current->ret;
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
	else if (current->next && ((current->ret && current->next->type == 1) || \
			(!current->ret && current->next->type == 2)))
		traveler(current->next, info);
}

int	go_through_list(t_data *info)
{
	t_cond	*head;
	char	*str;

	str = ft_strdup(info->buf);
	head = create_level(str, NULL, NULL, 1);
	print_tree(head, 1, 1, 1);	
//	free(str);
	info->trinary_tree = head;
	return (1);
}
