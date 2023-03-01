/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                              :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:49:35 by leklund           #+#    #+#             */
/*   Updated: 2023/03/01 13:35:45 by nlonka           ###   ########.fr       */
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
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	if (!str[i])
		return (NULL);
	return (&str[++i]);
}

int	echo(t_data *info)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	//handle -n here
	while (info->args[i])
	{
		printf("%s", info->args[i]);
		i++;
	}
	if (!flag)
		printf("\n");
	return (1);
}

int	execute_built(t_data *info)
{
	if (info->built == 1)
	{
		// printf("echo\n\r");
		echo(info);
	}
	else if (info->built == 3)
	{
		// printf("display_curdir\n\r");
		display_curdir();
	}
	else if (info->built == 6)
	{
	//	printf("env_export: [%s]\n\r", *info->cmds);
	//	printf("env_export_arged: [%s]\n\r", argumenter(*info->cmds));
	//	env_export(info, argumenter(*info->cmds));
		display_env(info);
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
