/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:21:53 by leklund           #+#    #+#             */
/*   Updated: 2023/03/01 16:21:58 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

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
	env = retrive_env();
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
