/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:00:10 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/23 18:40:56 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_pipes(t_data *info)
{
	size_t	i;

	i = 0;
	info->cmd_amount = 0;
	while (info->cmds[info->cmd_amount])
		info->cmd_amount += 1;
	info->pipe_amount = (info->cmd_amount - 1) * 2;
	info->pipe = malloc(sizeof(int) * info->pipe_amount);
	if (!info->pipe)
		return (write(2, "oijoi\n", 6) - 7);
	while (i < info->cmd_amount)
	{
		if (pipe(info->pipe + 2 * i) < 0)
			return (-1);
		i++;
	}
	return (1);
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
	if (!info->paths)
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

void	arguing(t_data *info)
{
	info->check = 1;
	info->cmd_to_use = NULL;
	info->args = parse_split(info->cmds[info->i], ' ');
	if (!info->args)
		return (ft_putendl_fd("no cmd :(", 2));
	if (!access(info->args[0], X_OK))
		info->cmd_to_use = ft_strdup(info->args[0]);
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

void	handle_buf(t_data *info)
{
	pid_t	kiddo;

	info->i = 0;
	while (info->buf[info->i] && (info->buf[info->i] == ' ' || info->buf[info->i] == '\t' || info->buf[info->i] == '\n'))
		info->i += 1;
	if (!info->buf[info->i])
		return ;
	info->i = 0;
	info->cmds = parse_split(info->buf, '|');
	if (!info->cmds)
		return (ft_putendl_fd("apua", 2));
	if (init_pipes(info) < 0)
		return (ft_putendl_fd("apua 2", 2));
	find_the_paths(info);
	while (info->cmds[info->i] && !info->check)
	{
		is_built_in(info);
		if (!info->built)
			arguing(info);
		if (info->check)
			break ;
//		print_ar(info->args);
		kiddo = fork();
		if (kiddo < 0)
			return (ft_putendl_fd("stillbirth?????\n", 2));
		if (kiddo == 0)
			the_kindergarden(info);
		if (kiddo == 0)
			exit (127);
		if (!info->built)
			free_commands(info);
		info->i += 1;
	}
	if (info->pipe_amount != 0)
		close_pipeline(info);	
	while ((wait(&info->return_val)) > 0)
		;
}
