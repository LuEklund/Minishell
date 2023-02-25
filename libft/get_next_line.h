/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:59:52 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/21 13:55:41 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buflist
{
	char				*buffy;
	struct s_buflist	*next;

}	t_buflist;

typedef struct s_fdlist
{
	int				fd;
	t_buflist		*begin;	
	struct s_fdlist	*next_fd;
}	t_fdlist;

t_buflist	*new_buf(void);
t_fdlist	*new_fdlist(int fd);
t_fdlist	*fdder(int fd, t_fdlist **beginning);
int			read_file(int fd, t_buflist *beginning, t_buflist *current);
char		*get_next_line(int fd);
int			find_line(char *str);
long		size_counter(t_buflist *current);
void		clean_buf(t_buflist *c_buf, t_fdlist *c_fd);
t_fdlist	*clean_fd(t_fdlist *ptr_fd, t_fdlist *c_fd);
char		*answerer(t_buflist *current, int i, int i2);

#endif
