/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:00:10 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/24 12:34:18 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_child(t_data *info, char *str, int y)
{
	char	**no_space;

	info->cmds = parse_split(str, '|', info);
	if (!info->cmds)
		exit(write(2, "memory errawr🦖\n", 15));
	while (info->cmds[y])
		y++;
	if (y > 1)
		return (free_ar(info->cmds), 0);
	no_space = parse_split(info->cmds[0], ' ', info);
	free_ar(info->cmds);
	if (no_space)
		is_built_in(info, no_space[0]);
	if (!no_space || !(info->built == 2 || info->built == 4 || \
	info->built == 5 || info->built == 6))
		return (free_ar(no_space), empty_whelp_list(info), 0);
	info->cmds = parse_split(str, '|', info);
	redirection_parser(info, 0, 0);
	free_ar(info->cmds);
	work_built(info, no_space, 1, 0);
	empty_whelp_list(info);
	free_ar(no_space);
	return (1);
}

void	print_spesh_error(t_error *help, t_data *info)
{
	while (info->buf[help->i] && info->buf[help->i] != ' ')
	{
		write(2, &info->buf[help->i], 1);
		help->i += 1;
	}
}

void	syntax_error(t_data *info)
{
	t_error	*help;

	help = info->error;
	if (!info->buf)
		return (free(help));
	info->return_val = 258;
	ft_putstr_fd(info->dino, 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (help->par < 0 && help->i)
		help->i -= 1;
	if (!info->buf[help->i])
		ft_putstr_fd("newline", 2);
	else if (help->special)
		print_spesh_error(help, info);
	else if (help->amper)
		write(2, "&", 1);
	else
		write(2, &info->buf[help->i], 1);
	if (help->and || help->or || help->out_t || help->in_t)
		write(2, &info->buf[help->i + 1], 1);
	ft_putendl_fd("'", 2);
	free(info->buf);
	free(help);
}

int	work_pipe(t_data *info, char *cmd_chain)
{
	pid_t	kiddo;

	info->redi_list = NULL;
	info->all_red_n = 0;
	if (check_if_child(info, cmd_chain, 0))
		return (info->return_val);
	kiddo = fork();
	if (kiddo < 0)
		exit(write(2, "child process error\n", 19));
	if (kiddo)
	{
		parent_signals(info, 1);
		close_pipeline(info);
		return (info->return_val);
	}
	kid_signals(info);
	handle_pipe(info, cmd_chain);
	if (info->return_val != 127 && info->return_val != 6 \
			&& info->return_val != 10 && info->return_val != 11)
		info->return_val = WEXITSTATUS(info->return_val);
	exit(info->return_val);
}

void	handle_buf(t_data *info)
{
	int		i;

	i = 0;
	info->history_buf = ft_strdup(info->buf);
	if (!info->history_buf)
		exit(write(2, "memory errawr🦖\n", 15));
	if (error_parser(info))
		return (syntax_error(info));
	free(info->error);
	info->hd_list = NULL;
	go_through_list(info);
	info->cmd_n = 0;
	if (!info->hd_error)
		traveler(info->trinary_tree, info);
	empty_doc(info->hd_list);
	empty_tree(info->trinary_tree);
	free(info->buf);
}
