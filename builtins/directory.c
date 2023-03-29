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

int	display_curdir(void)
{
	char	path[4095];

	if (getcwd(path, sizeof(path)))
		printf("%s\n\r", path);
	else
		return (0);
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

int	changde_dir_success(t_data *info, char *curr_dir)
{
	char	*old_pwd_var;
	char	*new_pwd_var;

	old_pwd_var = ft_strjoin("OLDPWD=", curr_dir);
	free(curr_dir);
	env_export(info, old_pwd_var);
	free(old_pwd_var);
	curr_dir = get_curdir();
	if (!curr_dir)
		return (1);
	new_pwd_var = ft_strjoin("PWD=", curr_dir);
	env_export(info, new_pwd_var);
	free(new_pwd_var);
	free(curr_dir);
	return (0);
}

void	changde_dir_error(t_data *info, char *curr_dir)
{
	free(curr_dir);
	if (info->args[1][0] == '-')
	{
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd("cd: ", 2);
		ft_putchar_fd(info->args[1][0], 2);
		ft_putchar_fd(info->args[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("cd: usage: cd [path]\n", 1);
	}
	else
	{
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd(": cd: ", 2);
		ft_putstr_fd(info->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

int	change_dir(t_data *info)
{
	char		*curr_dir;
	int			return_val;
	struct stat	statbuf;

	stat(info->args[1], &statbuf);
	if (!(statbuf.st_mode & S_IFDIR))
	{
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(info->args[1], 2);
		ft_putstr_fd(": Not a directory\n", 2);
		return (1);
	}
	curr_dir = get_curdir();
	if (!curr_dir)
		return (0);
	return_val = chdir(info->args[1]);
	if (return_val == 0)
		return (changde_dir_success(info, curr_dir));
	else
		changde_dir_error(info, curr_dir);
	return (1);
}
