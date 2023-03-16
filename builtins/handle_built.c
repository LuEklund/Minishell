/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:22:20 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/11 20:58:33 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fake_it(t_data *info)
{
	free_ar(info->args);
	info->args = ft_split("n n", ' ');
	if (!info->args)
		return (ft_putendl_fd("apua", 2));
	info->cmd_to_use = ft_strdup(" "); 
	if (!info->cmd_to_use)
		return (ft_putendl_fd("apua", 2), free_ar(info->args));
	info->built = 0;
	info->check = 0;
}

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

void	bob_the_builtin(t_data *info)
{
	info->check = 1;
	if (info->built == 1 || info->built == 3 || info->built == 7)
		info->check = 0;
	else if (info->built == 6 && !info->args[1])
		info->check = 0;
	else if (info->built == 2 && info->i == 0 && !info->cmds[1])
	{
		change_dir(info);
		info->built_exec = 1;
	}
	else if (info->built == 4 && info->i == 0 && !info->cmds[1])
	{
		info->exit = 1;
		exit(-32);
	}
	else if (info->built == 5 && info->i == 0 && !info->cmds[1])
	{
		unset_env(info, 0);
		info->built_exec = 1;
	}
	else if (info->built == 6 && info->i == 0 && !info->cmds[1])
	{
		env_export(info, 0);
		info->built_exec = 1;
	}
	else
		fake_it(info);
	if (!info->check || info->built_exec)
		return ;
	free_ar(info->args);
	free_ar(info->cmds);
}
