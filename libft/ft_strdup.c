/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:01:56 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/07 15:32:47 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*ans;

	i = 0;
	while (str[i] != '\0')
		i++;
	ans = (char *) malloc ((i + 1) * sizeof(char));
	if (ans == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		ans[i] = str[i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}
