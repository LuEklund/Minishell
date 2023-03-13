/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:00:10 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/08 18:57:04 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(t_data *info, int var)
{
	info->return_val = 258;
	ft_putstr_fd(info->dino, 2);
	if (var)
		ft_putendl_fd("syntax error near unexpected token `||'", 2);
	else
	{
		empty_redi_list(info);
		free(info->cmds);
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
	}
}

void	handle_buf(t_data *info)
{
	pid_t	kiddo;

	info->cmds = parse_split(info->buf, '|', info);
	if (!info->cmds || !info->cmds[0])
		return (syntax_error(info, 1));
	if (init_pipes(info) < 0)
		return (syntax_error(info, 0));
	find_the_paths(info);
	while (info->cmds[info->i] && !info->check)
	{
		arguing(info);
		if (info->check || info->exit)
			break ;
		kiddo = fork();
		if (kiddo < 0)
			return (ft_putendl_fd("stillbirth?????\n", 2));
		if (kiddo == 0)
			the_kindergarden(info);
		free_commands(info);
		info->i += 1;
	}
	close_pipeline(info);	
	while ((wait(&info->return_val)) > 0)
		;
	empty_redi_list(info);
}
