/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:06:51 by leklund           #+#    #+#             */
/*   Updated: 2023/03/07 10:06:54 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"


int	unset_env_function(t_data *info, char *rm_var)
{
	char		**new_environ;
	int			i;
	int			removeable;

	i = 0;
	removeable = 0;
	if (!export_error_handler(info, rm_var))
	{
		printf("\033[0;32mDinoshell>\033[0m unset: `%s': not a valid identifier\n", rm_var);
		return (0);
	}
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

int	unset_env(t_data *info, char *rm_var)
{
	int	index_args;

	index_args = 1;
	if (rm_var)
	{
		unset_env_function(info, rm_var);
	}
	else
	{
		while (info->args[index_args])
		{
			unset_env_function(info, info->args[index_args]);
			index_args++;
		}

	}
	return (1);
}