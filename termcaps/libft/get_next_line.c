/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:43:24 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/22 18:15:07 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buflist	*new_buf(void)
{
	t_buflist	*node;

	node = malloc(sizeof(t_buflist));
	if (!node)
		return (NULL);
	node->buffy = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!node->buffy)
	{
		free(node);
		return (NULL);
	}
	(node->buffy)[0] = '\0';
	node->next = NULL;
	return (node);
}

t_fdlist	*new_fdlist(int fd)
{
	t_fdlist	*node;

	node = malloc(sizeof(t_fdlist));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->begin = new_buf();
	if (!node->begin)
	{
		free(node);
		return (NULL);
	}
	node->next_fd = NULL;
	return (node);
}

t_fdlist	*fdder(int fd, t_fdlist **beginning)
{
	t_fdlist	*current;

	if (!(*beginning))
		*beginning = new_fdlist(fd);
	if (!(*beginning))
		return (NULL);
	current = *beginning;
	while (current->next_fd != NULL && current->fd != fd)
		current = current->next_fd;
	if (current->fd == fd)
		return (current);
	current->next_fd = new_fdlist(fd);
	if (!current->next_fd)
		return (NULL);
	return (current->next_fd);
}

int	read_file(int fd, t_buflist *beginning, t_buflist *current)
{
	long	have_read;

	if (current && find_line(current->buffy))
		return (1);
	else if (current && (current->buffy[0]))
	{
		current->next = new_buf();
		current = current->next;
	}
	while (1)
	{
		have_read = read(fd, current->buffy, BUFFER_SIZE);
		if (have_read <= 0)
			break ;
		current->buffy[have_read] = '\0';
		if (find_line(current->buffy))
			return (1);
		current->next = new_buf();
		current = current->next;
	}
	if (!(beginning->buffy[0]))
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{	
	static t_fdlist	*ptr_fd;
	t_fdlist		*current_fd;
	t_buflist		*current_buf;
	int				check;
	char			*ans;

	if (fd < 0 || fd > 999 || BUFFER_SIZE < 1)
		return (NULL);
	current_fd = fdder(fd, &ptr_fd);
	if (!current_fd)
		return (NULL);
	current_buf = current_fd->begin;
	check = read_file(fd, current_buf, current_buf);
	if (!check)
		ans = NULL;
	else
		ans = answerer(current_buf, 0, 0);
	clean_buf(current_buf, current_fd);
	ptr_fd = clean_fd(ptr_fd, current_fd);
	return (ans);
}
