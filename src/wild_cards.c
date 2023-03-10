/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:09:46 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/10 20:28:03 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_args(t_data *info, int i)
{
	char	**files;

	(void)info;
	(void)i;
	files = ft_ls();
	print_ar(files);
	free_ar(files);
}

void	process_wild_cards(t_data *info)
{
	t_wild	*current;
	int		safe;

	current = info->wild_list;
	safe = -1;
	while (current)
	{
		if (safe == -1 || safe != current->i)
		{
			add_args(info, current->i);
			safe = current->i;
		}
		current = current->next;
	}
}

void	new_wild(t_data *info, int i)
{
	t_wild	*new;
	t_wild	*current;

	new = malloc(sizeof(t_wild));
	if (!new)
		exit(write(2, "memory error\n", 13));
	new->next = NULL;
	new->i = i;
	if (!info->wild_list)
		info->wild_list = new;
	else
	{
		current = info->wild_list;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	wild_card_check(t_data *info)
{
	int		i;
	int		i2;
	int		check;

	i = 1;
	i2 = 0;
	check = 1;
	info->wild_list = NULL;
	while (info->args[i])
	{
		while (info->args[i][i2])
		{
			if (info->args[i][i2] == '*')
			{
				new_wild(info, i);
				check = 0;
			}
			i2++;
		}
		i++;
		i2 = 0;
	}
	if (check)
		return ;
	process_wild_cards(info);
	empty_wild_list(info);
}
