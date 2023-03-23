/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:35:13 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/23 15:00:42 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_input_parser(const char *str, t_split *he, int var)
{
	int	len;

	len = he->expand_type - 2;
//	if (!var)
//		printf("1the len is %d at %c%d\n", len, str[len + he->i3], he->i3);
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
//	if (!var)
//		printf("2the len is %d at %c%d\n", len, str[he->i3], he->i3);
	return (1);
}
