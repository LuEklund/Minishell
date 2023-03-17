/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trinary_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:37:05 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/17 18:52:38 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_par(char *str, size_t *i, size_t i2)
{
	t_error	help;
	char	*ans;

	help.i = 0;
	while (str[help.i] && str[help.i] != '(')
		help.i += 1;
	*i = help.i;
	if (!str[help.i])
		return (str);
	ans = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!ans)
		exit(write(2, "memory error\n", 13));
	help.par = 0;
	get_tokenized(&help, str, 0);
	help.i = quote_check((char const *)str, help.i, &help.q, &help.sq);
	while (str[help.i] && help.par)
	{
		ans[i2] = str[help.i];
		i2++;
		help.i = quote_check((char const *)str, help.i, &help.q, &help.sq);
		get_tokenized(&help, str, 0);
	}
	ans[i2] = '\0';
	*i = 0;
	//freee strr???
	return (ans);
}

t_cond	*check_content(char *str, t_cond *head, t_error help, int var)
{
	///quotes could fuck it up here?
	get_tokenized(&help, str, 0);
	if (var == 0 || var == -1)
	{
		if (!help.par)
			return (NULL);
		while (str[help.i] && help.par)
		{
			help.i = quote_check((char const *)str, help.i, &help.q, &help.sq);
			get_tokenized(&help, str, 0);
		}
		return (create_level(ft_substr((char const *)str, 0, help.i), head));
	}
	return (NULL);
}

char	*content_creator(char *str, t_error help, int var)
{
	char	*ans;

	if (var == -1)
	{
		ans = malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!ans)
			exit(write(2, "memory error\n", 13));
		ft_strlcpy(ans, str, ft_strlen(str) + 1);
		return (ans);
	}
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
	return (ans);
}

t_cond	*create_condition_node(char *str, t_cond *head, int var)
{
	t_cond	*new;
	t_error	help;

	help.i = 0;
	help.q = 0;
	help.sq = 0;
	help.par = 0;
	new = check_content(str, head, help, var);
	if (new)
		return (new);
	new = malloc(sizeof(t_cond));
	if (!new)
		exit(write(2, "memory error\n", 13));
	new->type = 0;
	new->ret = 0;
	new->content = content_creator(str, help, var);
	new->up = head;
	new->first_cond = NULL;
	new->sec_cond = NULL;
	new->next = NULL;
	return (new);
}

t_cond	*create_tokenode(t_error help, char *str, size_t i, t_cond *head)
{
	t_cond	*new;

	new = malloc(sizeof(t_cond));
	if (!new)
		exit(write(2, "memory error\n", 13));
	if (help.or)
		new->type = 1;
	else
		new->type = 2;
	new->ret = 0;
	new->up = head;
	new->first_cond = create_condition_node(str, new, 0);
	new->sec_cond = create_condition_node(str + i + 2, new, -1);
	if (head)
		new->next = create_level(str + i + 2, new);
	return (new);
}

t_cond	*create_level(char *str, t_cond *head)
{
	t_error	help;

	help.i = 0;
	help.q = 0;
	help.sq = 0;
	help.par = 0;
	while (str[help.i])
	{
		get_tokenized(&help, str, 0);
		if (!help.par && (help.or || help.and) && help.q + help.sq == 0)
			break ;
//		printf("[%zu] is %c\n", help.i, str[help.i]);
		help.i = quote_check((char const *)str, help.i, &help.q, &help.sq);
		if (!str[help.i])
			str = remove_par(str, &help.i, 0);
	}
	if (!str[help.i])
		return (NULL);
	else if (!head)
	{
		head = create_tokenode(help, str, help.i, NULL);
		head->next = create_level(str + help.i + 2, head);
		return (head);
	}
	else
		return (create_tokenode(help, str, help.i, head));
}
