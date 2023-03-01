/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:14:40 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/10 12:14:36 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*ans;
	size_t	size;

	if (str && ft_strlen(str) < len)
		len = ft_strlen(str);
	ans = (char *) malloc ((len + 1) * sizeof(char));
	if (ans == NULL)
		return (NULL);
	if (str && start >= ft_strlen(str))
	{
		ans[0] = '\0';
		return (ans);
	}
	size = 0;
	while (str && str[start] != '\0' && size != len)
	{
		ans[size] = str[start];
		size++;
		start++;
	}
	ans[size] = '\0';
	return (ans);
}
