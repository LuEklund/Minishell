/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:00:10 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/21 13:05:22 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(t_data *info)
{
	t_error	*help;

	help = info->error;
	if (!info->buf)
		return ;
	info->return_val = 258;
//	printf("at index %zu\n:", help->i);
	ft_putstr_fd(info->dino, 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (!info->buf[help->i])
		ft_putstr_fd("newline", 2);
	else
		write(2, &info->buf[help->i], 1);	
	if (help->and || help->or || help->out_t || help->in_t)
		write(2, &info->buf[help->i + 1], 1);
	ft_putendl_fd("'", 2);
	free(info->buf);
	free(help);
}

int	handle_pipe(t_data *info, char *cmd_str)
{
	info->cmds = parse_split(cmd_str, '|', info);
//	printf("1cmd here is '%s'\n", cmd_str);
	if (init_pipes(info) < 0)
		exit (2);
	info->envs = retrieve_env();
//	printf("2cmd here is '%s'\n", cmd_str);
	find_the_paths(info);
	while (info->cmds[info->i])
	{
		if (arguing(info))
		{
			info->i += 1;
			continue ;
		}
		if (info->exit)
			break ;
		info->kiddo[info->i] = fork();
		if (info->kiddo[info->i] < 0)
			exit(write(2, "forking errawr🦖\n", 16));	
		if (info->kiddo[info->i] == 0)
			the_kindergarden(info);
		free_commands(info);
		info->i += 1;
	}
//	printf("2.5cmd here is '%s'\n", cmd_str);
	close_pipeline(info);
	info->i = 0;
	while ((waitpid(info->kiddo[info->i], &info->return_val, 0)) > 0)
		info->i += 1;
//	printf("3cmd here is '%s'\n", cmd_str);
	free_ar(info->envs);
	free(info->kiddo);
	empty_redi_list(info);
	return (info->return_val);
}

void	handle_buf(t_data *info)
{
	int		i;
	pid_t	kiddo;

	i = 0;
	info->history_buf = ft_strdup(info->buf);
	if (!info->history_buf)
		exit(write(2, "memory error\n", 13));
	if (error_parser(info))
		return (syntax_error(info));
	free(info->error);
	go_through_list(info);
	kiddo = fork();
	if (kiddo < 0)
		exit(write(2, "child process error\n", 19));
	if (kiddo)
	{
		parent_signals(info);
		close_pipeline(info); //////does it work????
		free(info->buf);
		return ;
	}
	kid_signals(info);
	traveler(info->trinary_tree, info);
	unlink(".dinoshell_heredoc373_tmp");
	exit(info->return_val);
}
