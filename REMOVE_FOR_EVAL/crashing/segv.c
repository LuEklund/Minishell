/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:55:46 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/22 13:55:50 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main()
{
	char	*str;

	str = 0;
	while (str[2])
		;
	return (0);
}
