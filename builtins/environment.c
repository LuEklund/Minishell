/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviorment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:02:28 by leklund           #+#    #+#             */
/*   Updated: 2023/03/06 11:48:39 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	display_env(t_data *info, int export_type)
{
	int		i;
	int		i2;
	char 	c;
	char	**env;
	(void) info;

	i = 0;
	i2 = 0;
	c = 34;
	env = retrieve_env();
	while (env[i] != NULL)
	{
		if (export_type)
		{
			i2 = 0;
			printf("declare -x ");
			while (env[i][i2] != '\0' && env[i][i2] != '=')
				printf("%c", env[i][i2++]);
			if (env[i][i2++])
				printf("=%c%s%c",c ,env[i]+i2, c);
			printf("\n");
		}
		else if (find_equal_sign(env[i]))
			printf("%s\n\r", env[i]);
		i++;
	}
	free_ar(env);
	return (1);
}

int	export_error_handler(t_data *info, char *new_var)
{
	if (new_var[0]
		&& !((new_var[0] >= 65 && new_var[0] <= 90)
			|| (new_var[0] >= 97 && new_var[0] <= 122)))
	{
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd(" export: '", 2);
		ft_putstr_fd(new_var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	return (1);
}

static int	contain_flag(t_data *info, char *var)
{
	if (var[0] && var[0] == '-')
	{
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd(" export: ", 2);
		ft_putchar_fd(var[0], 2);
		ft_putchar_fd(var[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("export: usage: export [name[=value] ...]\n", 1);
		return (1);
	}
	return (0);
}

int	export_env_function(t_data *info, char *new_var)
{
	char		**new_env;
	char		**curr_env;
	int			i;

	if (!export_error_handler(info, new_var))
		return (1);
	else
	{
		if (!change_env_variable(info, new_var))
		{
			curr_env = retrieve_env();
			i = 0;
			while (curr_env[i] != NULL)
				i++;
			new_env = (char **)malloc(sizeof(char *) * (i + 2));
			if (!new_env)
				return (1);
			i = 0;
			while (curr_env[i] != NULL)
			{
				new_env[i] = curr_env[i];
				i++;
			}
			new_env[i] = (char *)malloc(sizeof(char) * (ft_strlen(new_var) + 1));
			ft_strlcpy(new_env[i], new_var, ft_strlen(new_var) + 1);
			i++;
			new_env[i] = NULL;

			make_env_file(new_env);
			free_ar(curr_env);
			free(new_env);
		}
	}
	return (0);
}


int	env_export(t_data *info, char *manual_add)
{
	int index_var;

	if (manual_add)
	{
		if (contain_flag(info, manual_add))
			return (1);
		export_env_function(info, manual_add);
	}
	else
	{
		index_var = 1;
		if (!info->args[index_var])
		{
			display_env(info, 1);
			return (0);
		}
		if (contain_flag(info, info->args[index_var]))
			return (1);
		while (info->args[index_var])
		{
			export_env_function(info, info->args[index_var]);
			index_var++;
		}	
	}
	return (0);
}






