/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_abort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:04:06 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/22 14:07:05 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

int main()
{
	char	buffer[120];

	fgets(buffer, sizeof buffer, stdin);
	strcat("mutsis", buffer);
	return (0);
}
