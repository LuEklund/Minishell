/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:49:35 by leklund           #+#    #+#             */
/*   Updated: 2023/02/19 10:49:39 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"


char	**copy_env(char **env_to_copy)
{
	char		**new_env;
	int			i;

	i = 0;
	while (env_to_copy[i] != NULL)
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env_to_copy[i] != NULL)
	{
		new_env[i] = env_to_copy[i];
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

static char	*argumenter(char *str)
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
	// printf("%s\n\r", path);
	// printf("%s\n\r", argumenter(path));
	if (chdir(argumenter(path)) == 0)
		return (1);
	else
		return (0);
}

int	display_env(t_data *info)
{
	int i;

	i= 0;
	while (info->envs[i] != NULL)
	{
		printf("%s\n\r", info->envs[i]);
		i++;
	}
	return (1);
}

int	env_export(t_data *info, char *new_var)
{
	char		**new_env;
	int			i;

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
	display_env(info);
	return (1);
}

int	unset_env(t_data *info, char *rm_var)
{
	char		**new_environ;
	int			i;
	int			removeable;
	//Big leaks problem
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

int	echo(char *str, int flag)
{
	printf("%s", str);
	if (!flag)
		printf("\n");
	printf("\r");
	return (1);
}


int	execute_built(t_data *info)
{
	if (info->built == 1)
	{
		// printf("echo\n\r");
		echo(*info->cmds, 0);
	}
	else if (info->built == 2)
	{
		// printf("change_dir: %s\n\r", *info->cmds);
		change_dir(*info->cmds);
	}
	else if (info->built == 3)
	{
		// printf("display_curdir\n\r");
		display_curdir();
	}
	else if (info->built == 4)
	{
		printf("exit\n\r");
		// exit (0);
	}
	else if (info->built == 5)
	{
		// printf("unset_env\n\r");
		unset_env(info, argumenter(*info->cmds));
	}
	else if (info->built == 6)
	{
		// printf("env_export: %s\n\r", argumenter(*info->cmds));
		env_export(info, argumenter(*info->cmds));
	}
	else if (info->built == 7)
	{
		// printf("display_env\n\r");
		display_env(info);
	}
	else
	{
		printf("error\n\r");
	}
	return (0);
}
