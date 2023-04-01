/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:25:39 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/29 17:25:43 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tokens(t_error *he);   

void	find_or_and(t_error *he, char *str)
{
	reset_help(he);
	if (!he->i || he->q || he->sq)
		;
	else if (str && str[he->i] == '|' && str[he->i - 1] == '|')
		he->or = 1;
	else if (str && str[he->i] == '&' && str[he->i - 1] == '&')
		he->and = 1;
}

char	*second_white_space_cleanse(char *src, char *ans, size_t i)
{
	t_error	he;

	he.i = 0;
	he.q = 0;
	he.sq = 0;
	reset_help(&he);
	while (src && src[he.i])
	{
	//	printf("at %c%zu\n", src[he.i], he.i);
	//	print_tokens(&he);
		if (!(src[he.i] == ' ' && (he.and || he.or)) || he.q || he.sq)
		{
			if (ans)
				ans[i] = src[he.i];
			i++;
		}
		find_or_and(&he, src);
		he.i = quote_check(src, he.i, &he.q, &he.sq);
	}
	if (ans)
		return (ans);
	ans = malloc(sizeof(char) * (i + 1));
	if (!ans)
		exit(write(2, "memory errawr🦖\n", 15));
	ans[i] = '\0';
	return (second_white_space_cleanse(src, ans, 0));
}

void	free_help(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	free_ar(char **ar)
{
	int	i;

	i = 0;
	if (!ar)
		return ;
	while (ar[i])
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}

void	get_outed(t_data info)
{
	free_ar(info.envs);
	tcsetattr(info.fd_in, TCSAFLUSH, &info.old_term);
}

int	redir_input_parser(const char *str, t_split *he, int var)
{
	int	len;

	len = he->expand_type - 2;
	while (str[he->i3 + len] && str[he->i3 + len] != ' ' \
			&& he->sq + he->q == 0)
		len++;
	if (he->sq + he->q != 0)
		return (0);
	if (var)
	{
		while (str[he->i3 + len] == he->c)
			len++;
	}
	he->i3 += len;
	return (1);
}
