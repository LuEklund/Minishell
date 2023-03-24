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

int	check_for_logic(char *str, int var)
{
	t_error	help;

	help.q = 0;
	help.sq = 0;
	help.par = 0;
	help.i = 0;
//	printf("working on str '%s':\n", str);
	while (str[help.i])
	{
		get_tokenized(&help, str, 0);
//		printf("and val is %d, or val is %d and par val is %d\n", help.and, help.or, help.par);
		if (!var && (help.and || help.or || help.par))
			return (0);
		if (var && !help.par && (help.or || help.and))
			return (0);
		help.i = quote_check((char const *)str, help.i, &help.q, &help.sq);
	}
//	printf("returning 1\n");
	return (1);
}

char	*par_ser(char *str, t_error *help)
{
	char	*ans;

	get_tokenized(help, str, 0);
	while (str[help->i] && !(!help->par && (help->and || help->or)))
	{
		help->i = quote_check((char const *)str, help->i, &help->q, &help->sq);
		get_tokenized(help, str, 0);
	}
//	printf("i is %zu in par_ser\n", help->i);
	if (str[help->i] || !help->rm_par || check_for_logic(str, 0))
	{
//		printf("returning '%s' from here\n", str);
		return (str);
	}
	help->q = 0;
	help->sq = 0;
	help->par = 0;
	help->i = 0;
	reset_token_val(help);
//	printf("we're cutting up\n %s\n now\n", str);
	ans = ft_substr((char const *)str, 1, ft_strlen(str) - 2);
//	printf("cut result\n %s\n now\n", ans);
//	free(str);
	if (!ans)
		exit(write(2, "memory errawr🦖\n", 15));
	return (par_ser(ans, help));
}

t_cond	*check_content(char *str, t_cond *up, t_error help)
{
	///quotes could fuck it up here?
	get_tokenized(&help, str, 0);
	if (1)
	{
		if (!help.par)
			return (NULL);
		while (str[help.i] && help.par)
		{
			help.i = quote_check((char const *)str, help.i, &help.q, &help.sq);
			get_tokenized(&help, str, 0);
		}
		return (create_level(ft_substr((char const *)str, 0, help.i + 1), NULL, up, 1));
	}
	return (NULL);
}

char	*content_creator(char *str, t_error help, int var)
{
	char	*ans;

	(void)var;//ff
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
//		printf("copying '%c' at %zu\n", str[help.i], help.i);
		ans[help.i] = str[help.i];
		if (!help.i)
			break ;
		help.i -= 1;
	}
//	printf("condition for something is:\n%s\n", ans);
	return (ans);
}

t_cond	*create_condition_node(char *str, t_cond *up, int var)
{
	t_cond	*new;
	t_error	help;

	help.i = 0;
	help.q = 0;
	help.sq = 0;
	help.par = 0;
	new = check_content(str, up, help);
	if (new)
		return (new);
	new = malloc(sizeof(t_cond));
	if (!new)
		exit(write(2, "memory errawr🦖\n", 15));
	new->type = 0;
	new->ret = -1;
	new->content = content_creator(str, help, var);
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
	if (help.or)
		new->type = 1;
	else
		new->type = 2;
	new->ret = -1;
	new->up = up;
	new->sec_cond = create_condition_node(str + i + 2, new, -1);
	new->back = back;
	if (back)
	{
		new->first_cond = NULL;
		new->next = create_level(str + i + 2, new, up, 0);
	}
	else
		new->first_cond = create_condition_node(str, new, 0);
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
//	if (up)
//		printf("going into par_ser for up %d\n", up->type);
//	if (back)
//		printf("going into par_ser for back %d\n", back->type);
	str = par_ser(str, &help);
//	printf("i is %zu\n", help.i);
	if (check_for_logic(str, 1) && back)
		return (NULL);
	else if (!str[help.i])
		return (create_condition_node(str, up, 0));
	else if (!back)
	{
		back = create_tokenode(help, str, NULL, up);
		back->next = create_level(str + help.i + 2, back, up, 0);
//		if (back->next)
//			printf("str is %s and content is %s\n", str + help.i + 2, back->next->content);///
		return (back);
	}
	else
		return (create_tokenode(help, str, back, up));
}
