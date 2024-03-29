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

char	*the_anser(char *str, int i2)
{
	char	*ans;

	ans = malloc(sizeof(char) * (i2 + 1));
	if (!ans)
	{
		free(str);
		exit(write(2, "memory errawr🦖\n", 15));
	}
	ans[i2] = '\0';
	return (ans);
}

char	*white_space_cleanse(char *str, char *ans, int *qts, int cmd)
{
	size_t	i[2];

	i[0] = 0;
	i[1] = 0;
	while (str[i[0]])
	{
		if ((str[i[0]] > 32 && str[i[0]] < 127) || (cmd \
		&& (str[i[0] + 1] > 32 && str[i[0] + 1] < 127)) || qts[0] + qts[1] \
		|| (str[i[0]] == ' ' && (str[i[0] - 1] == '|' || str[i[0] - 1] == '&')))
		{
			if (ans)
				ans[i[1]] = str[i[0]];
			i[1] += 1;
		}
		i[0] = print_check((char const *)str, i[0], &cmd, qts);
	}
	if (!i[1])
		return (free(str), NULL);
	if (!ans)
	{
		ans = the_anser(str, i[1]);
		return (white_space_cleanse(str, ans, qts, 0));
	}
	return (free(str), ans);
}

int	init_error(t_error *he, int *qts, t_data *info)
{
	qts[0] = 0;
	qts[1] = 0;
	he->space = 0;
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
	he->i = quote_check((char const *)info->buf, he->i, &he->q, &he->sq);
	return (0);
}

int	error_parser(t_data *info)
{
	t_error	*he;
	int		qts[2];

	he = malloc(sizeof(t_error));
	if (init_error(he, qts, info))
		return (1);
	while (info->buf[he->i])
	{
		if (he->i && he->token && he->q + he->sq == 0)
		{
			get_tokenized(he, info->buf, 3);
			if (he->token && redi_syntax(he, info->buf) && \
			info->buf[he->i] != ' ')
				return (1);
		}
		get_tokenized(he, info->buf, 1);
		if ((he->and || he->or) && he->plus_yes)
			he->i += 1;
		he->i = quote_check((char const *)info->buf, \
		he->i, &he->q, &he->sq);
		if (parenthesee(he, info->buf) || he->amper)
			return (1);
	}
	return (he->token + he->par);
}
