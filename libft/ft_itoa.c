/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:20:25 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/08 14:32:36 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*the_big_malloc_300(int n, int *h)
{
	char	*ans;

	*h = 1;
	if (n < 0)
		*h = *h + 1;
	while (n / 10)
	{
		n = n / 10;
		*h = *h + 1;
	}
	ans = (char *) malloc ((*h + 1) * sizeof(char));
	return (ans);
}

static long int	the_powering(int h, int c)
{
	long int	ans;

	ans = 1;
	while (h > 1)
	{
		ans = ans * 10;
		h--;
	}
	if (c < 0)
		ans = ans / 10;
	return (ans);
}

static void	negs(char *ans, int i, int h, int n)
{
	long int	n2;

	ans[i] = '-';
	i++;
	n2 = -(long int)n;
	while (the_powering(h, -1) > 0)
	{
		ans[i] = n2 / (the_powering(h, -1)) % 10 + '0';
		h--;
		i++;
	}
	ans[i] = '\0';
}

char	*ft_itoa(int n)
{
	char	*ans;
	int		i;
	int		h;

	i = 0;
	ans = the_big_malloc_300(n, &h);
	if (ans == NULL)
		return (NULL);
	if (n < 0)
		negs(ans, i, h, n);
	else
	{
		while (h > 0)
		{
			ans[i] = n / (the_powering(h, 1)) % 10 + '0';
			h--;
			i++;
		}
		ans[i] = '\0';
	}
	return (ans);
}
