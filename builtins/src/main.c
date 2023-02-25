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
struct termios orig_termios;


void die(const char *s) {
  perror(s);
  exit(1);
}

void disableRawMode() {
	printf("\033[0;100mDISABLE-RAW-MODE\033[0m \n");
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
		die("tcetattr");
}

void	enableRawMode(void)
{
	struct termios	raw;

	 if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
	 	die("tcgetattr");
	atexit(disableRawMode);
	raw = orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ICANON | IEXTEN | ISIG);

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		die("tcsetattr");
}

int	check_input(char *in_str)
{
	if (!ft_strncmp(in_str, "exit", 5))
		return (0);
	else if (!ft_strncmp(in_str, "pwd", 3))
		return (display_curdir());
	else if (!ft_strncmp(in_str, "cd", 2))
		return (change_dir(in_str));
	else if (!ft_strncmp(in_str, "env", 3))
		return (get_env());
	else if (!ft_strncmp(in_str, "export", 6))
		return (env_export("MY_VAR=Hello, World!"));
	else if (!ft_strncmp(in_str, "unset", 5))
		return (unset_env("MY_VAR"));
	else if (!ft_strncmp(in_str, "echo", 4))
		return (echo("echo test", 1));
	return (1);
}


int	main(void)
{
	char	*buf;
	// char	c;

	enableRawMode();
	buf = NULL;	
	while (1)
	{
		if (buf)
			free(buf);
		buf = readline("\033[0;32mDinoshell>\033[0m ");
		if (!check_input(buf))
			break ;
		if (!ft_strncmp(buf, "exit", 5))
			break ;
	}
	if (buf)
		free(buf);
	printf("\033[0;95mexit\033[0m 🦕\n");
	return 0;
}
