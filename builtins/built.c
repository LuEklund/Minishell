/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                              :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:49:35 by leklund           #+#    #+#             */
/*   Updated: 2023/03/16 17:17:29 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	echo(t_data *info)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 2;
	if (info->args[i][0] == '-' && info->args[i][1] == 'n')
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
