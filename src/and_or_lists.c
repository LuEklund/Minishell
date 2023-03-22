/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 21:04:12 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/22 13:05:06 by nlonka           ###   ########.fr       */
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
//	printf("executing\n");
	current->ret = handle_pipe(info, current->content);
//	printf("executed\n");
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
//	printf("current type is %d and ret is %d\n", current->type, current->ret);
//	if (!current->type)
//		printf("current command is\n%s\nand up is %p\n", current->content, current->up);
	if ((current->ret && current->type == 1) || (!current->ret && \
		current->type == 2))
		traveler(current->sec_cond, info);
	if (current->next)
	{
		current->next->ret = current->ret;
		traveler(current->next, info);
	}

}

int	go_through_list(t_data *info)
{
	t_cond	*head;
	char	*str;
	size_t	i;

	i = 0;
	str = ft_strdup(info->buf);
//	printf("str is '%s'\n", str);
	while (str[i] && (str[i] == '(' || str[i] == ')'))
		i++;
	if (!str[i])
		head = NULL;
	else
		head = create_level(str, NULL, NULL, 1);
//	print_tree(head, 1, 1, 1);	
//	free(str);
	info->trinary_tree = head;
	return (1);
}
