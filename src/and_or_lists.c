/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 21:04:12 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/17 18:54:37 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_node(t_cond *node, int i, int level)
{
	printf("level [%d] branch[%d] node type %d\n", level, i, node->type);
	if (!node->type)
		printf("content:\n%s\n", node->content);
}

void	print_tree(t_cond *head, int i, int level)
{
	while (head)
	{
		print_node(head, i, level);
		print_tree(head->first_cond, i, level + 1);
		print_tree(head->sec_cond, i, level + 1);
		i++;
		head = head->next;
	}
}

void	go_through_list(t_data *info)
{
	t_cond	*head;

	head = create_level(info->buf, NULL);
	if (!head)
		return ;//handle normally
	print_tree(head, 1, 1);	
}
