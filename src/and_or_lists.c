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
	print_tree(head->sec_cond, b, sub_b + 1, level);//
	print_tree(head->next, b + 1, sub_b, level);
}

void	empty_tree(t_cond *head)
{
	if (!head)
		return ;
	empty_tree(head->first_cond);
	empty_tree(head->sec_cond);
	empty_tree(head->next);
//	printf("node is of type %d\n", head->type);
//	if (!head->type)
//		printf("content:\n'%s'\n", head->content);
//	if (!head->type && head->content && head->content[0])
//		free(head->content);
	free(head);
}

void	look_for_heredocs(t_cond *head, t_data *info)
{
	if (!head || info->hd_error)
		return ;
	look_for_heredocs(head->first_cond, info);
	if (!head->type)
	{
	//	printf("here i am!!\n");
	//	printf("%d\n", info->hd);
		info->hd_error = find_hd(head, head->content, info);
		info->hd += 1;
		head->hd_n = info->hd;
	}
	look_for_heredocs(head->sec_cond, info);
	look_for_heredocs(head->next, info);
}

void	exec_node(t_cond *current, t_data *info)
{
//	printf("executing\n");
	current->ret = work_pipe(info, current->content);
	info->cmd_n += 1;
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
	if (!str)
		exit(write(2, "memory errawr🦖\n", 15));
//	printf("str is '%s'\n", str);
	while (str[i] && (str[i] == '(' || str[i] == ')'))
		i++;
	if (!str[i])
		head = NULL;
	else
		head = create_level(str, NULL, NULL, 1);
	free(str);
//	print_tree(head, 1, 1, 1);	
//	free(str);
	info->hd = 0;
	info->hd_n = 0;
	info->hd_error = 0;
	look_for_heredocs(head, info);
	if (info->hd_error)
		info->trinary_tree = NULL;
	else
		info->trinary_tree = head;
	return (1);
}
