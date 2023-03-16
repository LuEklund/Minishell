/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                              :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:49:35 by leklund           #+#    #+#             */
/*   Updated: 2023/03/06 11:40:55 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"


int	make_env_file(char **env_to_copy)
{
	int	fd;
	int i;

	fd = open(".dinoshell_env777_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0 )
		return (0);
	i = 0;
	while (env_to_copy[i])
	{
		write(fd, env_to_copy[i], ft_strlen(env_to_copy[i]));
		i++;
		write(fd, "\n", 1);
	}
	close(fd);
	return (1);
}

char	**retrieve_env(void)
{
	int		fd;
	int		i;
	char	*line;
	char	**new_env;

	fd = open(".dinoshell_env777_tmp", O_RDWR);
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
	new_env = (char **)malloc(sizeof(char *) * i);
	if (!new_env)
		return (NULL);
	close(fd);
	fd = open(".dinoshell_env777_tmp", O_RDWR);
	i = 0;
	while (42)
	{
		line = get_next_line(fd);
		new_env[i] = line;
		if (!line)
			break ;
		i++;
	}
	close(fd);
	i = 0;
	return (new_env);
}

int	handle_word(t_data *info, int i,int file, char *last_char)
{
	int	i2;

	i2 = 0;
	while (info->args[i][i2])
	{
		if (info->args[i][i2] == '>')
			file = 1;
		if (!file)
			write(1, &info->args[i][i2], 1);
		*last_char = info->args[i][i2];
		i2++;
	}
	if (*last_char == '>')
		file = 1;
	else
	{
		if (info->args[i + 1] && info->args[i + 1][0] != '>')
			write(1, " ", 1);
		file = 0;
	}
	return (file);
}

int	echo(t_data *info)
{
	int		i;
	int		new_line;
	int		file;
	char	last_char;

	i = 1;
	new_line = 2;
	file = 0;
	last_char = 0;
	if (info->args[i][0] == '-' && info->args[i][1] == 'n')
	{
		while(info->args[i][new_line] == 'n')
			new_line++;
		if (!info->args[i][new_line])
		{
			new_line = 0;
			i++;
		}
	}
	while (info->args[i])
	{
		printf("%s", info->args[i]);
		// file = handle_word(info, i, file, &last_char);
		i++;
		if (info->args[i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (1);
}

int	execute_built(t_data *info)
{
	if (info->built == 1)
	{
		// printf("echo\n\r");
		return (echo(info));
	}
	else if (info->built == 3)
	{
		// printf("display_curdir\n\r");
		return (display_curdir());
	}
	else if (info->built == 6)
	{
		// env_export(info, 0);
		// display_env(info, 1);	
		return (env_export(info, info->args[1]));
	}
	else if (info->built == 7)
	{
		// printf("display_env\n\r");
		return (display_env(info, 0));
	}
	return (0);
}
