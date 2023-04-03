/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:56:40 by leklund           #+#    #+#             */
/*   Updated: 2023/02/25 12:56:43 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	display_curdir(t_data *info)
{
	char	path[4095];
	int		i;

	i = 0;
	while (info->envs[i] && ft_strncmp(info->envs[i], "PWD=", 4))
		i++;
	if (!info->envs[i])
	{
		if (getcwd(path, sizeof(path)))
			printf("%s\n", path);
		else
			return (0);
	}
	else
		printf("%s\n", info->envs[i]+4);
	return (1);
}

char	*get_curdir(void)
{
	char	path[4095];
	char	*return_ptr;

	if (getcwd(path, sizeof(path)))
	{
		return_ptr = (char *)malloc(sizeof(char) * ft_strlen(path) + 1);
		if (!return_ptr)
			return (NULL);
		ft_strlcpy(return_ptr, path, ft_strlen(path) + 1);
		return (return_ptr);
	}
	else
		return (NULL);
}

int	go_home(t_data *info)
{
	int		i;
	char	*home;

	i = 0;
	while (info->envs[i] && ft_strncmp(info->envs[i], "HOME=", 5))
		i++;
	if (!info->envs[i])
	{
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (info->envs[i][5])
		home = info->envs[i] + 5;
	else
		return (1);
	return (apply_change(info, home));
}

int	go_prev(t_data *info)
{
	int		i;
	char	*prev;

	i = 0;
	while (info->envs[i] && ft_strncmp(info->envs[i], "OLDPWD=", 7))
		i++;
	if (!info->envs[i])
	{
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	prev = info->envs[i] + 7;
	return (apply_change(info, prev));
}

int	change_dir(t_data *info)
{
	if (!info->args[1])
		return (go_home(info));
	if (info->args[1][0] == '-' && !info->args[1][1])
	{
		if (go_prev(info))
			return (1);
		display_curdir(info);
		return (0);
	}
	return (apply_change(info, info->args[1]));
}
