/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:25:39 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/29 17:25:43 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	free_ar(info.envs);
	tcsetattr(info.fd_in, TCSAFLUSH, &info.old_term);
}

int	redir_input_parser(const char *str, t_split *he, int var)
{
	int	len;

	len = he->expand_type - 2;
	while (str[he->i3 + len] && str[he->i3 + len] != ' ' \
			&& he->sq + he->q == 0)
		len++;
	if (he->sq + he->q != 0)
		return (0);
	if (var)
	{
		while (str[he->i3 + len] == he->c)
			len++;
	}
	he->i3 += len;
	return (1);
}
