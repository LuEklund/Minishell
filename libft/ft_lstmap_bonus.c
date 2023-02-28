/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:38:52 by nlonka            #+#    #+#             */
/*   Updated: 2022/11/21 15:38:54 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;

	new_list = NULL;
	if (f && del && lst)
	{
		while (lst != NULL)
		{
			new_elem = ft_lstnew(f(lst->content));
			if (new_elem == NULL)
			{
				ft_lstclear(&new_list, (*del));
				return (NULL);
			}
			ft_lstadd_back(&new_list, new_elem);
			lst = lst->next;
		}
		return (new_list);
	}
	return (NULL);
}
