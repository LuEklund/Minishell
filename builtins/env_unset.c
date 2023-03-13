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

static int	contain_flag(t_data *info, char *var)
{
	if (var[0] && var[0] == '-')
	{
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd(" unset: ", 2);
		ft_putchar_fd(var[0], 2);
		ft_putchar_fd(var[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("unset: usage: unset [name ...]\n", 1);
		return (1);
	}
	return (0);
}

int	unset_env(t_data *info, char *rm_var)
{
	int	index_args;

	index_args = 1;
	if (rm_var)
	{
		if (contain_flag(info, rm_var))
			return (0);
		unset_env_function(info, rm_var);
	}
	else
	{
		if (contain_flag(info, info->args[index_args]))
			return (0);
		while (info->args[index_args])
		{
			unset_env_function(info, info->args[index_args]);
			index_args++;
		}

	}
	return (1);
}