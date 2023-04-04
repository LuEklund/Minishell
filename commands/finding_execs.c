/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_execs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:10:10 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/23 17:20:54 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	test_access(t_data *info, char *str)
{
	int	i;

	i = 0;
	info->check = 0;
	while (info->paths && info->paths[i] && !(info->check))
	{
		info->cmd_to_use = ft_strjoin(info->paths[i], str);
		if (!info->cmd_to_use)
			return ;
		info->check = access(info->cmd_to_use, X_OK) + 1;
		if (!info->check)
		{
			i++;
			free(info->cmd_to_use);
		}
	}
	if (!info->check)
		info->cmd_to_use = NULL;
}

void	test_paths(t_data *info, char *str)
{
	size_t	i;
	size_t	safe;
	char	*cmd;

	i = 0;
	if (!str)
		return ;
	info->check = 0;
	while (str[i])
		i++;
	cmd = malloc(sizeof(char) * (i + 2));
	if (!cmd)
		exit(write(2, "memory error\n", 13));
	cmd[0] = '/';
	cmd[i + 1] = '\0';
	safe = i;
	i = 1;
	while (i != safe + 1)
	{
		cmd[i] = str[i - 1];
		i++;
	}
	test_access(info, cmd);
	free(cmd);
}

void	print_access_error(t_data *info)
{
	struct stat	statbuf;

	info->return_val = 127;
	stat(info->args[0], &statbuf);
	if (info->paths && (access(info->args[0], F_OK) || \
	!(statbuf.st_mode & S_IFDIR)))
		return (ft_putendl_fd(": command not found", 2));
	if (access(info->args[0], F_OK))
		return (ft_putendl_fd(": No such file or directory", 2));
	info->return_val = 126;
	if (!(statbuf.st_mode & S_IFDIR))
		return (ft_putendl_fd(": Permission denied", 2));
	ft_putendl_fd(": is a directory", 2);
}

void	find_execs(t_data *info)
{
	pid_t		kiddo;
	struct stat	statbuf;

	stat(info->args[0], &statbuf);
	info->cmd_to_use = NULL;
	if (!access(info->args[0], X_OK) && !(statbuf.st_mode & S_IFDIR))
		info->cmd_to_use = ft_strdup(info->args[0]);
	else if (info->args[0] && info->args[0][0])
		test_paths(info, info->args[0]);
	if (!info->cmd_to_use && (info->qt_total > 0 || info->empty))
	{
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd(info->args[0], 2);
		print_access_error(info);
		free_ar(info->args);
		kiddo = fork();
		if (!kiddo)
			exit(info->return_val);
		waitpid(kiddo, &info->return_val, 0);
	}
}

int	arguing(t_data *info)
{
	info->empty = 0;
	info->built_exec = 0;
	info->exit = 0;
	info->cmd_to_use = NULL;
	info->args = parse_split(info->cmds[info->i], ' ', info);
	while (info->args && info->args[0] && info->args[0][info->empty])
		info->empty += 1;
	info->qt_total = info->split->qt_total;
	wild_card_check(info, 1, 0);
	is_built_in(info, info->args[0]);
	if (info->built)
		return (0);
	find_execs(info);
	if (!info->cmd_to_use)
		return (1);
	return (0);
}
