/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:02:28 by leklund           #+#    #+#             */
/*   Updated: 2023/03/06 11:48:39 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

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

int	env_error_handler(t_data *info, char *new_var, char *type)
{
	int	i;
	int	check;

	check = 1;
	i = 0;
	if (new_var[i] == '=' || !new_var[i] || new_var[i] == '+'
		|| (new_var[i] >= '0' && new_var[i] <= '9'))
		check = -1;
	while ((check == -1) || (new_var[i] && new_var[i] != '='))
	{
		if (check == -1 || !((new_var[i] >= 65 && new_var[i] <= 90)
				|| (new_var[i] >= 97 && new_var[i] <= 122) || new_var[i] == '_'
				|| (new_var[i] == '+' && new_var[i + 1] == '=')
				|| (new_var[i] >= '0' && new_var[i] <= '9')))
		{
			ft_putstr_fd(info->dino, 2);
			ft_putstr_fd(type, 2);
			ft_putstr_fd(" `", 2);
			ft_putstr_fd(new_var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	copy_new_var(t_data *info, char **new_env, char *new_var, int i)
{
	int	checkp;
	int	len;

	len = ft_strlen(new_var);
	if (find_sign(new_var, '+') - find_sign(new_var, '=') == -1
		&& new_var[find_sign(new_var, '+')] == '+')
	{
		checkp = find_sign(new_var, '+');
		new_env[i] = (char *)ft_calloc(sizeof(char), len);
		ft_strlcpy(new_env[i], new_var, checkp + 1);
		ft_strlcpy(new_env[i] + checkp, new_var + checkp + 1, len - checkp);
	}
	else
	{
		new_env[i] = (char *)malloc(sizeof(char) * (len + 1));
		ft_strlcpy(new_env[i], new_var, len + 1);
	}
	i++;
	new_env[i] = NULL;
	free(info->envs);
	info->envs = new_env;
}

int	export_env_function(t_data *info, char *new_var)
{
	char	**new_env;
	int		i;

	if (!env_error_handler(info, new_var, "export"))
		return (1);
	else
	{
		if (!change_env_variable(info, new_var))
		{
			i = 0;
			while (info->envs[i] != NULL)
				i++;
			new_env = (char **)malloc(sizeof(char *) * (i + 2));
			if (!new_env)
				return (1);
			i = 0;
			while (info->envs[i] != NULL)
			{
				new_env[i] = info->envs[i];
				i++;
			}
			copy_new_var(info, new_env, new_var, i);
		}
	}
	return (0);
}

int	env_export(t_data *info, char *manual_add)
{
	int	index_var;
	int	ret;

	ret = 0;
	if (manual_add)
	{
		if (contain_flag(info, manual_add))
			return (1);
		if (export_env_function(info, manual_add))
			ret = 1;
	}
	else
	{
		index_var = 0;
		if (!info->args[index_var + 1])
			return (display_env(info, 1));
		if (contain_flag(info, info->args[index_var]))
			return (1);
		while (info->args[++index_var])
		{
			if (export_env_function(info, info->args[index_var]))
				ret = 1;
		}
	}
	return (ret);
}
