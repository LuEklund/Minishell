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
	if (!(*cmd) && str[i] > 32 && str[i] < 127 && str[i] != '|' && str[i] != '>' \
			&& str[i] != '<' && str[i] != '&' && str[i] != '(' && str[i] != ')')
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

void	reset_token_val(t_error *help)
{
	help->or = 0;
	help->pipe = 0;
	help->and = 0;
	help->amper = 0;
	help->out_o = 0;
	help->in_o = 0;
	help->out_t = 0;
	help->in_t = 0;
}

void	get_tokenized(t_error *help, char *str, int var)
{
	reset_token_val(help);
	help->token = 1;
	if (help->sq + help->q != 0)
		help->token = 0;
	else if (str && str[help->i] == '|' && str[help->i + 1] == '|')
		help->or = 1;
	else if (str && str[help->i] == '|')
		help->pipe = 1;
	else if (str && str[help->i] == '&' && str[help->i + 1] == '&')
		help->and = 1;
	else if (str && str[help->i] == '&')
		help->amper = 1;
	else if (str && str[help->i] == '>' && str[help->i + 1] == '>')
		help->out_t = 1;
	else if (str && str[help->i] == '>')
		help->out_o = 1;
	else if (str && str[help->i] == '<' && str[help->i + 1] == '<')
		help->in_t = 1;
	else if (str && str[help->i] == '<')
		help->in_o = 1;
	else
		help->token = 0;
	if (str && str[help->i] == '(' && !var)
		help->par += 1;
	else if (str && str[help->i] == ')')
		help->par -= 1;
}

int	parenthesee(t_error *help, char *str)
{
	if (!help->i)
		return (0);
	if (str[help->i] != '(' && str[help->i] != ')')
		return (0);
	if (help->par < 0)
		return (1);
	if (help->amper + help->pipe + help->or + help->and == 0 && \
		str[help->i] == '(' && str[help->i - 1] != '(')
		return (1);
	return (0);	
}

int	redi_syntax(t_error *help, char *str)
{
	if (help->out_t + help->out_o + help->in_t + help->in_o == 0)
		return (1);
	if (help->i == 1 && ((str[help->i - 1] == '>' && str[help->i] == '>') || \
			(str[help->i - 1] == '<' && str[help->i] == '<')))
		return (0);
	if (str[help->i - 1] == '>' && str[help->i] == '>' && str[help->i - 2] == '>')
		return (1);
	if (str[help->i - 1] == '<' && str[help->i] == '<' && str[help->i - 2] == '<')
		return (1);
	if (str[help->i] == '<' && str[help->i - 1] == '<')
		return (0);
	if (str[help->i] == '>' && str[help->i - 1] == '>')
		return (0);
	printf("hi from i %zu\n", help->i);
	if (str[help->i - 1] == '|' || str[help->i - 1] == '&')
		return (0);
//	printf("hi from i %zu\n", help->i);
	return (1);
}
int	error_parser(t_data *info)
{
	t_error	*help;
	int		qts[2];

	help = malloc(sizeof(t_error));
	qts[0] = 0;
	qts[1] = 0;
	help->i = 0;
	help->q = 0;
	help->sq = 0;
	help->par = 0;
	info->error = help;
	info->buf = white_space_cleanse(info->buf, NULL, qts, 0);
	if (!info->buf)
		return (1);
//	printf("buf is '%s'\n", info->buf);
	get_tokenized(help, info->buf, 1);
	if (help->pipe + help->or + help->amper + help->and != 0 || help->par < 0)
		return (1);
	while (info->buf[help->i])
	{
		help->i = quote_check((char const *)info->buf, help->i, &help->q, &help->sq) - 1;
		if (help->i && help->token && help->q + help->sq == 0)
		{
			get_tokenized(help, info->buf, 1);
			if (help->token && redi_syntax(help, info->buf))
				return (1);
		}
//		printf("parr is %d at %c%zu\n", help->par, info->buf[help->i], help->i);
		get_tokenized(help, info->buf, 0);
		if (help->and || help->or)
			help->i += 1;
		help->i = quote_check((char const *)info->buf, help->i, &help->q, &help->sq);
		if (parenthesee(help, info->buf))
			return (1);
	}
//	printf("token is %d parr is %d\n", help->token, help->par);
	return (help->token + help->par);
}
