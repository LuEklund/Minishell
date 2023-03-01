/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:22:20 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/01 14:18:03 by nlonka           ###   ########.fr       */
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

void	bob_the_builtin(t_data *info)
{
	if (info->built == 1 || info->built == 3 || info->built == 7)
		info->check = 0;
	else if (info->built == 6 && !info->args[1])
		info->check = 0;
	else if (info->built == 2 && info->i == 0 && !info->cmds[1])
		change_dir(info->args[1]);
	else if (info->built == 4 && info->i == 0 && !info->cmds[1])
		info->exit = 1;
	else if (info->built == 5 && info->i == 0 && !info->cmds[1])
		unset_env(info, info->args[1]);
	else if (info->built == 6 && info->i == 0 && !info->cmds[1])
		env_export(info, info->args[1]);
	else
		fake_it(info);
	if (!info->check)
		return ;
	free_ar(info->args);
	free_ar(info->cmds);
}
