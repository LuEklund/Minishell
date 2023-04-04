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

void	reset_token_val(t_error *he, char *str, int var)
{
	he->special = 0;
	if (var == 3 || var == 5)
		he->plus_yes = 0;
	if (var == 2)
		he->i += 1;
	if (var && str[he->i] == ' ')
		return ;
	he->token = 0;
	if (var != 3 && var != 5)
		he->plus_yes = 1;
	he->or = 0;
	he->pipe = 0;
	he->and = 0;
	he->amper = 0;
	he->out_o = 0;
	he->in_o = 0;
	he->out_t = 0;
	he->in_t = 0;
}

void	par_plus(t_error *he, char *str, int var)
{
	if (he->sq + he->q != 0 || var == 3)
		return ;
	else if (str && str[he->i] == '(')
		he->par += 1;
	else if (str && str[he->i] == ')')
		he->par -= 1;
	else
		return ;
}

void	continue_tokenization(t_error *he, char *str)
{
	if (str[he->i] == '&')
		he->amper = 1;
	else if (str[he->i] == '>' && str[he->i + 1] == '>')
		he->out_t = 1;
	else if (str[he->i] == '>')
		he->out_o = 1;
	else if (str[he->i] == '<' && str[he->i + 1] == '<')
		he->in_t = 1;
	else if (str[he->i] == '<')
		he->in_o = 1;
	else
		he->token = 0;
}

void	get_tokenized(t_error *he, char *str, int var)
{
	reset_token_val(he, str, var);
	he->token = 1;
	if (he->sq + he->q != 0 || !str)
		he->token = 0;
	else if (var && str[he->i] == ' ' && (he->pipe \
	|| he->amper || he->or || he->and))
		reset_token_val(he, str, 2 + var);
	else if (str[he->i] == '|' && str[he->i + 1] == '|')
		he->or = 1;
	else if (str[he->i] == '|')
		he->pipe = 1;
	else if (str[he->i] == '&' && str[he->i + 1] == '&')
		he->and = 1;
	else
		continue_tokenization(he, str);
	par_plus(he, str, var);
}
