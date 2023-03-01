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

int	change_env_variable(t_data *info, char *var_name, char *var_info)
{
	int	i;
	int	len;
	int	len_info;

	i = 0;
	len = find_equal_sign(var_name);
	if (!len)
		len = ft_strlen(var_name);
	while (info->envs[i] != NULL)
	{
		// printf("[%d] [%s] == [%s], len: %d\n",i , var_name, info->envs[i], len);
		if (!ft_strncmp(info->envs[i], var_name, len))
		{
			printf("good\n");
			len_info = ft_strlen(var_info);
			free(info->envs[i]);
			info->envs[i] = (char *)malloc(sizeof(char) * (len + len_info + 1));
			ft_strlcpy(info->envs[i], var_name, len + 1);
			printf("[%s]\n", info->envs[i]);
			ft_strlcpy(&info->envs[i][len], var_info, len_info + 1);
			printf("[%s]\n", info->envs[i]);
			return (1);
		}
		i++;
	}
	printf("not ex\n");
	return (0);
}
