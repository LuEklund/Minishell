/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:03:38 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/11 16:29:54 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	allocate_array(char **ans, int len, int i)
{
	struct dirent	*dir;
	DIR				*dh;

	dh = opendir(".");
	if (!dh)
		exit(write(2, "Unable to read directory\n", 25));
	dir = readdir(dh);
	while (dir)
	{
		if (dir->d_name[0] == '.')
		{
			dir = readdir(dh);
			continue ;
		}
		while (dir->d_name[len])
			len++;
		ans[i] = malloc(sizeof(char) * (len + 1));
		if (!ans[i])
			exit(write(2, "memory error\n", 13));
		len = 0;
		i++;
		dir = readdir(dh);
	}
	closedir(dh);
}

void	copy_files(char **ans, int i, int i2, DIR *dh)
{
	struct dirent	*dir;

	allocate_array(ans, 0, 0);
	dh = opendir(".");
	if (!dh)
		exit(write(2, "Unable to read directory\n", 25));
	dir = readdir(dh);
	while (dir)
	{
		if (dir->d_name[0] == '.')
		{
			dir = readdir(dh);
			continue ;
		}
		while (dir->d_name[i2])
		{
			ans[i][i2] = dir->d_name[i2];
			i2++;
		}
		ans[i][i2] = '\0';
		i2 = 0;
		i++;
		dir = readdir(dh);
	}
	closedir(dh);
}

char	**ft_ls(void)
{
	int				n;
	char			**ans;
	struct dirent	*dir;
	DIR				*dh;

	n = 0;
	dh = opendir(".");
	if (!dh)
		exit(write(2, "Unable to read directory\n", 25));
	dir = readdir(dh);
	while (dir)
	{
		if (dir->d_name[0] != '.')
			n++;
		dir = readdir(dh);
	}
	if (!n)
		return (NULL);
	ans = malloc(sizeof(char *) * (n + 1));
	if (!ans)
		exit(write(2, "memory error\n", 13));
	ans[n] = 0;
	closedir(dh);
	copy_files(ans, 0, 0, NULL);
	return (ans);
}
