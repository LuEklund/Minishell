/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:25:20 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/06 11:24:25 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	find_the_right_env(char *str2, t_split *help, t_data *info, char **ans)
{
	int i;
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
		return ;
	if (help->check)
	{
		envy(i, help, info, ans);
		return ;
	}
	while (info->envs[i][i2] != '=')
		i2++;
	i3 = i2 + 1;
	while (info->envs[i][i3])
		i3++;
	i3 -= (i2 + 1);
	help->i += i3 + 1;
}

int	expand_envs(const char *s1, t_data *info, t_split *he, char **ans)
{
	int		i;
	char	*s2;

	i = 0;
	while (s1[i + 1 + he->i3] && s1[i + 1 + he->i3] != '\"' && s1[i + 1 + he->i3] != '\'' \
			&& s1[i + 1 + he->i3] != ' ' && s1[i + 1 + he->i3] != '|')
		i++;
	if (i == 0 || s1[i + 1 + he->i3] == '|')
		return (0);
	s2 = malloc(sizeof(char) * (i + 2));
	if (!s2)
		exit(write(2, "yikes\n", 6));
	i = 0;
	while (s1[i + 1 + he->i3] && s1[i + 1 + he->i3] != '\"' && s1[i + 1 + he->i3] \
			!= '\'' && s1[i + 1 + he->i3] != ' ') 
	{
		s2[i] = s1[i + 1 + he->i3];
		i++;
	}
	s2[i] = '=';
	s2[i + 1] = '\0';
	he->i3 += i + 1;
	find_the_right_env(s2, he, info, ans);
	return (1);
}
