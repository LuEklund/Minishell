/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:09:46 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/16 19:35:42 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	does_it_match(char *file, char *wild, int i, int i2)
{
	int	check = 0;
	while (wild[i2])
	{
		while (wild[i2] && wild[i2] == '*')
			i2++;
		if (!wild[i2])
			return (1);
		if (!i2 && wild[0] != file[i])
			return (0);
		while (file[i] && wild[i2] != file[i])
			i++;
		if (!file[i])
			return (0);
		while (file[i] && wild[i2] && wild[i2] == file[i])
		{
			i++;
			i2++;
		}
		if (!i)
			return (0);
		if (!wild[i2] && !file[i])
			return (1);
		if (wild[i2] != '*' && wild[i2] != file[i])
			i2 = 0;
		check++;
		if (check > 500)
			exit(1);
	}
	if (!file[i])
		return (1);
	return (0);
}

void	add_args(t_data *info, char **files, int i)
{
	int		i2;
	int		check;
	int		check2;

	i2 = 0;
	check2 = 0;
	while (files[i2])
	{
		check = does_it_match(files[i2], info->args[i], 0, 0);
		if (check)
			add_to_list(files[i2], info->args_list, i);
		check2 += check;
		i2++;
	}
	if (check2)
		remove_from_list(info, info->args[i], info->args_list);
}

void	process_wild_cards(t_data *info)
{
	char	**files;
	t_wild	*current;
	int		safe;

	current = info->wild_list;
	safe = -1;
	files = ft_ls();
	while (current)
	{
		if (safe == -1 || safe != current->i)
		{
			add_args(info, files, current->i);
			safe = current->i;
		}
		current = current->next;
	}
	free_ar(info->args);
	free_ar(files);
	info->args = copy_list_to_ar(info->args_list);
	empty_wild_list(info);
	empty_args_list(info);
	empty_whelp_list(info);
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
	t_whelp	*current;

	i = 1;
	i2 = 0;
	current = info->wmark_list;
//	print_list(current);
	info->wild_list = NULL;
	info->args_list = copy_ar_to_list(info->args);
	while (info->args[i])
	{
		while (info->args[i][i2])
		{
			if (info->args[i][i2] == '*')
			{
				if (current->valid)
					new_wild(info, i);
				current = current->next;
			}
			i2++;
		}
		i++;
		i2 = 0;
	}
	if (!info->wild_list)
		return (empty_args_list(info), empty_whelp_list(info));
	process_wild_cards(info);
}
