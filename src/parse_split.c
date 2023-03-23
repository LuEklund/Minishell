/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:07:38 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/16 16:29:44 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_check(char const *str, int i, int *q, int *sq)
{
	if (*q == 1 && str[i] == '\"')
		*q = 0;
	else if (*sq == 1 && str[i] == '\'')
		*sq = 0;
	else if (*q == 0 && *sq == 0 && str[i] == '\"')
		*q = 1;
	else if (*sq == 0 && *q == 0 && str[i] == '\'')
		*sq = 1;
	i++;
	return (i);
}

int	quote_see(char const *str, t_split help)
{
	if (help.sq == 0 && str[help.i3] == '\"')
		return (0);
	if (help.q == 0 && str[help.i3] == '\'')
		return (0);
	if (help.q == 1 && str[help.i3] == '\"')
		return (0);
	if (help.sq == 1 && str[help.i3] == '\'')
		return (0);
	return (1);
}

int	expand_check(char const *str, t_split *help)
{
	help->expand_type = 5;
	if (str[help->i3] == '$' && help->sq == 0) 
	{
		if (str[help->i3 + 1] == '?')
			help->expand_type = 1;
		else
			help->expand_type = 0;	
	}
	else if (str[help->i3] == '>' && help->sq + help->q == 0 && help->c == ' ')
	{
		if (str[help->i3 + 1] == '>')
			help->expand_type = 3;
		else
			help->expand_type = 2;
	}
	else if (str[help->i3] == '<' && help->sq + help->q == 0 && help->c == ' ')
	{
		if (str[help->i3 + 1] == '<')
			help->expand_type = 3;
		else
			help->expand_type = 2;
	}
	else
		return (0);
	return (1);
}

int	red_c(char const *str, t_split *help, int i, int h)
{
	if (help->c != ' ')
		return (quote_check(str, i, &help->q, &help->sq));
	help->i3 = i;
	expand_check(str, help);
	if (help->expand_type != 3 && help->expand_type != 2)
		return (quote_check(str, i, &help->q, &help->sq));
	if (!redir_input_parser(str, help, 0))
		return (quote_check(str, i, &help->q, &help->sq));
	if (h == 1)
		help->i3 += 1;
	return (help->i3);
}

void	wild_marker(char const *str, t_split help, t_data *info)
{
	t_whelp	*current;
	t_whelp	*new;
	
//	printf("check for '%c', at %c%d\n", help.c, str[help.i3], help.i3);
	if (str[help.i3] != '*' || help.c != ' ')
		return ;
	new = malloc(sizeof(t_whelp));
	if (!new)
		exit(write(2, "memory error\n", 13));
	new->next = NULL;
	new->h = help.i2;
	if (help.sq + help.q == 0)
		new->valid = 1;
	else
		new->valid = 0;
	if (!info->wmark_list)
	{
		new->n = 1;
		info->wmark_list = new;
		return ;
	}
	current = info->wmark_list;
	while (current->next)
		current = current->next;
	current->next = new;
	new->n = current->n + 1;
}

static int	string_amount(char const *str, t_split help, int ans, int i)
{
	while (str[i] == help.c && str[i] != '\0' && help.q + help.sq == 0)
		i++;
	if (str[i] == '\0')
		ans = -1;
	while (str[i] != '\0')
	{
		if (str[i] != '\0')
			i = red_c(str, &help, i, ans);
		while (str[i] == help.c)
		{
			if (str[i + 1] != '\0' && str[i + 1] != help.c && str[i + 1] != '>' \
				   	&& str[i + 1] != '<' && help.sq + help.q == 0)
			{
			//	write(2, &str[i + 1], 1);
			//	write(2, "\n", 1);
				ans++;
			}
			i = quote_check(str, i, &help.q, &help.sq);
		}
	}
	if (ans == 0 && str[0] != '\0')
		return (1);
	if (str[0] == '\0' || ans < 0)
		ans = 0;
	return (ans);
}

