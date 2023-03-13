/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:02:14 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/08 18:56:59 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_hd_file(t_redi *current, t_data *info)
{
	int		fd;
	int		len;
	char	*buffy;

	(void)info;
	len = ft_strlen(current->file_name);
	fd = open(".dinoshell_heredoc373_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		exit(write(2, "temporary file error\n", 21));
	while (1)
	{
		write(1, "\033[0;36mhere\033[0m\033[0;32mdino\033[0m\033[0;36mc>\033[0m ", 44);
		buffy = get_next_line(0);
		if (!buffy)
			exit(37);
		if (!(ft_strncmp(current->file_name, buffy, len)) \
				&& (buffy[len] == '\n' || buffy[len] == '\0'))
			break ;
		write(fd, buffy, ft_strlen(buffy));
		free(buffy);
	}
	free(buffy);
	exit(0);
}
