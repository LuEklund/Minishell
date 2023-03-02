/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:07:38 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/02 18:15:32 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	quote_check(char const *str, int i, int *q, int *sq)
{
	if (*q == 1 && str[i] == '\"')
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

static int	string_amount(char const *str, char c, int q, int sq)
{
	int	ans;
	int	i;

	ans = 1;
	i = q + sq;
	while (str[i] == c && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		ans = -1;
	while (str[i] != '\0')
	{
		while (str[i] == c)
		{
			if (str[i + 1] != '\0' && str[i + 1] != c && sq + q == 0)
				ans++;
			i = quote_check(str, i, &q, &sq);
		}
		if (str[i] != '\0')
			i = quote_check(str, i, &q, &sq);
	}
	if (ans == 0 && str[0] != '\0')
		return (1);
	if (str[0] == '\0' || ans < 0)
		ans = 0;
	return (ans);
}

static char	**ansllocator(char **ans, char const *str, t_data *info, t_split help)
{
	while (help.i2 < help.h)
	{
		if (str[help.i3] == '\'')
			help.sq = help.sq + 1 % 2;
		if (str[help.i3] == '\"')
			help.q = help.q + 1 % 2;
		while (str[help.i3] != '\0' && str[help.i3] == help.c && help.q + help.sq == 0)
			help.i3 += 1;
		while (str[help.i3] != '\0' && (str[help.i3] != help.c || help.q + help.sq != 0))
		{
			if (str[help.i3] == '$' && help.sq == 0 && str[help.i3 + 1])
			{
				if (expand_envs(str, info, &help))
					continue ;
			}
			if (help.c == '|' || quote_see(str, help))
				help.i += 1;
			help.i3 = quote_check(str, help.i3, &help.q, &help.sq);
		}
		help.l = help.i - help.h2;
		help.h2 = help.h2 + help.l;
		ans[help.i2] = (char *) malloc (sizeof(char) * (help.l + 1));
		help.i2 += 1;
	}
	return (ans);
}

static char	**string_separator_7000(char **ans, char const *str, t_data *info, t_split help)
{
	(void)info;
	while (help.i2 < help.h)
	{
		if (str[help.i3] == '\'')
			help.sq = help.sq + 1 % 2;
		if (str[help.i3] == '\"')
			help.q = help.q + 1 % 2;
		while (str[help.i3] != '\0' && str[help.i3] == help.c && help.q + help.sq == 0)
			help.i3 += 1;
		while (str[help.i3] != '\0' && (str[help.i3] != help.c || help.q + help.sq != 0))
		{
			if (quote_see(str, help) || help.c == '|')
				ans[help.i2][help.i] = str[help.i3];
			if (quote_see(str, help) || help.c == '|')
				help.i += 1;
			help.i3 = quote_check(str, help.i3, &help.q, &help.sq);
		}
		ans[help.i2][help.i] = '\0';
		help.i2 += 1;
		help.i = 0;
	}
	return (ans);
}

static char	**check_malloc(char **ans, int h)
{
	int	i2;

	i2 = 0;
	while (i2 < h)
	{
		if (ans[i2] == NULL)
		{
			i2 = 0;
			while (i2 < h)
			{
				free(ans[i2]);
				i2++;
			}
			free(ans);
			return (NULL);
		}
		i2++;
	}
	return (ans);
}

void	init_help(t_data *info, int h, char c)
{
	t_split	*help;

	help = info->split;
	help->h = h;
	help->i = 0;
	help->i2 = 0;
	help->i3 = 0;
	help->l = 0;
	help->h2 = 0;
	help->q = 0;
	help->sq = 0;
	help->c = c;
}

char	**parse_split(char const *str, char c, t_data *info)
{
	int		h;
	char	**ans;
	t_split	help;

	info->split = &help;
	if (str == NULL)
		return (NULL);
	if (str && str[0] == '\'')
		h = string_amount(str, c, 0, 1);
	else if (str && str[0] == '\"')
		h = string_amount(str, c, 1, 0);
	else
		h = string_amount(str, c, 0, 0);
	ans = (char **) malloc(sizeof(char *) * (h + 1));
	if (ans == NULL)
		return (NULL);
	ans[h] = 0;
	init_help(info, h, c);
	ans = ansllocator(ans, str, info, *(info->split));
	ans = check_malloc(ans, h);
	if (ans == NULL)
		return (NULL);
	ans = string_separator_7000(ans, str, info, *(info->split));
	return (ans);
}
