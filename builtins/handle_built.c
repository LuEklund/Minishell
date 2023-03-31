/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:22:20 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/23 11:39:45 by nlonka           ###   ########.fr       */
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
