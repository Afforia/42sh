/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:32:55 by wveta             #+#    #+#             */
/*   Updated: 2019/09/20 19:32:21 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_handler_rl(int signo)
{
	if (signo == SIGQUIT)
	{
		ft_putstr("SIGQUIT\n");
		if (g_subshell == 99)
			exit(3);
		else
			ft_putchar('\n');
		signal(SIGQUIT, ft_signal_handler_rl);
	}
//	else if (signo == SIGCHLD && g_subshell > 1)
//		exit(3);
	else if (signo == SIGINT)
	{
		if (g_check == 0)
			ft_putchar('\n');
//		longjmp(g_cmd->ebuf, g_cmd->jmp_code);
		else
			exit(0);
		signal(SIGINT, ft_signal_handler_rl);
	}
}

void	ft_sig_set(void)
{
//	signal(SIGCHLD, ft_signal_handler_rl);
//	signal(SIGQUIT, ft_signal_handler_rl);
	signal(SIGINT, ft_signal_handler_rl);
}
