/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kid_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:06:21 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/22 11:03:06 by nlonka           ###   ########.fr       */
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
	tcsetattr(info->safe_in, TCSAFLUSH, &info->old_term);
	while ((wait(&info->return_val)) > 0)
		;
	info->return_val = WEXITSTATUS(info->return_val);
	tcsetattr(info->safe_in, TCSAFLUSH, &info->new_term);
	if (info->return_val == 130)
		printf("\n");
	if (info->return_val == 131)
		printf("Quit: 3\n");
	if (info->return_val == 69)
		info->exit = 1;
	if (info->return_val == 139)
	{
		ft_putstr_fd(info->dino, 2);
		ft_putendl_fd("Segmentation fault: 11", 2);
	}
}

