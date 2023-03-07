/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:21:16 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/07 20:24:47 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_file(t_redi *current, t_data *info)
{
	int i;
	int	len;

	i = current->i + 1;
	while (info->cmds[current->pipe_n][i] != ' ')
		i++;
	i++;
	len = i;
	while (info->cmds[current->pipe_n][len] && info->cmds[current->pipe_n][len] != ' ')
		len++;
	len -= i;
	current->file_name = malloc(sizeof(char) * (len + 1));
	while (info->cmds[current->pipe_n][i] && info->cmds[current->pipe_n][i] != ' ')
	{
		current->file_name[i - (current->i + 2)] = info->cmds[current->pipe_n][i];
		i++;
	}
	current->file_name[i - (current->i + 1)] = '\0';
	return (0);
}

int	open_infile(t_redi *current, t_data *info)
{
	if (!info->cmds[current->pipe_n][current->i + 1])
		return (-1);
	find_file(current, info);
	if (access(current->file_name, R_OK) < 0)
		return (ft_putstr_fd(info->dino, 2), ft_putstr_fd(current->file_name, 2) \
			, ft_putendl_fd(": Permission denied", 2), 0);
	current->fd = open(current->file_name, O_RDONLY);
	if (current->fd < 0)
		return (ft_putstr_fd(info->dino, 2), ft_putstr_fd(current->file_name, 2) \
			, ft_putendl_fd(": No such file or directory", 2), 0);
	return (0);
}

int	open_outfile(t_redi *current, t_data *info)
{
	if (!info->cmds[current->pipe_n][current->i + 1])
		return (-1);
	if (current->type == -2 && !info->cmds[current->pipe_n][current->i + 2])
		return (-1);
	find_file(current, info);
	if (access(current->file_name, W_OK) < 0)
		return (ft_putstr_fd(info->dino, 2), ft_putstr_fd(current->file_name, 2) \
			, ft_putendl_fd(": Permission denied", 2), 0);
	if (current->type == -1)
		current->fd = open(current->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		current->fd = open(current->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);

	return (0);
}

int	here_doc(t_redi *current, t_data *info)
{
	(void)info;
	(void)current;
	return (0);
}

int	continue_redir(t_data *info)
{
	t_redi	*current;

	if (!info->all_red_n)
		return (0);
	current = info->redi_list;
	while (current)
	{
		if (current->type == 1)
			info->check2 = open_infile(current, info);
		else if (current->type == 2)
			info->check2 = here_doc(current, info);
		else
			info->check2 = open_outfile(current, info);
		if (info->check2)
			return (-1);
		current = current->next;
	}
	return (0);
}
