/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:02:14 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/24 12:34:12 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redi	*copy_hd_node(t_redi *hd, int red_n)
{
	t_redi	*new;

	new = malloc(sizeof(t_redi));
	new->next = NULL;
	new->type = 2;
	new->pipe_n = hd->pipe_n;
	new->red_n = red_n;
	new->i = hd->i;
	new->cmd_n = hd->cmd_n;
	new->fd = hd->fd;
	new->file_name = ft_strdup(hd->file_name);
	if (!new->file_name)
		exit(write(2, "memory errawr🦖\n", 15));
	return (new);
}

void	get_hd_file(t_redi *current, int len, int fd)
{
	char	*buffy;

	len = ft_strlen(current->file_name);
	fd = open(current->hd_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		exit(write(2, "temporary file error\n", 21));
	while (1)
	{
		buffy = \
		readline("\033[0;36mhere\033[0m\033[0;32mdino\033[0m\033[0;36mc>\033[0m ");
		if (!buffy)
		{
			close(fd);
			exit (0);
		}
		if (!(ft_strncmp(current->file_name, buffy, len)) \
				&& (buffy[len] == '\n' || buffy[len] == '\0'))
			break ;
		write(fd, buffy, ft_strlen(buffy));
		write(fd, "\n", 1);
		free(buffy);
	}
	close(fd);
	free(buffy);
	exit(0);
}

int	here_doc(t_redi *current, t_data *info, pid_t kiddo)
{
	char	*number;

	find_file(current, info);
	info->hd_n += 1;
	number = ft_itoa(info->hd_n);
	if (!number)
		exit(write(2, "memory errawr🦖\n", 15));
	current->hd_file = ft_strjoin(".dinoshell_heredoc373_tmp", number);
	free(number);
	if (!current->hd_file)
		exit(write(2, "memory errawr🦖\n", 15));
	kiddo = fork();
	if (kiddo)
		parent_signals(info, 0);
	else
	{
		kid_signals(info);
		get_hd_file(current, 37, 37);
	}
	current->fd = open(current->hd_file, O_RDONLY);
	if (current->fd < 0)
		exit(write(2, "temporary file error\n", 21));
	if (info->return_val)
		info->return_val = 1;
	return (info->return_val);
}

int	deal_doc(t_data *info, size_t i, size_t i2, char **pipes)
{
	t_redi	*new;
	t_redi	*current;
	int		check;

	new = malloc(sizeof(t_redi));
	if (!new)
		exit(write(2, "memory errawr🦖\n", 15));
	new->type = 2;
	new->next = NULL;
	new->pipe_n = i;
	new->i = i2 + 1;
	new->cmd_n = info->hd;
	new->used = 0;
	info->cmds = pipes;
	check = here_doc(new, info, 0);
	if (!info->hd_list)
		info->hd_list = new;
	else
	{
		current = info->hd_list;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (check);
}

int	find_hd(char *str, t_data *info, int i, int i2)
{
	char	**pipes;
	int		qts[2];

	qts[0] = 0;
	qts[1] = 0;
	pipes = parse_split(str, '|', info);
	if (!pipes)
		exit(write(2, "memory errawr🦖\n", 15));
	while (pipes[i])
	{
		while (pipes[i][i2])
		{
			if (pipes[i][i2] == '<' && pipes[i][i2 + 1] == '<' \
					&& qts[0] + qts[1] == 0)
			{
				if (deal_doc(info, i, i2, pipes))
					return (free_ar(pipes), 1);
			}
			i2 = quote_check(pipes[i], i2, &qts[0], &qts[1]);
		}
		i2 = 0;
		i += 1;
	}
	return (free_ar(pipes), 0);
}
