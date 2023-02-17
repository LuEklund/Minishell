/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:50:48 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/11 16:03:46 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	the_sign(int c)
{
	if (c == -1)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	long int	n;
	long int	i;
	int			c;

	c = 1;
	i = 0;
	n = 0;
	while ((str[i] > 6 && str[i] < 14) || str[i] == ' ')
	{
		i++;
		if (str[i] == '\0')
			return (0);
	}
	if (str[i] == '-')
		c = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
		if (n < 0)
			return (the_sign(c));
	}
	return (n * c);
}	
