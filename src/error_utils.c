/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:08:00 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/31 10:08:02 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_token_val(t_error *he)
{
	he->or = 0;
	he->pipe = 0;
	he->and = 0;
	he->amper = 0;
	he->out_o = 0;
	he->in_o = 0;
	he->out_t = 0;
	he->in_t = 0;
	he->special = 0;
}

void	par_plus(t_error *he, char *str, int var)
{
	if (he->sq + he->q != 0)
		;
	else if (str && str[he->i] == '(' && !var)
		he->par += 1;
	else if (str && str[he->i] == ')')
		he->par -= 1;
}

void	get_tokenized(t_error *he, char *str, int var)
{
	reset_token_val(he);
	he->token = 1;
	if (he->sq + he->q != 0)
		he->token = 0;
	else if (str && str[he->i] == '|' && str[he->i + 1] == '|')
		he->or = 1;
	else if (str && str[he->i] == '|')
		he->pipe = 1;
	else if (str && str[he->i] == '&' && str[he->i + 1] == '&')
		he->and = 1;
	else if (str && str[he->i] == '&')
		he->amper = 1;
	else if (str && str[he->i] == '>' && str[he->i + 1] == '>')
		he->out_t = 1;
	else if (str && str[he->i] == '>')
		he->out_o = 1;
	else if (str && str[he->i] == '<' && str[he->i + 1] == '<')
		he->in_t = 1;
	else if (str && str[he->i] == '<')
		he->in_o = 1;
	else
		he->token = 0;
	par_plus(he, str, var);
}

int	parenthesee(t_error *he, char *str)
{
	if (he->par < 0)
		return (1);
	if (!he->i || he->sq + he->q != 0)
		return (0);
	if (str[he->i - 1] == ')' && str[he->i] != ')' && he->amper + \
	he->or + he->and == 0)
	{
		reset_token_val(he);
		he->special = 1;
		return (1);
	}
	if (str[he->i] != '(' && str[he->i] != ')')
		return (0);
	if (str[he->i] == ')' && str[he->i - 1] == '(')
		return (1);
	if (he->amper + he->or + he->and == 0 && \
		str[he->i] == '(' && str[he->i - 1] != '(')
		return (1);
	if (he->pipe)
		return (1);
	return (0);
}

int	redi_syntax(t_error *he, char *str)
{
	if (he->out_t + he->out_o + he->in_t + he->in_o == 0)
		return (1);
	if (he->i == 1 && ((str[he->i - 1] == '>' && str[he->i] == '>') || \
			(str[he->i - 1] == '<' && str[he->i] == '<')))
		return (0);
	if (str[he->i - 1] == '>' && str[he->i] == '>' && str[he->i - 2] == '>')
		return (1);
	if (str[he->i - 1] == '<' && str[he->i] == '<' && str[he->i - 2] == '<')
		return (1);
	if (str[he->i] == '<' && str[he->i - 1] == '<')
		return (0);
	if (str[he->i] == '>' && str[he->i - 1] == '>')
		return (0);
	if (str[he->i - 1] == '|' || str[he->i - 1] == '&')
		return (0);
	return (1);
}
