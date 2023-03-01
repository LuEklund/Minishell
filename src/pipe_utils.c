/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:46:56 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/01 17:45:49 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_built_in(t_data *info)
{
	info->built = 0;
	info->check = 0;
	if (!ft_strncmp("echo", info->args[0], 5))
		info->built = 1;
	else if (!ft_strncmp("cd", info->args[0], 3))
		info->built = 2;
	else if (!ft_strncmp("pwd", info->args[0], 4))
		info->built = 3;
	else if (!ft_strncmp("exit", info->args[0], 5))
		info->built = 4;
	else if (!ft_strncmp("unset", info->args[0], 6))
		info->built = 5;
	else if (!ft_strncmp("export", info->args[0], 7))
		info->built = 6;
	else if (!ft_strncmp("env", info->args[0], 4))
		info->built = 7;
}

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

int	get_duped(int read, int write)
{
	int	check;

	check = dup2(read, 0);
	if (check < 0)
		return (1);
	check = dup2(write, 1);
	if (check < 0)
		return (1);
	return (0);
}

void	the_kindergarden(t_data *info)
{
	if (info->pipe_amount == 0)
		info->check = get_duped(info->fd_in, info->fd_out);
	else if (info->i == 0)
		info->check = get_duped(info->fd_in, info->pipe[1]);
	else if (info->i == info->cmd_amount - 1)
		info->check = get_duped(info->pipe[(info->i * 2) - 2], info->fd_out);
	else
		info->check = get_duped(info->pipe[(info->i * 2) - 2], \
				info->pipe[(info->i * 2) + 1]);
	if (!info->check && info->pipe_amount != 0)
		close_pipeline(info);
	if (!info->check && info->built)
		exit(execute_built(info));
	if (!ft_strncmp(info->cmd_to_use, " ", 2))
		exit (0);
	if (!info->check)
	{
		execve(info->cmd_to_use, info->args, info->envs);
		info->check = 1;
	}
}

void	free_commands(t_data *info)
{
	free_ar(info->args);	
	free(info->cmd_to_use);
}
