/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:47:06 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/09 09:45:25 by nlonka           ###   ########.fr       */
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
		printf("%s\n", ar[i]);
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
	unlink(".dinoshell_heredoc373_tmp");
	get_duped(info.safe_in, info.safe_out);
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
