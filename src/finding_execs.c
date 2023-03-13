/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_execs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:10:10 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/08 13:13:17 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	test_access(t_data *info, char *str)
{
	int	i;

	i = 0;
	while (info->paths[i] && !(info->check))
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
	info->check = 1;
	while (info->envs[i])
	{
		if (!(ft_strncmp(info->envs[i], "PATH=", 5)))
			break ;
		i++;
	}
	if (!info->envs[i])
		return (ft_putendl_fd("no paths", 2));
	while (info->envs[i][i2] != '/')
		i2++;
	info->paths = ft_split(info->envs[i] + i2, ':');
	if (!info->paths || !info->paths[0])
		return (ft_putendl_fd("split failed", 2));
	info->check = 0;
}

void	test_paths(t_data *info, char *str)
{
	size_t	i;
	size_t	safe;
	char	*cmd;

	i = 0;
	info->check = 0;
	while (str[i] != ' ' && str[i])
		i++;
	cmd = malloc(sizeof(char) * (i + 2));
	if (!cmd)
		return ;
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
	if (!access(info->args[0], X_OK))
	{
		info->cmd_to_use = ft_strdup(info->args[0]);
		info->check = 1;
	}
	else
		test_paths(info, info->args[0]);
	if (!info->check)
		info->check = 1;
	else
		info->check = 0;
	if (!info->cmd_to_use)
	{
		free_ar(info->args);
		return (ft_putendl_fd("no cmd :(", 2));
	}
}

void	arguing(t_data *info)
{
	info->exit = 0;
	info->check = 1;
	info->cmd_to_use = NULL;
	info->args = parse_split(info->cmds[info->i], ' ', info);
	if (!info->args || !info->args[0])
	{
		info->return_val = 258;
		return (ft_putstr_fd(info->dino, 2), \
		ft_putendl_fd("syntax error near unexpected token `|'", 2));
	}
	is_built_in(info);
	if (info->built)
		return (bob_the_builtin(info));
	find_execs(info);
}
