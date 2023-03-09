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

int	display_curdir()
{
	char 	path[4095];

	if (getcwd(path, sizeof(path)))
		printf("%s\n\r", path);
	else
		return (0);
	return (1);
}

char	*get_curdir()
{
	char 	path[4095];
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

int	change_dir(t_data *info)
{
	char	*curr_dir;
	char	*old_pwd_var;
	char	*new_pwd_var;

	curr_dir = get_curdir();
	if (!curr_dir)
		return (0);
	if (chdir(info->args[1]) == 0)
	{
		old_pwd_var = ft_strjoin("OLDPWD=", curr_dir);
		free(curr_dir);
		env_export(info, old_pwd_var);
		curr_dir = get_curdir();
		if (!curr_dir)
			return (0);
		new_pwd_var = ft_strjoin("PWD=", curr_dir);
		env_export(info, new_pwd_var);
		free(curr_dir);
		return (1);
	}
	else
		return (0);
}
