/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:22:20 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/21 13:14:10 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	work_built(t_data *info, char **args)
{
	info->args = args;
	if (info->built == 2)
		info->return_val = change_dir(info);
	else if (info->built == 4)
	{
		info->exit = 1;
		info->return_val = built_exit(info);
	}
	else if (info->built == 5)
		info->return_val = env_unset(info, NULL);
	else if (info->built == 6)
		info->return_val = env_export(info, NULL);
}

void	fake_it(t_data *info)
{
	/////probs not necessary
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

void	is_built_in(t_data *info, char *arg)
{
	info->built = 0;
	info->check = 0;
	if (!ft_strncmp("echo", arg, 5))
		info->built = 1;
	else if (!ft_strncmp("cd", arg, 3))
		info->built = 2;
	else if (!ft_strncmp("pwd", arg, 4))
		info->built = 3;
	else if (!ft_strncmp("exit", arg, 5))
		info->built = 4;
	else if (!ft_strncmp("unset", arg, 6))
		info->built = 5;
	else if (!ft_strncmp("export", arg, 7))
		info->built = 6;
	else if (!ft_strncmp("env", arg, 4))
		info->built = 7;
}

int	bob_the_builtin(t_data *info)
{
	info->check = 0;
	if (info->built == 1 || info->built == 3 || info->built == 7)
		;
	else if (info->built == 6 && !info->args[1])
		;
	else if (info->built == 2 && info->i == 0 && !info->cmds[1])
		info->built_exec = 1;
	else if (info->built == 4 && info->i == 0 && !info->cmds[1])
		exit (69);
	else if (info->built == 5 && info->i == 0 && !info->cmds[1])
		info->built_exec = 1;
	else if (info->built == 6 && info->i == 0 && !info->cmds[1])
		info->built_exec = 1;
//	else
//		fake_it(info);
	return (1);
}
