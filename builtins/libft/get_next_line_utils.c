/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:51:54 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/22 18:16:19 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_line(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

long	size_counter(t_buflist *current)
{
	long	i;
	long	count;

	count = 0;
	i = 0;
	while (current)
	{
		while (current->buffy[i])
		{
			if (current->buffy[i] == '\n')
				return (count + 1);
			i++;
			count++;
		}
		count++;
		current = current->next;
		i = 0;
	}
	return (count);
}

void	clean_buf(t_buflist *c_buf, t_fdlist *c_fd)
{
	t_buflist	*help;
	int			i;
	int			i2;

	i = 0;
	i2 = 0;
	while (c_buf->next)
	{
		help = c_buf->next;
		free(c_buf->buffy);
		free(c_buf);
		c_fd->begin = help;
		c_buf = help;
	}
	while (c_buf->buffy[i] && c_buf->buffy[i] != '\n')
		i++;
	if (c_buf->buffy[i])
		i++;
	while (c_buf->buffy[i])
	{
		c_buf->buffy[i2] = c_buf->buffy[i];
		i2++;
		i++;
	}
	c_buf->buffy[i2] = '\0';
}	

t_fdlist	*clean_fd(t_fdlist *ptr_fd, t_fdlist *c_fd)
{
	if (!((c_fd->begin->buffy)[0]))
	{
		free(c_fd->begin->buffy);
		free(c_fd->begin);
		if (ptr_fd == c_fd)
			ptr_fd = ptr_fd->next_fd;
		else
		{
			while (ptr_fd->next_fd && ptr_fd->next_fd != c_fd)
				ptr_fd = ptr_fd->next_fd;
			if (ptr_fd->next_fd)
				ptr_fd->next_fd = ptr_fd->next_fd->next_fd;
		}	
		free(c_fd);
	}
	return (ptr_fd);
}

char	*answerer(t_buflist *current, int i, int i2)
{
	long	size;
	char	*ans;

	size = size_counter(current);
	ans = malloc(sizeof(char) * (size + 1));
	if (!ans)
		return (NULL);
	while (current)
	{
		while (current->buffy[i])
		{
			ans[i2] = current->buffy[i];
			i++;
			i2++;
			if (current->buffy[i - 1] == '\n')
				break ;
		}
		i = 0;
		current = current->next;
	}
	ans[i2] = '\0';
	return (ans);
}
