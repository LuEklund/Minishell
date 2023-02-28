/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:09:06 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/11 16:35:06 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	string_amount(char const *str, char c)
{
	int	i;
	int	ans;

	i = 0;
	ans = 1;
	while (str[i] == c && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		ans = -1;
	while (str[i] != '\0')
	{
		while (str[i] == c)
		{
			if (str[i + 1] != c && str[i + 1] != '\0')
				ans++;
			i++;
		}
		if (str[i] != '\0')
			i++;
	}
	if (ans == 0 && str[0] != '\0')
		return (1);
	if (str[0] == '\0' || ans < 0)
		ans = 0;
	return (ans);
}

static char	**ansllocator(char **ans, char const *str, char c, int h)
{
	int	i;
	int	i2;
	int	i3;
	int	l;
	int	h2;

	i = 0;
	i2 = 0;
	i3 = 0;
	h2 = 0;
	while (i2 < h)
	{
		while (str[i3] == c && str[i3] != '\0')
			i3++;
		while (str[i3] != c && str[i3] != '\0')
		{
			i3++;
			i++;
		}
		l = i - h2;
		h2 = h2 + l;
		ans[i2] = (char *) malloc (sizeof(char) * (l + 1));
		i2++;
	}
	return (ans);
}

static char	**string_separator_7000(char **ans, char const *str, char c, int h)
{
	int	i;
	int	i2;
	int	i3;

	i = 0;
	i2 = 0;
	i3 = 0;
	while (i2 < h)
	{
		while (str[i3] == c && str[i3] != '\0')
			i3++;
		while (str[i3] != c && str[i3] != '\0')
			ans[i2][i++] = str[i3++];
		ans[i2][i] = '\0';
		i2++;
		i = 0;
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

char	**ft_split(char const *str, char c)
{
	int		h;
	char	**ans;

	if (str == NULL)
		return (NULL);
	h = string_amount(str, c);
	ans = (char **) malloc(sizeof(char *) * (h + 1));
	if (ans == NULL)
		return (NULL);
	ans[h] = 0;
	ans = ansllocator(ans, str, c, h);
	ans = check_malloc(ans, h);
	if (ans == NULL)
		return (NULL);
	ans = string_separator_7000(ans, str, c, h);
	return (ans);
}
