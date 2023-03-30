/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:34:32 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/27 17:38:35 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_check(char const *str, int i, int *cmd, int *qts)
{
	int	hi;

	hi = i;
	hi = quote_check(str, hi, &qts[0], &qts[1]) - 1;
	if (!(*cmd) && str[i] > 32 && str[i] < 127 && str[i] != '|' && str[i] != \
	'>' && str[i] != '<' && str[i] != '&' && str[i] != '(' && str[i] != ')')
		*cmd = 1;
	else if (*cmd && qts[0] + qts[1])
		return (hi + 1);
	else if (*cmd)
	{
		while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
			i++;
		if (!str[i] || str[i] == '|' || str[i] == '>' || str[i] == '<' || \
			str[i] == '&' || str[i] == '(' || str[i] == ')')
			*cmd = 0;
	}
	return (hi + 1);
}

char	*white_space_cleanse(char *str, char *ans, int *qts, int cmd)
{
	size_t	i;
	size_t	i2;

	print_check((char const *)str, 0, &cmd, qts);
	i = qts[0] + qts[1];
	if (ans)
		ans[0] = str[0];
	i2 = i;
	while (str[i])
	{
		if ((str[i] > 32 && str[i] < 127) || (cmd && (str[i + 1] > 32 && \
			str[i + 1] < 127)) || qts[0] + qts[1])
		{
			if (ans)
				ans[i2] = str[i];
			i2++;
		}
		i = print_check((char const *)str, i, &cmd, qts);
	}
	if (!i2)
		return (free(str), NULL);
	if (!ans)
	{
		ans = malloc(sizeof(char) * (i2 + 1));
		if (!ans)
			return (write(2, "memory error\n", 13), free(str), NULL);
		ans[i2] = '\0';
		return (white_space_cleanse(str, ans, qts, 0));
	}
	free(str);
	return (ans);
}

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
	if (str && str[he->i] == '(' && !var)
		he->par += 1;
	else if (str && str[he->i] == ')')
		he->par -= 1;
}

int	parenthesee(t_error *he, char *str)
{
	if (he->par < 0)
		return (1);
	if (!he->i)
		return (0);
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

int	error_parser(t_data *info)
{
	t_error	*he;
	int		qts[2];

	he = malloc(sizeof(t_error));
	qts[0] = 0;
	qts[1] = 0;
	he->i = 0;
	he->q = 0;
	he->sq = 0;
	he->par = 0;
	info->error = he;
	info->buf = white_space_cleanse(info->buf, NULL, qts, 0);
	if (!info->buf)
		return (1);
	get_tokenized(he, info->buf, 1);
	if (he->pipe + he->or + he->amper + he->and != 0 || he->par < 0)
		return (1);
	while (info->buf[he->i])
	{
		he->i = quote_check((char const *)info->buf, \
		he->i, &he->q, &he->sq) - 1;
		if (he->i && he->token && he->q + he->sq == 0)
		{
			get_tokenized(he, info->buf, 1);
			if (he->token && redi_syntax(he, info->buf))
				return (1);
		}
		get_tokenized(he, info->buf, 0);
		if (he->and || he->or)
			he->i += 1;
		he->i = quote_check((char const *)info->buf, \
		he->i, &he->q, &he->sq);
		if (parenthesee(he, info->buf))
			return (1);
	}
	return (he->token + he->par);
}
