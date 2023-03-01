/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:57:41 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/10 11:35:38 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	src_len;
	size_t	dst_len;

	dst_len = 0;
	src_len = ft_strlen(src);
	if (n == 0)
		return (src_len);
	while (*dst && n > 0)
	{
		dst_len++;
		dst++;
		n--;
	}
	while (*src && n > 1)
	{
		*dst = *src;
		dst++;
		src++;
		n--;
	}
	if (n == 1 || *src == 0)
		*dst = '\0';
	return (dst_len + src_len);
}
