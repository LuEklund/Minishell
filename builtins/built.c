/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                              :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:49:35 by leklund           #+#    #+#             */
/*   Updated: 2023/03/23 15:00:36 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	print_exit(int var)
{
	if (var)
		ft_putendl_fd("\033[0;95mexit\033[0m 🦕", 2);
}

long long	built_exit(t_data *info, long long return_val, int sign, int var)
{
	if (!info->args[1])
		return (print_exit(var), 0);
	return_val = exit_atoi(info, &sign);
	if (return_val < 0)
	{
		print_exit(var);
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(info->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (return_val);
	}
	if (info->args[2])
	{
		print_exit(var);
		info->exit = 0;
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	print_exit(var);
	if (sign == -2)
		return (0);
	return (return_val * sign);
}

int	n_skipper(t_data *info, int *i, int new_line)
{
	int	index;

	index = 0;
	while (info->args[*i] && info->args[*i][0] == '-'
		&& info->args[*i][1] == 'n')
	{
		index = 2;
		while (info->args[*i][index] == 'n')
			index++;
		if (info->args[*i][index])
			return (new_line);
		new_line = 0;
		(*i)++;
	}
	return (new_line);
}

int	echo(t_data *info)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 2;
	new_line = n_skipper(info, &i, new_line);
	while (info->args[i])
	{
		printf("%s", info->args[i]);
		i++;
		if (info->args[i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (0);
}

int	execute_built(t_data *info)
{
	if (info->built == 1)
		return (echo(info));
	else if (info->built == 2)
		return (change_dir(info));
	else if (info->built == 3)
		return (display_curdir(info));
	else if (info->built == 4)
		return (built_exit(info, 0, 1, 0));
	else if (info->built == 5)
		return (env_unset(info, 0));
	else if (info->built == 6)
		return (env_export(info, 0));
	else if (info->built == 7)
		return (display_env(info, 0));
	return (0);
}
