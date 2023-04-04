/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:21:53 by leklund           #+#    #+#             */
/*   Updated: 2023/03/16 20:29:18 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	upgrade_shell_lvl(t_data *info, char **env_to_copy)
{
	int		i;
	int		shlvl_int;
	char	*shlvl_char;
	char	*sh_lvl_str;

	i = 0;
	while (env_to_copy[i])
	{
		if (!ft_strncmp(env_to_copy[i], "SHLVL=", 6))
		{
			shlvl_int = ft_atoi(env_to_copy[i] + 6) + 1;
			shlvl_char = ft_itoa(shlvl_int);
			sh_lvl_str = ft_strjoin("SHLVL=", shlvl_char);
			env_export(info, sh_lvl_str);
			free(shlvl_char);
			free(sh_lvl_str);
		}
		i++;
	}
	return (1);
}

int	find_sign(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	append_env_var(t_data *info, char *var, int i)
{
	char	*new_env_var;
	int		append_from;

	append_from = find_sign(var, '=') + 1;
	if (!find_sign(info->envs[i], '='))
		append_from--;
	new_env_var = ft_strjoin(info->envs[i], var + append_from);
	free(info->envs[i]);
	info->envs[i] = new_env_var;
	return (1);
}

int	uppdate_var(t_data *info, char *var, int i, int append)
{
	int	len;
	int	has_equal;

	has_equal = 0;
	len = ft_strlen(var);
	if (append)
		return (append_env_var(info, var, i));
	if ((find_sign(info->envs[i], '=') && !find_sign(var, '=')) || append)
		has_equal = 1;
	free(info->envs[i]);
	info->envs[i] = (char *)malloc(sizeof(char) * (len + has_equal + 1));
	ft_strlcpy(info->envs[i], var, len + 1);
	if (has_equal && info->envs[i][len] != '=')
	{
		info->envs[i][len] = '=';
		info->envs[i][len + 1] = '\0';
	}
	return (1);
}

int	change_env_variable(t_data *info, char *var)
{
	int	i;
	int	len;
	int	append;

	i = 0;
	append = 0;
	if (find_sign(var, '+') - find_sign(var, '=') == -1
		&& var[find_sign(var, '+')] == '+')
	{
		len = find_sign(var, '+');
		append = 1;
	}
	else
		len = find_sign(var, '=');
	if (!len)
		len = ft_strlen(var);
	while (info->envs[i] != NULL)
	{
		if (!ft_strncmp(info->envs[i], var, len) && (info->envs[i][len] == '='
			|| info->envs[i][len] == '\0'))
			return (uppdate_var(info, var, i, append));
		i++;
	}
	return (0);
}
