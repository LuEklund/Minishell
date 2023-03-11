/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kid_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:06:21 by nlonka            #+#    #+#             */
/*   Updated: 2023/03/11 18:43:27 by nlonka           ###   ########.fr       */
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

void	mute_signals(t_data *info)
{
	info->z_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &info->z_act, &info->old_act);
	sigaction(SIGTSTP, &info->z_act, &info->old_act);
	sigaction(SIGINT, &info->z_act, &info->old_act);
}

