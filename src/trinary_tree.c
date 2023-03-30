/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trinary_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:37:05 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/24 12:23:00 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*content_creator(char *str, t_error help)
{
	char	*ans;

	get_tokenized(&help, str, 0);
	while (str[help.i] && !help.or && !help.and)
	{
		help.i = quote_check((char const *)str, help.i, &help.q, &help.sq);
		get_tokenized(&help, str, 0);
	}
	ans = malloc(sizeof(char) * (help.i + 1));
	ans[help.i] = '\0';
	help.i -= 1;
	while (1)
	{
		ans[help.i] = str[help.i];
		if (!help.i)
			break ;
		help.i -= 1;
	}
	return (ans);
}

t_cond	*create_condition_node(char *str, t_cond *up)
{
	t_cond	*new;
	t_error	help;

	help.i = 0;
	help.q = 0;
	help.sq = 0;
	help.par = 0;
	new = check_content(str, up, help);
	if (new)
		return (free(str), new);
	new = malloc(sizeof(t_cond));
	if (!new)
		exit(write(2, "memory errawr🦖\n", 15));
	new->type = 0;
	new->ret = -1;
	new->content = content_creator(str, help);
	free_help(str);
	new->up = up;
	new->hd_n = 0;
	new->first_cond = NULL;
	new->sec_cond = NULL;
	new->next = NULL;
	return (new);
}

t_cond	*create_tokenode(t_error help, char *str, t_cond *back, t_cond *up)
{
	t_cond	*new;
	size_t	i;

	i = help.i;
	new = malloc(sizeof(t_cond));
	if (!new)
		exit(write(2, "memory errawr🦖\n", 15));
		new->type = 2;
	if (help.or)
		new->type = 1;
	new->ret = -1;
	new->up = up;
	new->sec_cond = create_condition_node(ft_substr((char const *)str, i + 2, \
	ft_strlen(str) - (i + 1)), new);
	new->back = back;
	if (back)
	{
		new->first_cond = NULL;
		new->next = create_level(ft_substr((char const *)str, i + 2, \
		ft_strlen(str) - (i + 1)), new, up, 0);
	}
	else
		new->first_cond = create_condition_node(ft_strdup(str), new);
	free_help(str);
	return (new);
}

t_cond	*create_level(char *str, t_cond *back, t_cond *up, int var)
{
	t_error	help;

	help.i = 0;
	help.q = 0;
	help.sq = 0;
	help.par = 0;
	help.rm_par = var;
	str = par_ser(str, &help);
	if (check_for_logic(str, 1) && back)
		return (free_help(str), NULL);
	else if (!str[help.i])
		return (create_condition_node(str, up));
	else if (!back)
	{
		back = create_tokenode(help, ft_strdup(str), NULL, up);
		back->next = create_level(ft_substr((char const *)str, help.i + 2, \
		ft_strlen(str) - (help.i + 1)), back, up, 0);
		return (free_help(str), back);
	}
	else
		return (create_tokenode(help, str, back, up));
}