static char	**ansllocator(char **ans, char const *str, t_data *info, t_split he)
{
	while (he.i2 < he.h)
	{
		if (str[he.i3] == '\'')
			he.sq = he.sq + 1 % 2;
		if (str[he.i3] == '\"')
			he.q = he.q + 1 % 2;
		while (str[he.i3] != '\0' && str[he.i3] == he.c && he.q + he.sq == 0)
			he.i3 += 1;
		while (str[he.i3] != '\0' && (str[he.i3] != he.c || he.q + he.sq != 0))
		{
			if (str[he.i3 + 1] && expand_check(str, &he) && expand_envs(str, info, &he, ans))
					continue ;
			wild_marker(str, he, info);
			if (he.c != ' ' || quote_see(str, he))
				he.i += 1;
			he.i3 = quote_check(str, he.i3, &he.q, &he.sq);
		}
		he.l = he.i - he.h2;
		he.h2 = he.h2 + he.l;
	//	printf("len for height[%d] is %d\n", he.i2, he.l);
		ans[he.i2] = (char *) malloc (sizeof(char) * (he.l + 1));
		he.i2 += 1;
	}
	return (ans);
}

static char	**string_separator_7000(char **ans, char const *str, t_data *info, t_split help)
{
	help.check = 1;
	while (help.i2 < help.h)
	{
		if (str[help.i3] == '\'')
			help.sq = help.sq + 1 % 2;
		if (str[help.i3] == '\"')
			help.q = help.q + 1 % 2;
		while (str[help.i3] != '\0' && str[help.i3] == help.c && help.q + help.sq == 0)
			help.i3 += 1;
		while (str[help.i3] != '\0' && (str[help.i3] != help.c || help.q + help.sq != 0))
		{
			if (str[help.i3 + 1] && expand_check(str, &help) && expand_envs(str, info, &help, ans))
				continue ;
			if (help.c != ' ' || quote_see(str, help))
				ans[help.i2][help.i] = str[help.i3];
			if (help.c != ' ' || quote_see(str, help))
				help.i += 1;
			help.i3 = quote_check(str, help.i3, &help.q, &help.sq);
		}
		ans[help.i2][help.i] = '\0';
		help.i2 += 1;
		help.i = 0;
	}
	return (ans);
}

static char	**check_malloc(char **ans, int h)
{
	int	i2;

	i2 = 0;
	while (i2 < h)
	{
		if (ans[i2] == NULL)
		{
			i2 = 0;
			while (i2 < h)
			{
				free(ans[i2]);
				i2++;
			}
			free(ans);
			return (NULL);
		}
		i2++;
	}
	return (ans);
}

void	init_help(t_data *info, char c, char const *str)
{
	t_split	*help;

	help = info->split;
	help->sq = 0;
	help->q = 0;
	if (str && str[0] == '\'')
		help->sq = 1;
	else if (str && str[0] == '\"')
		help->q = 1;
	help->i = 0;
	help->i2 = 0;
	help->i3 = 0;
	help->l = 0;
	help->h2 = 0;
	help->q = 0;
	help->sq = 0;
	help->c = c;
	help->check = 0;
}

char	**parse_split(char const *str, char c, t_data *info)
{
	int		h;
	char	**ans;
	t_split	help;

	info->split = &help;
	init_help(info, c, str);
	if (str == NULL)
		return (NULL);
	h = string_amount(str, help, 1, help.sq + help.q);
//	printf("h is %d\n", h);
	ans = (char **) malloc(sizeof(char *) * (h + 1));
	if (ans == NULL)
		return (NULL);
	ans[h] = 0;
	help.h = h;
	help.q = 0;
	help.sq = 0;
	ans = ansllocator(ans, str, info, *(info->split));
	ans = check_malloc(ans, h);
	if (ans == NULL)
		return (NULL);
	ans = string_separator_7000(ans, str, info, *(info->split));
	return (ans);
}
