/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_val_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:56:51 by leklund           #+#    #+#             */
/*   Updated: 2023/03/22 12:56:53 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

// static int	the_sign(int c)
// {
// 	if (c == -1)
// 		return (0);
// 	else
// 		return (-1);
// }

long long	exit_atoi(t_data *info, int *sign)
{
	const char			*str;
	unsigned long long			n;
	unsigned long int	i;

	str = info->args[1];
	i = 0;
	n = 0;
	while ((str[i] > 6 && str[i] < 14) || str[i] == ' ')
	{
		i++;
		if (str[i] == '\0')
			return (-1);
	}
	if (str[i] == '-')
		*sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
		if ((long long)(n - 1) < 0)
		{
			// printf("SMOL-Pos[%lld]\n", n);
			return (-1);
		}
		else if((long long)n < 0 && *sign == 1)
		{
			// printf("SMOL-Neg[%lld]\n", n);
			return (-1);
		}

	}
	if (str[i] != '\0')
	{
		// printf("Aqtual Char[%c], Value[%d]\n", str[i], str[i]);
		return (-1);
	}
	// printf("return-NUM[%llU]\n", n);
	if (n == 9223372036854775808ULL)
	{
		*sign = -2;
		return (2);
	}

	return (n);
}