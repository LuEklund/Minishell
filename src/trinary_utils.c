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

void	free_help(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
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
		get_tokenized(&help, str, 0);
		if (!var && (help.and || help.or || help.par))
			return (0);
		if (var && !help.par && (help.or || help.and))
			return (0);
		help.i = quote_check((char const *)str, help.i, &help.q, &help.sq);
	}
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
	if (str[help->i] || !help->rm_par || check_for_logic(str, 0))
		return (str);
	help->q = 0;
	help->sq = 0;
	help->par = 0;
	help->i = 0;
	reset_token_val(help);
	ans = ft_substr((char const *)str, 1, ft_strlen(str) - 2);
	free_help(str);
	if (!ans)
		exit(write(2, "memory errawr🦖\n", 15));
	return (par_ser(ans, help));
}

t_cond	*check_content(char *str, t_cond *up, t_error help)
{
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
		return (create_level(ft_substr((char const *)str, 0, help.i + 1), \
		NULL, up, 1));
	}
	return (NULL);
}
