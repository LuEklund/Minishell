/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:32:03 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/11 17:59:46 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_file(t_redi *current, t_data *info)
{
	int i;
	int	len;
	int	i2;

	i2 = 0;
	i = current->i + 1;
	while (info->cmds[current->pipe_n][i] && info->cmds[current->pipe_n][i] == ' ')
		i++;
	len = i;
	while (info->cmds[current->pipe_n][len] && info->cmds[current->pipe_n][len] != ' ')
		len++;
	len -= i;
	current->file_name = malloc(sizeof(char) * (len + 1));
	while (info->cmds[current->pipe_n][i] && info->cmds[current->pipe_n][i] != ' ')
	{
		current->file_name[i2] = info->cmds[current->pipe_n][i];
		i++;
		i2++;
	}
	current->file_name[i2] = '\0';
	return (0);
}

int	open_infile(t_redi *current, t_data *info)
{
	if (!info->cmds[current->pipe_n][current->i + 1])
		return (1);
	find_file(current, info);
	if (!access(current->file_name, F_OK) && access(current->file_name, R_OK) < 0)
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
		return (1);
	if (current->type == -2 && !info->cmds[current->pipe_n][current->i + 2])
		return (1);
	find_file(current, info);
	if (!access(current->file_name, F_OK) && access(current->file_name, W_OK) < 0)
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
	find_file(current, info);
	info->hd = 1;
	get_hd_file(current, info);
	current->fd = open(".dinoshell_heredoc373_tmp", O_RDONLY);
	if (current->fd < 0)
		exit(write(2, "temporary file error\n", 21));
	return (0);
}

int	open_files(t_data *info)
{
	t_redi	*current;

	info->hd = 0;
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
			return (1);
		current = current->next;
	}
	return (0);
}
