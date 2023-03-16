/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trinary_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 20:04:34 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/16 21:39:04 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cond	*new_tokenode(char *str, t_error help, t_cond *head, t_cond *first)
{
	t_cond	*new;

	new = malloc(sizeof(t_cond));
	if (!new)
		exit(write(2, "memory error\n", 13));
	if (help.or)
		new->type = 1;
	else
		new->type = 2;
	new->ret = 0;
	new->first_cond = first;
	new->second_cond = create_tree(str, head, new);
	new->next = NULL;
}

t_cond	*new_content_node(char *str, t_cond *first)
{
	t_cond	*new;

	if (!str)
		exit(write(2, "memory error\n", 13));
	new = malloc(sizeof(t_cond));
	if (!new)
		exit(write(2, "memory error\n", 13));
	new->content = str;
	new->first_cond = first;
	new->second_cond = sec;
	new->next = NULL;
	new->ret = 0;
}

t_cond	*new_content_insert(char *str, t_cond *first)
{
	first = new_content_node(str, NULL, NULL);
	return (first);
}

t_cond	*create_tree(char *str, t_cond *head, t_cond *first)
{
	size_t	len;
	t_error	help;

	len = 0;
	while (str && str[len])
	{
		get_tokenized(&help, str, 0);
		if (help.and || help.or)
			break ;
		len++;
	}
	if (!str || (!str[len] && !len))
		return (head);
	if (!len)
	{
		first->next = new_tokenode(str + 2, help, first);
		return ;
	}
	else if (head)
		first->next = new_content_node(ft_substr((char const *)str, 0, len), first);
	else
		head = new_content_insert(ft_substr((char const *)str, 0, len), first);
}
