/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:35:13 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/10 17:17:06 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_input_parser(const char *str, t_split *he, int var)
{
	int	len;

	len = he->expand_type - 2;
//	ft_putnbr_fd(len, 2);
//	ft_putstr_fd("\n", 2);

	while (str[he->i3 + len] && str[he->i3 + len] != ' ' \
			&& he->sq + he->q == 0)
	{
	//	printf("%c%d\n", str[he->i3 + len], he->i3 + len);
		len++;
	}
	if (he->sq + he->q != 0)
		return (0);
	if (var)
	{
		while (str[he->i3 + len] == he->c)
			len++;
	}
	he->i3 += len;
//	ft_putnbr_fd(len, 2);
//	ft_putstr_fd("\n", 2);
	return (1);
}
