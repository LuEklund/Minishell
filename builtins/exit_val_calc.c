/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_val_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:56:51 by leklund           #+#    #+#             */
/*   Updated: 2023/03/23 11:35:54 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int	pre_checker(const char *str, unsigned long int *i, int *sign)
{
	*i = 0;
	while ((str[*i] > 6 && str[*i] < 14) || str[*i] == ' ')
	{
		i++;
		if (str[*i] == '\0')
			return (-1);
	}
	if (str[*i] == '-')
		*sign = -1;
	if (str[*i] == '-' || str[*i] == '+')
		i++;
	return (0);
}

long long	exit_atoi(t_data *info, int *sign)
{
	const char			*str;
	unsigned long long	n;
	unsigned long int	i;

	str = info->args[1];
	n = 0;
	if (pre_checker(str, &i, sign))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
		if ((long long)(n - 1) < 0)
			return (-1);
		else if ((long long)n < 0 && *sign == 1)
			return (-1);
	}
	if (str[i] != '\0')
		return (-1);
	if (n == 9223372036854775808ULL)
	{
		*sign = -2;
		return (2);
	}
	return (n);
}
