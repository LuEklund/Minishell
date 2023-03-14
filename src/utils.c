/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:47:06 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/11 20:58:24 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//			   //
// REMOVE THIS //
//			   //

void	print_ar(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
	{
		printf("'%s'\n", ar[i]);
		i++;
	}
	///IIIIIIIIIIIIIII DELEEETE MEEEEEE
}

//			   //
// REMOVE THIS //
//			   //


void	free_ar(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}

void	get_outed(t_data info)
{
	close_pipeline(&info);
	get_duped(info.safe_in, info.safe_out);
	close(info.fd_in);
	close(info.fd_out);
	unlink(".dinoshell_heredoc373_tmp");
	tcsetattr(0, TCSANOW, &info.old_term);
}

void	empty_redi_list(t_data *info)
{
	t_redi	*latter;
	t_redi	*current;

	current = info->redi_list;
	while (current)
	{
		close(current->fd);
		if (current->file_name)
			free(current->file_name);
		latter = current;
		current = current->next;
		free(latter);
	}
}

void	empty_wild_list(t_data *info)
{
	t_wild	*latter;
	t_wild	*current;

	current = info->wild_list;
	while (current)
	{
		latter = current;
		current = current->next;
		free(latter);
	}
}

void	empty_args_list(t_data *info)
{
	t_args	*latter;
	t_args	*current;

	current = info->args_list;
	while (current)
	{
		latter = current;
		free(current->arg);
		current = current->next;
		free(latter);
	}
}
