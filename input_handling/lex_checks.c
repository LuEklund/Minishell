/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:05:06 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/30 19:05:08 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_check(char const *str, int i, int *q, int *sq)
{
	if (!str)
		;
	else if (*q == 1 && str[i] == '\"')
		*q = 0;
	else if (*sq == 1 && str[i] == '\'')
		*sq = 0;
	else if (*q == 0 && *sq == 0 && str[i] == '\"')
		*q = 1;
	else if (*sq == 0 && *q == 0 && str[i] == '\'')
		*sq = 1;
	i++;
	return (i);
}

int	quote_see(char const *str, t_split help)
{
	if (help.sq == 0 && str[help.i3] == '\"')
		return (0);
	if (help.q == 0 && str[help.i3] == '\'')
		return (0);
	if (help.q == 1 && str[help.i3] == '\"')
		return (0);
	if (help.sq == 1 && str[help.i3] == '\'')
		return (0);
	return (1);
}

int	expand_check(char const *str, t_split *help)
{
	help->expand_type = 5;
	if (str[help->i3] == '$' && help->sq == 0)
	{
		if (str[help->i3 + 1] == '?')
			help->expand_type = 1;
		else
			help->expand_type = 0;
	}
	else if (str[help->i3] == '>' && help->sq + help->q == 0 && help->c == ' ')
	{
		if (str[help->i3 + 1] == '>')
			help->expand_type = 3;
		else
			help->expand_type = 2;
	}
	else if (str[help->i3] == '<' && help->sq + help->q == 0 && help->c == ' ')
	{
		if (str[help->i3 + 1] == '<')
			help->expand_type = 3;
		else
			help->expand_type = 2;
	}
	else
		return (0);
	return (1);
}
