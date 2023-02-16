/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:40:54 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/10 16:44:46 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t s)
{
	void	*ptr;
	size_t	i;
	size_t	m_amount;

	i = 0;
	m_amount = n * s;
	if (s != 0)
	{
		if (m_amount / s != n)
			return (NULL);
	}
	ptr = (void *) malloc(m_amount);
	if (!ptr)
		return (NULL);
	while (i < (n * s))
	{
		((char *)ptr)[i] = '\0';
		i++;
	}
	return (ptr);
}
