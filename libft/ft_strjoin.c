/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:45:59 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/07 18:20:22 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	szcounter9000(char const *s1, char const *s2)
{
	unsigned long	loca;
	unsigned long	loca2;

	loca = 0;
	loca2 = 0;
	while (s1 && s1[loca] != '\0')
		loca++;
	while (s2 && s2[loca2] != '\0')
		loca2++;
	return (loca + loca2);
}

static void	the_conjoiner(char *ans, int *loca, int *loca2, const char *str)
{
	while (str && str[*loca] != '\0')
	{
		ans[*loca2] = str[*loca];
		*loca = *loca + 1;
		*loca2 = *loca2 + 1;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int				loca;
	int				loca2;
	unsigned long	sz;
	char			*ans;

	loca = 0;
	loca2 = 0;
	sz = szcounter9000(s1, s2);
	ans = (char *) malloc ((sz + 1) * sizeof(char));
	if (ans == NULL)
		return (NULL);
	the_conjoiner(ans, &loca, &loca2, s1);
	loca = 0;
	the_conjoiner(ans, &loca, &loca2, s2);
	ans[loca2] = '\0';
	return (ans);
}
