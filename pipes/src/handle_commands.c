/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:02:20 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/21 16:47:48 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in_bob(void)
{
	return ;
}

int	init_pipes(t_data *info)
{
	int	i;

	i = 0;
	info->cmd_amount = 0;
	while (info->cmds[info->cmd_amount])
		info->cmd_amount += 1;
	info->pipe_amount = (info->cmd_amount - 1) * 2;
	info->pipe = malloc(sizeof(int) * info->pipe_amount);
	while (i < info->cmd_amount)
	{
		if (pipe(info->pipe + 2 * i) < 0)
			return (-1);
		i++;
	}
	return (0);
}

void	commander(t_data *info)
{
	if (!info->built_in)
		
}

void	voi_parse(t_data *info)
{
	//sadly enough i do have to change that name later on :(...
	if (init_pipes(info) < 0)
		return (ft_putendl_fd("pipes fucked up man..\n", 2));
	while (info->cmds[info->i])
	{
		is_built_in(info);
		commander(info);
		info->i += 1;
	}
}

void	handle_buf(t_data *info)
{
	info->i = 0;
	info->check = 0;
	info->fd_in = 0;
	info->fd_out = 1;
	//CHECK FOR THINGS LIKE ECHO "HII | FFF"
	info->cmds = ft_split(info->buf, '|');
	if (!info->cmds)
		exit(write(2, "apua\n", 5));
	//sanitize white spaces
	//check files & redirections
	voi_parse(info);
	while (wait(NULL) > 0)
		;
}
