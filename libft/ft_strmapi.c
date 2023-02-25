/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:05:56 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/07 18:03:46 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*ans;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	ans = (char *) malloc ((i + 1) * sizeof(char));
	if (ans == NULL)
		return (NULL);
	i = 0;
	while (s && s[i] != '\0')
	{
		ans[i] = f(i, s[i]);
		i++;
	}
	ans[i] = '\0';
	return (ans);
}
