/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:21:53 by leklund           #+#    #+#             */
/*   Updated: 2023/03/01 16:21:58 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	find_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	change_env_variable(t_data *info, char *var)
{
	int	i;
	int	len;
	int	has_equal;

	i = 0;
	has_equal = 0;
	len = find_equal_sign(var);
	if (!len)
		len = ft_strlen(var);
	while (info->envs[i] != NULL)
	{
		if (!ft_strncmp(info->envs[i], var, len))
		{
			len = ft_strlen(var);
			if (find_equal_sign(info->envs[i]) && !find_equal_sign((var)))
				has_equal = 1;
			free(info->envs[i]);
			info->envs[i] = (char *)malloc(sizeof(char) * (len + has_equal + 1));
			ft_strlcpy(info->envs[i], var, len + 1);
			if (has_equal && info->envs[i][len] != '=')
			{
				info->envs[i][len] = '=';
				info->envs[i][len + 1] = '\0';
			}
			return (1);
		}
		i++;
	}
	return (0);
}
