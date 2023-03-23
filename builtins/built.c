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
// -9223372036854775808
long long	built_exit(t_data *info)
{
	long long	return_val;
	int			sign;

	if (!info->args[1])
		return (0);
	sign = 1;
	return_val = exit_atoi(info, &sign);
//	 printf("recived-NUM[%lld]\n", return_val);
	if (return_val < 0)
	{
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(info->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (return_val);
	}
	if (info->args[2])
	{
		ft_putstr_fd(info->dino, 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (sign == -2)
		return (0);
	return (return_val * sign);
}

int	echo(t_data *info)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 2;
	if (info->args[i] && info->args[i][0] == '-' && info->args[i][1] == 'n')
	{
		while(info->args[i][new_line] == 'n')
			new_line++;
		if (!info->args[i][new_line])
		{
			new_line = 0;
			i++;
		}
	}
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
	{
		// printf("echo\n\r");
		return (echo(info));
	}
	else if (info->built == 2)
	{
		return (change_dir(info));
	}
	else if (info->built == 3)	
	{
		// printf("display_curdir\n\r");
		return (display_curdir());
	}
	else if (info->built == 4)
	{
		return(built_exit(info));
	}
	else if (info->built == 5)
	{
		return (env_unset(info, 0));
	}else if (info->built == 6)
	{
		return (env_export(info, 0));
	}
	else if (info->built == 7)
	{
		// printf("display_env\n\r");
		return (display_env(info, 0));
	}
	return (0);
}
