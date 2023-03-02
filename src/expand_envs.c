/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:25:20 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/02 18:19:15 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_the_right_env(char *str2, t_split *help, t_data *info)
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
	if (!info->envs[i])
		return ;
	while (info->envs[i][i2] != '=')
		i2++;
	i3 = i2 + 1;
	while (info->envs[i][i3])
		i3++;
	i3 -= (i2 + 1);
	help->i += i3;
	free(str2);
	
}

int	expand_envs(const char *s1, t_data *info, t_split *he)
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
	find_the_right_env(s2, he, info);
	return (1);
}
