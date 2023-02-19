/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 12:55:17 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/09 16:15:26 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != (unsigned char)c)
		i++;
	if (str[i] == '\0' && (unsigned char)c != '\0')
		return (0);
	str = str + i;
	return ((char *)str);
}
