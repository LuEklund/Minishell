/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:47:06 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/21 20:16:17 by nlonka           ###   ########.fr       */
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
}

//			   //
// REMOVE THIS //
//			   //

void	close_pipeline(t_data *info)
{
	size_t	i;

	i = 0;
	while (i != info->pipe_amount)
	{
		close(info->pipe[i]);
		i++;
	}
}
