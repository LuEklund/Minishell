/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:19:58 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/09 17:21:59 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t l)
{
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	if (l == 0 || !*haystack)
		return (NULL);
	while (haystack[i] != '\0' && i < l)
	{
		while (haystack[i] == needle[i2] && i < l)
		{
			i++;
			i2++;
			if (needle[i2] == '\0')
				return ((char *)(haystack + i - i2));
		}
		if (i2 != 0)
			i = i - i2 + 1;
		else
			i++;
		i2 = 0;
	}
	return (NULL);
}
