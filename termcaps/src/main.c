/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:36:44 by nlonka            #+#    #+#             */
/*   Updated: 2023/02/16 17:29:49 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	go_raw(void)
{
	struct termios	tc;

	tcgetattr(STDIN_FILENO, &tc);
	tc.c_lflag &= ~(ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tc);
}

int main(void)
{
	char	*buf;

	go_raw();
	buf = NULL;	
	while (ft_strncmp(buf, "exit", 5))
	{
		if (buf)
			free(buf);
		buf = readline("\033[0;32mDinoshell>\033[0m ");
	}
	if (buf)
		free(buf);
	printf("\033[0;95mexit\033[0m 🦕\n");
	return (0);
}
