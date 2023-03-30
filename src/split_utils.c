/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:41:51 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/29 17:41:53 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	red_c(char const *str, t_split *help, int i)
{
	int	safe;

	safe = i;
	if (help->c != ' ')
		return (quote_check(str, i, &help->q, &help->sq));
	help->i3 = i;
	expand_check(str, help);
	if (help->expand_type != 3 && help->expand_type != 2)
		return (quote_check(str, i, &help->q, &help->sq));
	if (!redir_input_parser(str, help, 0))
		return (quote_check(str, i, &help->q, &help->sq));
	if (!safe)
		help->i3 += 1;
	return (help->i3);
}

void	wild_marker(char const *str, t_split help, t_data *info)
{
	t_whelp	*current;
	t_whelp	*new;

	if (str[help.i3] != '*' || help.c != ' ')
		return ;
	new = malloc(sizeof(t_whelp));
	if (!new)
		exit(write(2, "memory error\n", 13));
	new->next = NULL;
	new->h = help.i2;
	if (help.sq + help.q == 0)
		new->valid = 1;
	else
		new->valid = 0;
	if (!info->wmark_list)
	{
		new->n = 1;
		info->wmark_list = new;
		return ;
	}
	current = info->wmark_list;
	while (current->next)
		current = current->next;
	current->next = new;
	new->n = current->n + 1;
}

void	init_help(t_data *info, t_split *help, char c, char const *str)
{
	help->sq = 0;
	help->q = 0;
	if (str && str[0] == '\'')
		help->sq = 1;
	if (str && str[0] == '\"')
		help->q = 1;
	help->i = 0;
	help->i2 = 0;
	help->i3 = 0;
	help->l = 0;
	help->h2 = 0;
	help->c = c;
	help->check = 0;
	info->split = help;
}
