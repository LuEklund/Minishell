/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trinary_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:25:56 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/29 17:25:58 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_help(t_error *he)
{
	he->or = 0;
	he->pipe = 0;
	he->and = 0;
}

void	get_tokenized_even_more(t_error *he, char *str)
{
	reset_help(he);
	if (str && str[he->i] == '|' && str[he->i + 1] == '|')
		he->or = 1;
	else if (str && str[he->i] == '|')
		he->pipe = 1;
	else if (str && str[he->i] == '&' && str[he->i + 1] == '&')
		he->and = 1;
	else if (str && str[he->i] == '(')
		he->par += 1;
	else if (str && str[he->i] == ')')
		he->par -= 1;
}

int	check_for_logic(char *str, int var)
{
	t_error	help;

	help.q = 0;
	help.sq = 0;
	help.par = 0;
	help.i = 0;
	while (str[help.i])
	{
		get_tokenized_even_more(&help, str);
		if (!var && (help.and || help.or || help.par))
			return (0);
		if (var && !help.par && (help.or || help.and))
			return (0);
		help.i = quote_check((char const *)str, help.i, &help.q, &help.sq);
	}
	return (1);
}

void	print_tokens(t_error *he);   //fddfdfdf

char	*par_ser(char *str, t_error *help)
{
	char	*ans;

	get_tokenized_even_more(help, str);
	while (str[help->i] && !(!help->par && (help->and || help->or)))
	{
		printf("at %c%zu\n", str[help->i], help->i);
		printf("rm par is %d\n", help->rm_par);
		print_tokens(help);
		help->i = quote_check((char const *)str, help->i, &help->q, &help->sq);
		get_tokenized_even_more(help, str);
	}
	if (str[help->i] || !help->rm_par || check_for_logic(str, 0))
		return (str);
	help->q = 0;
	help->sq = 0;
	help->par = 0;
	help->i = 0;
	reset_help(help);
	printf("before parsing:\n%s\n", str);
	ans = ft_substr((char const *)str, 1, ft_strlen(str) - 2);
	printf("after parsing:\n%s\n", ans);
	free_help(str);
	if (!ans)
		exit(write(2, "memory errawr🦖\n", 15));
	return (par_ser(ans, help));
}

t_cond	*check_content(char *str, t_cond *up, t_error help)
{
	get_tokenized_even_more(&help, str);
	if (1)
	{
		if (!help.par)
			return (NULL);
		while (str[help.i] && help.par)
		{
			help.i = quote_check((char const *)str, help.i, &help.q, &help.sq);
			get_tokenized_even_more(&help, str);
		}
		return (create_level(ft_substr((char const *)str, 0, help.i + 1), \
		NULL, up, 1));
	}
	return (NULL);
}
