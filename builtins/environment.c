/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviorment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:02:28 by leklund           #+#    #+#             */
/*   Updated: 2023/03/22 13:04:35 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	**copy_env(char **copy_env)
{
	char		**new_env;
	int			i;

	i = 0;
	while (copy_env[i] != NULL)
		i++;
	if (!i)
		return (NULL);
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (copy_env[i] != NULL)
	{
		new_env[i] = (char *)malloc(sizeof(char) * ft_strlen(copy_env[i]) + 1);
		ft_strlcpy(new_env[i], copy_env[i], ft_strlen(copy_env[i]) + 1);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	display_env(t_data *info, int export_type)
{
	int		i;
	int		i2;
	char	c;

	i = 0;
	i2 = 0;
	c = 34;
	while (info->envs[i] != NULL)
	{
		if (export_type)
		{
			i2 = 0;
			printf("declare -x ");
			while (info->envs[i][i2] != '\0' && info->envs[i][i2] != '=')
				printf("%c", info->envs[i][i2++]);
			if (info->envs[i][i2++])
				printf("=%c%s%c", c, info->envs[i] + i2, c);
			printf("\n");
		}
		else if (info->envs && find_sign(info->envs[i], '='))
			printf("%s\n\r", info->envs[i]);
		i++;
	}
	return (1);
}
