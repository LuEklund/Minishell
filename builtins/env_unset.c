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

static int	unset_error_checks(t_data *info, char *rm_var)
{
	if (!env_error_handler(info, rm_var, "unset"))
		return (1);
	if (find_equal_sign(rm_var))
	{
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd("unset: `", 2);
		ft_putstr_fd(rm_var, 2);
		ft_putstr_fd("`: not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

void	make_new_envirno(t_data *info, char **new_environ, int removeable)
{
	int	i;

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
		{
			free(info->envs[i]);
			removeable = 0;
		}
		i++;
	}
	new_environ[i] = NULL;
	free(info->envs);
	info->envs = new_environ;
}

int	unset_env_function(t_data *info, char *rm_var)
{
	char		**new_environ;
	int			i;
	int			removeable;

	i = 0;
	removeable = 0;
	if (unset_error_checks(info, rm_var))
		return (1);
	while (info->envs[i] != NULL)
	{
		if (!ft_strncmp(info->envs[i], rm_var, ft_strlen(rm_var))
			|| (find_equal_sign(rm_var)
				&& !ft_strncmp(info->envs[i], rm_var, find_equal_sign(rm_var))))
			removeable = i;
		i++;
	}
	if (!removeable)
		return (0);
	new_environ = (char **)malloc(sizeof(char *) * (i));
	if (!new_environ)
		return (0);
	make_new_envirno(info, new_environ, removeable);
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

int	env_unset(t_data *info, char *manual_remove)
{
	int	index_args;

	if (manual_remove)
	{
		if (contain_flag(info, manual_remove))
			return (1);
		unset_env_function(info, manual_remove);
	}
	else
	{
		index_args = 1;
		if (!info->args[index_args])
			return (1);
		if (contain_flag(info, info->args[index_args]))
			return (1);
		while (info->args[index_args])
		{
			unset_env_function(info, info->args[index_args]);
			index_args++;
		}
	}
	return (1);
}
