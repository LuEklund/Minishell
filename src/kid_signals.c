/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kid_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:06:21 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/23 17:18:29 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	slashing(int signum)
{
	(void)signum;
	exit(131);
}

void	kid_c(int signum)
{
	(void)signum;
	exit(130);
}

void	kid_signals(t_data *info)
{
	sigemptyset(&info->quit.sa_mask);
	info->quit.sa_handler = kid_c;
	sigaction(SIGINT, &info->quit, &info->old_act);
	sigemptyset(&info->z_act.sa_mask);
	info->z_act.sa_handler = slashing;
	sigaction(SIGQUIT, &info->z_act, &info->old_act);
}

void	parent_signals(t_data *info)
{
	info->z_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &info->z_act, &info->old_act);
	sigaction(SIGTSTP, &info->z_act, &info->old_act);
	sigaction(SIGINT, &info->z_act, &info->old_act);
	tcsetattr(info->fd_in, TCSAFLUSH, &info->old_term);
	while ((wait(&info->return_val)) > 0)
		;
//	printf("ret is %d\n", info->return_val);
	if (info->return_val != 11 && info->return_val != 10)
		info->return_val = WEXITSTATUS(info->return_val);
	tcsetattr(info->fd_in, TCSAFLUSH, &info->new_term);
	if (info->return_val == 130)
		printf("\n");
	if (info->return_val == 131)
		ft_putstr_fd("Quit: 3\n", 2);
	if (info->return_val == 11)
	{
		ft_putendl_fd("Segmentation fault: 11", 2);
		info->return_val = 139;
	}
	if (info->return_val == 6)
	{
		ft_putendl_fd("Abort trap: 6", 2);
		info->return_val = 134;
	}
	if (info->return_val == 10)
	{
		ft_putendl_fd("Bus error: 10", 2);
		info->return_val = 138;
	}
}

