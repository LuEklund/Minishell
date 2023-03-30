/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:04:54 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/16 15:49:28 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_list(char *str, t_args *current, int i)
{
	t_args	*tmp;

	while (current->next && current->i != i)
		current = current->next;
	if (!current->next)
	{
		current->next = new_arg(str, i);
		return ;
	}
	while (current->next && current->next->i == i)
		current = current->next;
	if (!current->next)
	{
		current->next = new_arg(str, i);
		return ;
	}
	tmp = current->next;
	current->next = new_arg(str, i);
	current->next->next = tmp;
}

void	remove_from_list(t_data *info, char *str, t_args *current)
{
	t_args	*tmp;

	if (!ft_strncmp(str, current->arg, ft_strlen(current->arg) + 1))
	{
		tmp = current->next;
		free(current->arg);
		free(current);
		info->args_list = tmp;
		return ;
	}
	while (current->next && \
	ft_strncmp(str, current->next->arg, ft_strlen(current->arg) + 1))
		current = current->next;
	if (!current->next)
		return ;
	tmp = current->next->next;
	free(current->next->arg);
	free(current->next);
	current->next = tmp;
}

t_args	*new_arg(char *str, int i)
{
	t_args	*new;

	new = malloc(sizeof(t_args));
	if (!new)
		exit(write(2, "memory error\n", 13));
	new->next = NULL;
	new->i = i;
	new->arg = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new->arg)
		exit(write(2, "memory error\n", 13));
	ft_strlcpy(new->arg, str, ft_strlen(str) + 1);
	return (new);
}

t_args	*copy_ar_to_list(char **ar)
{
	t_args	*head;
	t_args	*current;
	int		i;

	i = 1;
	if (!ar[0])
		return (NULL);
	head = new_arg(ar[0], 0);
	current = head;
	while (ar[i])
	{
		current->next = new_arg(ar[i], i);
		current = current->next;
		i++;
	}
	return (head);
}

char	**copy_list_to_ar(t_args *current)
{
	char	**ans;
	t_args	*safe;
	size_t	i;

	safe = current;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	ans = malloc(sizeof(char *) * (i + 1));
	ans[i] = 0;
	current = safe;
	i = 0;
	while (current)
	{
		ans[i] = malloc(sizeof(char) * (ft_strlen(current->arg) + 1));
		if (!ans[i])
			exit(write(2, "memory error\n", 13));
		ft_strlcpy(ans[i], current->arg, ft_strlen(current->arg) + 1);
		current = current->next;
		i++;
	}
	return (ans);
}
