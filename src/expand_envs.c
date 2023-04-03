/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:25:20 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/16 15:49:09 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	copy_ret(t_data *info, t_split *help, char **ans, int len)
{
	int	ret;
	int	safe;

	if (info->return_val != 258)
		ret = info->return_val % 255;
	else
		ret = 258;
	if (ret < 0)
	{
		ret = -ret;
		ans[help->i2][help->i] = '-';
		len++;
	}
	safe = len;
	while (len)
	{
		ans[help->i2][help->i + len - 1] = ret % 10 + '0';
		ret = ret / 10;
		len--;
	}
	help->i += safe;
	return (1);
}

int	return_value(t_data *info, t_split *help, char const *str, char **ans)
{
	int	len;
	int	ret;

	len = 1;
	ret = 258;
	if (help->expand_type > 1)
		return (redir_input_parser(str, help, 1));
	if (info->return_val != 258)
		ret = info->return_val % 255;
	if (ret < 0)
	{
		ret = -ret;
		len++;
	}
	while (ret / 10)
	{
		ret = ret / 10;
		len++;
	}
	help->i3 += 2;
	if (help->check)
		return (copy_ret(info, help, ans, len));
	help->i += len;
	return (1);
}

void	envy(int i, t_split *help, t_data *info, char **ans)
{
	int	i2;

	i2 = 0;
	while (info->envs[i][i2] != '=')
		i2++;
	i2++;
	while (info->envs[i][i2])
	{
		ans[help->i2][help->i] = info->envs[i][i2];
		i2++;
		help->i += 1;
	}
}

int	find_the_right_env(char *str2, t_split *help, t_data *info, char **ans)
{
	int	i;
	int	i2;
	int	i3;
	int	len;

	i = 0;
	i2 = 0;
	len = ft_strlen(str2);
	while (info->envs[i] && ft_strncmp(info->envs[i], str2, len))
		i++;
	free(str2);
	if (!info->envs[i])
		return (1);
	if (help->check)
		return (envy(i, help, info, ans), 1);
	while (info->envs[i][i2] != '=')
		i2++;
	i3 = i2 + 1;
	while (info->envs[i][i3])
		i3++;
	i3 -= (i2 + 1);
	help->i += i3 + 1;
	return (1);
}

int	expand_envs(const char *s1, t_data *info, t_split *he, char **ans)
{
	int		i;
	char	*s2;

	i = 0;
	if (he->expand_type)
		return (return_value(info, he, s1, ans));
	while (s1[i + 1 + he->i3] && s1[i + 1 + he->i3] != '\"' && s1[i + 1 \
	+ he->i3] != '\'' && s1[i + 1 + he->i3] != ' ' && s1[i + 1 + he->i3] \
	!= '|' && s1[i + 1 + he->i3] != '/' && s1[i + 1 + he->i3] != '=' \
	&& s1[i + 1 + he->i3] != '$')
		i++;
	if (i == 0 || s1[i + 1 + he->i3] == '|')
		return (0);
	s2 = malloc(sizeof(char) * (i + 2));
	if (!s2)
		exit(write(2, "memory errawr🦖\n", 15));
	i = -1;
	while (s1[++i + 1 + he->i3] && s1[i + 1 + he->i3] != '\"' && s1[i + 1 + \
	he->i3] != '\'' && s1[i + 1 + he->i3] != ' ' && s1[i + 1 + he->i3] \
	!= '/' && s1[i + 1 + he->i3] != '=' && s1[i + 1 + he->i3] != '$')
		s2[i] = s1[i + 1 + he->i3];
	ft_strlcpy(s2 + i, "=", 2);
	he->i3 += i + 1;
	return (find_the_right_env(s2, he, info, ans));
}
