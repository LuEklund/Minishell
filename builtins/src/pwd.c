/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:49:35 by leklund           #+#    #+#             */
/*   Updated: 2023/02/19 10:49:39 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*argumenter(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ')
		i++;
	return (&str[++i]);
}

int	display_curdir()
{
	char 	path[4095];

	if (getcwd(path, sizeof(path)))
		printf("%s\n\r", path);
	else
		return (0);
	return (1);
}

int	change_dir(char *path)
{
	// printf("%s\n\r", argumenter(path));
	if (chdir(argumenter(path)) == 0)
		return (1);
	else
		return (0);
}

int	get_env()
{
	extern char **environ;
	int i;

	i= 0;
	while (environ[i] != NULL)
	{
		printf("%s\n\r", environ[i]);
		i++;
	}
	return (1);
}

int	env_export(char *new_var)
{
	extern char	**environ;
	char		**new_environ;
	int			i;
	//Big leaks problem
	i = 0;
	while (environ[i] != NULL)
		i++;
	new_environ = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_environ)
		return (0);
	i = 0;
	while (environ[i] != NULL)
	{
		new_environ[i] = environ[i];
		i++;
	}
	new_environ[i++] = new_var;
	new_environ[i] = NULL;
	environ = new_environ;
	return (1);
}

int	unset_env(char *rm_var)
{
	extern char	**environ;
	char		**new_environ;
	int			i;
	int			removeable;
	//Big leaks problem
	i = 0;
	removeable = 0;
	while (environ[i] != NULL)
	{
		if (!ft_strncmp(environ[i], rm_var, ft_strlen(rm_var)))
			removeable = i;
		i++;
	}
	if (!removeable)
		return (0);
	new_environ = (char **)malloc(sizeof(char *) * (i));
	if (!new_environ)
		return (0);
	i = 0;
	while (environ[i] != NULL)
	{
		if (i != removeable)
		{
			if (removeable)
				new_environ[i] = environ[i];
			else
				new_environ[i - 1] = environ[i];
		}
		else
			removeable = 0;
		i++;
	}
	new_environ[i] = NULL;
	environ = new_environ;
	return (1);
}

int	echo(char *str, int flag)
{
	printf("%s", str);
	if (!flag)
		printf("\n");
	printf("\r");
	return (1);
}
