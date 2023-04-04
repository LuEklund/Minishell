/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:27:04 by nlonka            #+#    #+#             */
/*   Updated: 2023/04/01 19:27:06 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parenthesee(t_error *he, char *str)
{
	if (he->par < 0)
		return (1);
	if (!he->i || he->sq + he->q != 0)
		return (0);
	if ((he->amper + he->or + he->and == 0 && \
	str[he->i] == '(' && str[he->i - 1] != '(') || (str[he->i] == '|' \
	&& str[he->i + 1] != '|' && str[he->i - 1] == ')'))
		return (1);
	if (he->pipe && (str[he->i] == ')' || str[he->i] == '('))
		return (1);
	if (str[he->i - 1] == ')' && str[he->i] != ')' && str[he->i] != '|' \
	&& str[he->i] != '&' && str[he->i] && str[he->i] != ' ')
	{
		get_tokenized(he, str, 3);
		if (!(he->pipe || he->or || he->and || he->amper))
		{
			reset_token_val(he, str, 1);
			he->special = 1;
			return (1);
		}
		reset_token_val(he, str, 1);
	}
	if (str[he->i] == ')' && str[he->i - 1] == '(')
		return (1);
	return (0);
}

int	redi_syntax(t_error *he, char *str)
{
	if (!he->out_t && !he->out_o && !he->in_t && !he->in_o)
		return (1);
	if (he->i == 1 && ((str[he->i - 1] == '>' && str[he->i] == '>') || \
			(str[he->i - 1] == '<' && str[he->i] == '<')))
		return (0);
	if (he->i > 1 && str[he->i - 1] == '>' && \
	str[he->i] == '>' && str[he->i - 2] == '>')
		return (1);
	if (he->i > 1 && str[he->i - 1] == '<' && \
	str[he->i] == '<' && str[he->i - 2] == '<')
		return (1);
	if (he->i && str[he->i] == '<' && str[he->i - 1] == '<')
		return (0);
	if (he->i && str[he->i] == '>' && str[he->i - 1] == '>')
		return (0);
	if (he->i && (str[he->i - 1] == '|' || str[he->i - 1] == '&'))
		return (0);
	if (he->i > 1 && (str[he->i - 2] == '|' || str[he->i - 2] == '&'))
		return (0);
	return (1);
}
