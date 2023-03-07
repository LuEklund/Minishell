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

int	display_env(t_data *info, int export_type)
{
	int	i;
	int	i2;
	char c;

	i = 0;
	i2 = 0;
	c = 34;
	while (info->envs[i] != NULL)
	{
		if (export_type)
		{
			i2 = 0;
			printf("declare -x ");
			while (info->envs[i][i2] != '\0' && info->envs[i][i2] != '=')
				printf("%c", info->envs[i][i2++]);
			if (info->envs[i][i2++])
				printf("=%c%s%c",c ,info->envs[i]+i2, c);
			printf("\n");
		}
		else if (find_equal_sign(info->envs[i]))
			printf("%s\n\r", info->envs[i]);
		i++;
	}
	return (1);
}

int	export_error_handler(t_data *info, char *new_var)
{
	(void) info;
	if (new_var[0] && !((new_var[0] >= 65 && new_var[0] <= 90) || (new_var[0] >= 97 && new_var[0] <= 122)))
	{
		return (0);
	}
	return (1);
}

int	export_env_function(t_data *info, char *new_var)
{
	char		**new_env;
	int			i;

	if (!export_error_handler(info, new_var))
		printf("\033[0;32mDinoshell>\033[0m export: `%s': not a valid identifier\n", new_var);
	else
	{
		if (!change_env_variable(info, new_var))
		{
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
		}
	}
	return (1);
}

int	env_export(t_data *info, char *manual_add)
{
	int index_var;

	if (manual_add)
	{
		export_env_function(info, manual_add);
	}
	else
	{
		index_var = 1;
		if (!info->args[index_var])
		{
			display_env(info, 1);
			return (1);
		}
		while (info->args[index_var])
		{
			export_env_function(info, info->args[index_var]);
			index_var++;
		}	
	}
	return (1);
}
