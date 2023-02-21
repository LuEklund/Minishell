/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:21:32 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/21 16:47:41 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_built_in(t_data *info)
{
	info->built = 0;
	if (!ft_strncmp("echo", info->work_cmd, 4))
		info->built = 1;
	else if (!ft_strncmp("cd", info->work_cmd, 2))
		info->built = 2;
	else if (!ft_strncmp("pwd", info->work_cmd, 3))
		info->built = 3;
	else if (!ft_strncmp("exit", info->work_cmd, 4))
		info->built = 4;
	else if (!ft_strncmp("unset", info->work_cmd, 5))
		info->built = 5;
	else if (!ft_strncmp("export", info->work_cmd, 6))
		info->built = 6;
	else if (!ft_strncmp("env", info->work_cmd, 3))
		info->built = 7;
}

size_t	when_does_it_end(char *str, size_t start)
{
	while (str[start] != '\0' && str[start] != '|')
		start++;
	return (start);
}
