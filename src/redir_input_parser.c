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

int	redir_input_parser(const char *str, t_split *he)
{
	int	len;

	len = he->expand_type - 1;
//	ft_putnbr_fd(len, 2);
//	ft_putstr_fd("\n", 2);
	if (str[he->i3 + len] == ' ')
	{
		while (str[he->i3 + len] && str[he->i3 + len] == ' ' \
				&& he->sq + he->q == 0)
			len = quote_check(str, len + he->i3, &he->q, &he->sq) - he->i3;
		while (str[he->i3 + len] && str[he->i3 + len] != ' ' \
				&& he->sq + he->q == 0)
			len = quote_check(str, len + he->i3, &he->q, &he->sq) - he->i3;
	}
	else
	{
		while (str[he->i3 + len] && str[he->i3 + len] != ' ' \
				&& he->sq + he->q == 0)
			len++;
	}
	if (he->sq + he->q != 0)
		return (0);
	he->i3 += len;
	while (str[he->i3] == he->c)
		he->i3 += 1;
//	ft_putnbr_fd(len, 2);
//	ft_putstr_fd("\n", 2);
	return (1);
}
