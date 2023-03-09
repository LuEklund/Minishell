/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                              :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:49:35 by leklund           #+#    #+#             */
/*   Updated: 2023/03/06 11:40:55 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	**copy_env(char **env_to_copy)
{
	char		**new_env;
	int			i;

	i = 0;
	while (env_to_copy[i] != NULL)
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env_to_copy[i] != NULL)
	{
		new_env[i] = (char *)malloc(sizeof(char) * ft_strlen(env_to_copy[i]) + 1);
		ft_strlcpy(new_env[i], env_to_copy[i], ft_strlen(env_to_copy[i]) + 1);
		// new_env[i] = env_to_copy[i];
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

<<<<<<< HEAD
int	handle_word(t_data *info, int i,int file, char *last_char)
{
	int	i2;

	i2 = 0;
	while (info->args[i][i2])
	{
		if (info->args[i][i2] == '>')
			file = 1;
		if (!file)
			write(1, &info->args[i][i2], 1);
		*last_char = info->args[i][i2];
		i2++;
	}
	if (*last_char == '>')
		file = 1;
	else
	{
		if (info->args[i + 1] && info->args[i + 1][0] != '>')
			write(1, " ", 1);
		file = 0;
	}
	return (file);
}

=======
<<<<<<< HEAD
//<<<<<<< HEAD
//static char	*argumenter(char *str)
//{
//	int	i;

//	i = 0;
//	while (str[i] != ' ' && str[i] != '\0')
//		i++;
//	if (!str[i])
//		return (NULL);
//	return (&str[++i]);
//}
//=======
// static char	*argumenter(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != ' ' && str[i] != '\0')
// 		i++;
// 	if (!str[i])
// 		return (NULL);
// 	return (&str[++i]);
// }
//>>>>>>> 7906bd35c1ccfd503710837a27d2c97a321aae47

=======
>>>>>>> master
>>>>>>> nlonka
int	echo(t_data *info)
{
	int		i;
	int		new_line;
	int		file;
	char	last_char;

	i = 1;
	new_line = 2;
	file = 0;
	last_char = 0;
	if (info->args[i][0] == '-' && info->args[i][1] == 'n')
	{
		while(info->args[i][new_line] == 'n')
			new_line++;
		if (!info->args[i][new_line])
		{
			new_line = 0;
			i++;
		}
	}
	while (info->args[i])
	{
		file = handle_word(info, i, file, &last_char);
		i++;
	}
	if (new_line)
		printf("\n");
	return (1);
}

int	execute_built(t_data *info)
{
	if (info->built == 1)
	{
		// printf("echo\n\r");
		echo(info);
	}
	else if (info->built == 3)
	{
		// printf("display_curdir\n\r");
		display_curdir();
	}
	else if (info->built == 6)
	{
<<<<<<< HEAD
		env_export(info, 0);
=======
<<<<<<< HEAD
		display_env(info, 1);	
=======
		env_export(info, info->args[1]);
>>>>>>> master
>>>>>>> nlonka
	}
	else if (info->built == 7)
	{
		// printf("display_env\n\r");
		display_env(info, 0);
	}
	return (0);
}
