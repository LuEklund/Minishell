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
#include <ctype.h>
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
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 4;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		die("tcsetattr");
}


int main() {
	char c = '\0';

	// char	*buf;


	enableRawMode();
	// buf = NULL;	
	// buf = readline("\033[0;32mDinoshell>\033[0m ");
	while (1) {
	c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1)
		die("read");
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
    if (c == 'q') break;
  }
	// if (buf)
		// free(buf);
	printf("\033[0;95mexit\033[0m 🦕\n");
	return 0;
}

// int main(void)
// {
// 	char	*buf;

// 	go_raw();
// 	buf = NULL;	
// 	while (ft_strncmp(buf, "exit", 5))
// 	{
// 		if (buf)
// 			free(buf);
// 		buf = readline("\033[0;32mDinoshell>\033[0m ");
// 	}
// 	if (buf)
// 		free(buf);
// 	printf("\033[0;95mexit\033[0m 🦕\n");
// 	return (0);
// }