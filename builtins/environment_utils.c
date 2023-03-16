/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
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
	int		fd;
	int 	i;
	int		shlvl_int;
	char	*shlvl_char;
	char	*sh_lvl_str;

	fd = open(".dinoshell_env777_tmp", O_CREAT);
	if (fd < 0 )
		return (0);
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
	close(fd);
	return (1);
}

int	find_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	change_env_variable(t_data *info, char *var)
{
	int	i;
	int	len;
	int	has_equal;
	char **env;

	(void) info;
	i = 0;
	has_equal = 0;
	len = find_equal_sign(var);
	if (!len)
		len = ft_strlen(var);
	env = retrieve_env();
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], var, len))
		{
			len = ft_strlen(var);
			if (find_equal_sign(env[i]) && !find_equal_sign((var)))
				has_equal = 1;
			free(env[i]);
			env[i] = (char *)malloc(sizeof(char) * (len + has_equal + 1));
			ft_strlcpy(env[i], var, len + 1);
			if (has_equal && env[i][len] != '=')
			{
				env[i][len] = '=';
				env[i][len + 1] = '\0';
			}
			make_env_file(env);
			free(env);
			return (1);
		}
		i++;
	}
	return (0);
}

// int	change_env_variable(t_data *info, char *var)
// {
// 	int	i;
// 	int	len;
// 	int	has_equal;
// 	int	fd;
// 	char *line;
// 	(void) info;

// 	i = 0;
// 	has_equal = 0;
// 	fd = open(".dinoshell_env777_tmp", O_RDWR);
// 	len = find_equal_sign(var);
// 	if (!len)
// 		len = ft_strlen(var);
// 	while (42)
// 	{
// 		line = get_next_line(fd);
// 		if (!ft_strncmp(line, var, len))
// 		{
// 			len = ft_strlen(var);
// 			if (find_equal_sign(line) && !find_equal_sign((var)))
// 				has_equal = 1;
// 			if (has_equal && line[len] != '=')
// 			{
// 				line[len] = '=';
// 				line[len + 1] = '\0';
// 			}
// 			write(fd, line, len);
// 			free(line);
// 			return (1);
// 		}
// 		free(line);
// 		i++;
// 	}
// 	return (0);
// }
