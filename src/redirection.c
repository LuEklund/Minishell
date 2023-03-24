/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:21:18 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/24 11:21:35 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redi	*new_node(int type, int i, int i2, int red_n)
{
	t_redi	*new;

	new = malloc(sizeof(t_redi));
	if (!new)
		exit(write(2, "memory errawr🦖\n", 15));
	new->next = NULL;
	new->type = type;
	new->pipe_n = i;
	new->red_n = red_n;
	new->i = i2;
	new->cmd_n = 0;
	return (new);
}

void	new_redi_node(t_data *info, int type, int i, int *i2)
{
	t_redi	*current;
	int		check;

	check = 0;
	if (type % 2 == 0)
		*i2 += 1;
	if (!info->redi_list)
		info->redi_list = new_node(type, i, *i2, info->red_n);
	else
		check = 1;
	current = info->redi_list;
	while (current->next)
		current = current->next;
	if (check)
	{
		current->next = new_node(type, i, *i2, info->red_n);
		current = current->next;
	}
	info->red_n += 1;
}

void	connect_with_hd_list(t_data *info, size_t i, int *i2)
{
	t_redi	*current;
	t_redi	*new;
	t_redi	*hd;

	*i2 += 1;
	hd = info->hd_list;
	while (hd && (hd->cmd_n != info->cmd_n || hd->pipe_n != i || hd->used))
		hd = hd->next;
	if (!hd)
		exit(write(2, "is fucked\n", 10));
	hd->used = 1;
	new = copy_hd_node(hd, info->red_n);
	current = info->redi_list;
	if (!current)
		current = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	info->red_n += 1;
}

void	start_quotes(t_data *info, int i, int *i2)
{
	if (info->cmds[i][0] == '\'')
		info->sq = 1;
	else if (info->cmds[i][0] == '\"')
		info->q = 1;
	else
	{
		info->sq = 0;
		info->q = 0;
		return ;
	}
	*i2 += 1;
}

//////
//////

void	print_list(t_whelp *current)
{
	int	i = 1;

	////remove this
	while (current)
	{
		printf("%d", i);
		if (i % 10 == 1 && i % 100 != 11)
			printf(":st");
		else if (i % 10 == 2 && i % 100 != 12)
			printf(":nd");
		else if (i % 10 == 3 && i % 100 != 13)
			printf(":rd");
		else
			printf(":th");
	//	printf(" node is of type %d, in pipe %zu spot %zu\n", current->type, current->pipe_n, current->red_n);
		printf(" node has n %d h %d and validness of %d\n", current->n, current->h, current->valid);
		current = current->next;
		i++;
	}

}

//////
//////
int	redirection_parser(t_data *info, int i, int i2)
{
	while (info->cmds[i])
	{
		start_quotes(info, i, &i2);
		info->red_n = 0;
		while (info->cmds[i][i2])
		{
			if (info->q + info->sq != 0)
				;
			else if (info->cmds[i][i2] == '<' && info->cmds[i][i2 + 1] == '<')
				connect_with_hd_list(info, i, &i2);
			else if (info->cmds[i][i2] == '<')
				new_redi_node(info, 1, i, &i2);
			else if (info->cmds[i][i2] == '>' && info->cmds[i][i2 + 1] == '>')
				new_redi_node(info, -2, i, &i2);
			else if (info->cmds[i][i2] == '>')
				new_redi_node(info, -1, i, &i2);
			i2 = quote_check((char const *)info->cmds[i], i2, &info->q, &info->sq);
		}
		info->all_red_n += info->red_n;
		i2 = 0;
		i++;
	}
	return (open_files(info));
}
