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

int	childless_piper(t_data *info, int safe_in, int safe_out)
{
	t_redi	*in_node;
	t_redi	*out_node;
	int		in;
	int		out;

	in = safe_in;
	out = safe_out;
	info->i = 0;
	in_node = find_node(info, 0);
	out_node = find_node(info, 1);
	if (in_node)
		in = in_node->fd;
	if (out_node)
		out = out_node->fd;
	if (in < 0 || out < 0)
	{
		close(safe_in);
		close(safe_out);
		return (1);
	}
	info->check = get_duped(in, out);
	return (0);
}

void	work_built(t_data *info, char **args, int safe_in, int safe_out)
{
	safe_in = dup(1);
	safe_out = dup(0);
	if (childless_piper(info, safe_in, safe_out))
	{
		info->return_val = 1;
		return (empty_redi_list(info));
	}
	empty_redi_list(info);
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
	get_duped(safe_in, safe_out);
	close(safe_in);
	close(safe_out);
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
