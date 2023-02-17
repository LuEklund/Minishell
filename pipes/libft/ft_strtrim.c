/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:27:00 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/09 13:44:54 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	trim_beg(char const *s1, char const *set, int *beg)
{	
	int	loca;
	int	loca2;

	*beg = 0;
	loca = 0;
	loca2 = 0;
	while ((s1[loca] == set[loca2] || set[loca2] != '\0') && s1[loca] != '\0')
	{
		while (s1[loca] != set[loca2] && set[loca2] != '\0')
			loca2++;
		if (s1[loca] == set[loca2])
		{
			*beg = *beg + 1;
			loca++;
			loca2 = 0;
		}
	}
}

static void	trim_end(char const *s1, char const *set, int *len, int *end)
{
	int	i;
	int	i2;
	int	beg;

	beg = *end;
	*end = *len + 1;
	i = *len;
	i2 = 0;
	while ((s1[i] == set[i2] || set[i2] != '\0') && i != beg)
	{
		while (s1[i] != set[i2] && set[i2] != '\0')
			i2++;
		if (s1[i] == set[i2])
		{
			*end = *end - 1;
			i--;
			i2 = 0;
		}
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		loca;
	char	*ans;
	int		beg;
	int		len;
	int		end;

	loca = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	len = ft_strlen((char *)s1);
	trim_beg(s1, set, &beg);
	end = beg;
	trim_end(s1, set, &len, &end);
	len = len - beg - (len - end);
	ans = (char *) malloc ((len + 1) * sizeof(char));
	if (ans == NULL)
		return (NULL);
	while (beg != end)
	{
		ans[loca] = s1[beg];
		beg++;
		loca++;
	}
	ans[loca] = '\0';
	return (ans);
}
