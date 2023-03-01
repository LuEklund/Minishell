/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviorment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:02:28 by leklund           #+#    #+#             */
/*   Updated: 2023/03/01 13:08:57 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	display_env(t_data *info)
{
	int i;

	i = 0;
	while (info->envs[i] != NULL)
	{
		printf("%s\n", info->envs[i]);
		i++;
	}
	return (1);
}

int	valid_var(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '=')
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	unset_env(t_data *info, char *rm_var)
{
	char		**new_environ;
	int			i;
	int			removeable;

	i = 0;
	removeable = 0;
	while (info->envs[i] != NULL)
	{
		if (!ft_strncmp(info->envs[i], rm_var, ft_strlen(rm_var)))
			removeable = i;
		i++;
	}
	if (!removeable)
		return (0);
	new_environ = (char **)malloc(sizeof(char *) * (i));
	if (!new_environ)
		return (0);
	i = 0;
	while (info->envs[i] != NULL)
	{
		if (i != removeable)
		{
			if (removeable)
				new_environ[i] = info->envs[i];
			else
				new_environ[i - 1] = info->envs[i];
		}
		else
			removeable = 0;
		i++;
	}
	new_environ[i] = NULL;
	free(info->envs);
	info->envs = new_environ;
	return (1);
}

int	env_export(t_data *info, char *new_var)
{
	char		**new_env;
	int			i;

		printf("STRING [%s]\n", new_var);
	if(!new_var)
	{
		display_env(info);
		return (1);
	}
	if (!valid_var(new_var))
	{
		printf("NOT VALID\n");
		return (0);
	}
		printf("VALID\n");
	i = 0;
	while (info->envs[i] != NULL)
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (0);
	i = 0;
	while (info->envs[i] != NULL)
	{
		new_env[i] = info->envs[i];
		i++;
	}
	new_env[i] = (char *)malloc(sizeof(char) * (ft_strlen(new_var) + 1));
	ft_strlcpy(new_env[i], new_var, ft_strlen(new_var) + 1);
	i++;
	new_env[i] = NULL;

	free(info->envs);
	info->envs = new_env;
	// display_env(info);
	return (1);
}
