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

void	get_hd_file(t_redi *current, t_data *info)
{
	int		fd;
	int		len;
	char	*buffy;

	(void)info;
	len = ft_strlen(current->file_name);
	fd = open(current->hd_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		exit(write(2, "temporary file error\n", 21));
	while (1)
	{
		buffy = readline("\033[0;36mhere\033[0m\033[0;32mdino\033[0m\033[0;36mc>\033[0m ");
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
		get_hd_file(current, info);
	}
	if (info->return_val)
		return (1);
	current->fd = open(current->hd_file, O_RDONLY);
	if (current->fd < 0)
		exit(write(2, "temporary file error\n", 21));
	return (0);
}

int	deal_doc(t_data *info, size_t *i, char **pipes)
{
	t_redi	*new;
	t_redi	*current;

	new = malloc(sizeof(t_redi));
	if (!new)
		exit(write(2, "memory errawr🦖\n", 15));
	new->type = 2;
	new->pipe_n = i[0];
	new->i = i[1] + 1; ///or not + 1
	new->cmd_n = info->hd;
	new->used = 0;
	info->cmds = pipes;
	if (here_doc(new, info, 0))
		return (free(new), 1);
	if (!info->hd_list)
		info->hd_list = new;
	else
	{
		current = info->hd_list;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (0);
}

int	find_hd(t_cond *current, char *str, t_data *info)
{
	char	**pipes;
	int		qts[2];
	size_t	i[2];

	(void)current; /////
	qts[0] = 0;
	qts[1] = 0;
	i[0] = 0;
	i[1] = 0;
//	printf("whole str here is '%s'\n", str);
	pipes = parse_split(str, '|', info);
//	printf("cmds array:\n");
//	print_ar(pipes); /////
	if (!pipes)
		exit(write(2, "memory errawr🦖\n", 15));
	while (pipes[i[0]])
	{
		while (pipes[i[0]][i[1]])
		{
			if (pipes[i[0]][i[1]] == '<' && pipes[i[0]][i[1] + 1] == '<' \
					&& qts[0] + qts[1] == 0)
			{
				if (deal_doc(info, i, pipes))
					return (free_ar(pipes), 1);
			}
			i[1] = quote_check(pipes[i[0]], i[1], &qts[0], &qts[1]);
		}
		i[1] = 0;
		i[0] += 1;
	}
	return (free_ar(pipes), 0);
}
