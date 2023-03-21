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

int	make_env_file_first_time(t_data *info, char **env_to_copy)
{
	int		fd;
	int 	i;
	char	*env_place;
	(void)	info;

	env_place = ft_strjoin(get_curdir(), "/.dinoshell_env777_tmp");
	g_env_dir = env_place;
	printf("location %s\n", g_env_dir);
	fd = open(g_env_dir, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0 )
		return (0);
	i = 0;
	while (env_to_copy[i])
	{
		write(fd, env_to_copy[i], ft_strlen(env_to_copy[i]));
		write(fd, "\n", 1);
		i++;
	}
	close(fd);
	return (1);
}

int	make_env_file(t_data *info, char **env_to_copy)
{
	int		fd;
	int 	i;
	(void) info;

	fd = open(g_env_dir, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0 )
		return (0);
	i = 0;
	while (env_to_copy[i])
	{
		write(fd, env_to_copy[i], ft_strlen(env_to_copy[i]));
		write(fd, "\n", 1);
		i++;
	}
	close(fd);
	return (1);
}

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

char	**retrieve_env()
{
	int		fd;
	int		i;
	char	*line;
	char	*new_line;
	char	**new_env;

	// printf("open %s\n", g_env_dir);
	fd = open(g_env_dir, O_RDWR);
	if (fd < 0 )
		return (0);
	i = 0;
	while (42)
	{
		line = get_next_line(fd);
		i++;
		if (!line)
			break ;
		free(line);
	}
	new_env = (char **)malloc(sizeof(char *) * (i));
	if (!new_env)
		return (NULL);
	close(fd);
	fd = open(g_env_dir, O_RDWR);
	i = 0;
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
		{
			new_env[i] = NULL;
			break ;
		}
		new_line = (char *)malloc(sizeof(char) * (ft_strlen(line)));
		ft_strlcpy(new_line, line, ft_strlen(line));
		free(line);
		new_env[i] = new_line;
		i++;
	}
	close(fd);
	return (new_env);
}






