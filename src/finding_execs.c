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

void	find_the_paths(t_data *info)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (info->envs[i])
	{
		if (!(ft_strncmp(info->envs[i], "PATH=", 5)))
			break ;
		i++;
	}
	if (!info->envs[i])
	{
		info->paths = NULL;
		return ;
	}
	while (info->envs[i][i2] != '/')
		i2++;
	info->paths = ft_split(info->envs[i] + i2, ':');
	if (!info->paths || !info->paths[0])
		exit(write(2, "memory error\n", 13));
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

void	find_execs(t_data *info)
{
	info->cmd_to_use = NULL;
	if (!access(info->args[0], X_OK))
		info->cmd_to_use = ft_strdup(info->args[0]);
	else
		test_paths(info, info->args[0]);
	if (!info->cmd_to_use)
	{
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd(info->args[0], 2);
		if (info->paths)
			ft_putstr_fd(": command not found\n", 2);
		else
			ft_putstr_fd(": No such file or directory\n", 2);
		free_ar(info->args);
		info->return_val = 127;
	}
}

int	arguing(t_data *info)
{
	info->built_exec = 0;
	info->exit = 0;
	info->cmd_to_use = NULL;
	info->args = parse_split(info->cmds[info->i], ' ', info);
	wild_card_check(info, 1, 0);
	is_built_in(info, info->args[0]);
	if (info->built)
		return (0);
	find_execs(info);
	if (!info->cmd_to_use)
		return (1);
	return (0);
}
