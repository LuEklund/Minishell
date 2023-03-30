/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:07:38 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/24 12:33:42 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	string_amount(char const *str, t_split he, int ans, int i)
{
	while (str[i] == he.c && str[i] != '\0' && he.q + he.sq == 0)
		i++;
	if (str[i] == '\0')
		ans = -1;
	while (str[i] != '\0')
	{
		if (str[i] != '\0')
			i = red_c(str, &he, i);
		while (str[i] == he.c)
		{
			if (str[i + 1] != '\0' && str[i + 1] != he.c && !(he.c == ' ' && \
			(str[i + 1] == '>' || str[i + 1] == '<')) && he.sq + he.q == 0)
				ans++;
			i = quote_check(str, i, &he.q, &he.sq);
		}
	}
	if (ans == 0 && str[0] != '\0')
		return (1);
	if (str[0] == '\0' || ans < 0)
		ans = 0;
	return (ans);
}

static char	**ansllocator(char **ans, char const *str, t_data *info, t_split he)
{
	while (he.i2 < he.h)
	{
		if (str[he.i3] == '\'')
			he.sq = he.sq + 1 % 2;
		if (str[he.i3] == '\"')
			he.q = he.q + 1 % 2;
		while (str[he.i3] != '\0' && str[he.i3] == he.c && he.q + he.sq == 0)
			he.i3 += 1;
		while (str[he.i3] != '\0' && (str[he.i3] != he.c || he.q + he.sq != 0))
		{
			if (str[he.i3 + 1] && expand_check(str, &he) \
			&& expand_envs(str, info, &he, ans))
				continue ;
			wild_marker(str, he, info);
			if (he.c != ' ' || quote_see(str, he))
				he.i += 1;
			he.i3 = quote_check(str, he.i3, &he.q, &he.sq);
		}
		he.l = he.i - he.h2;
		he.h2 = he.h2 + he.l;
		ans[he.i2] = (char *) malloc (sizeof(char) * (he.l + 1));
		he.i2 += 1;
	}
	return (ans);
}

static char	**string_sep(char **ans, char const *str, t_data *info, t_split he)
{
	he.check = 1;
	while (he.i2 < he.h)
	{
		if (str[he.i3] == '\'')
			he.sq = he.sq + 1 % 2;
		if (str[he.i3] == '\"')
			he.q = he.q + 1 % 2;
		while (str[he.i3] != '\0' && str[he.i3] == he.c && he.q + he.sq == 0)
			he.i3 += 1;
		while (str[he.i3] != '\0' && (str[he.i3] != he.c || he.q + he.sq != 0))
		{
			if (str[he.i3 + 1] && expand_check(str, &he) \
			&& expand_envs(str, info, &he, ans))
				continue ;
			if (he.c != ' ' || quote_see(str, he))
				ans[he.i2][he.i] = str[he.i3];
			if (he.c != ' ' || quote_see(str, he))
				he.i += 1;
			he.i3 = quote_check(str, he.i3, &he.q, &he.sq);
		}
		ans[he.i2][he.i] = '\0';
		he.i2 += 1;
		he.i = 0;
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

char	**parse_split(char const *str, char c, t_data *info)
{
	int		h;
	char	**ans;
	t_split	he;

	if (str == NULL)
		return (NULL);
	init_help(info, &he, c, str);
	if (c == ' ')
		h = string_amount(str, he, 1, he.sq + he.q);
	else
		h = string_amount(str, he, 1, 0);
	ans = (char **) malloc(sizeof(char *) * (h + 1));
	if (ans == NULL)
		return (NULL);
	ans[h] = 0;
	he.h = h;
	if (c == ' ')
		he.i3 = he.sq + he.q;
	ans = ansllocator(ans, str, info, he);
	ans = check_malloc(ans, h);
	if (ans == NULL)
		return (NULL);
	ans = string_sep(ans, str, info, he);
	return (ans);
}
