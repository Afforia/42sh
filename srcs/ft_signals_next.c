/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals_next.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:32:55 by wveta             #+#    #+#             */
/*   Updated: 2019/09/29 23:21:47 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sig_set(void)
{
	signal(SIGCHLD, ft_signal_handler_rl);
	signal(SIGINT, ft_signal_handler_rl);
	signal(SIGTTIN, ft_signal_handler_rl);
//	signal(SIGTTOU, ft_signal_handler_rl);
//	signal(SIGTTOU, SIG_DFL);
//	signal(SIGTTIN, SIG_DFL);
	signal(SIGTSTP, ft_signal_handler_rl);
	signal(SIGQUIT, ft_signal_handler_rl);
//	signal(SIGKILL, ft_signal_handler_rl);
//	signal(SIGTERM, ft_signal_handler_rl);
	signal(SIGCONT, ft_signal_handler_rl);
}

void	ft_test_cmd_list(pid_t pid, int status)
{
	t_cmdlist *cur_cmd;

	if (g_job == 0 && g_pipe && ((cur_cmd = g_pipe->first_cmd)))
	{
		while (cur_cmd)
		{
			if (cur_cmd->pid != 0)
			{
				if (cur_cmd->pid == pid)
				{
					if ((!(cur_cmd->next)) && (WIFEXITED(status)))
						ft_set_shell("?", "1");
					else
						ft_set_shell("?", "0");
					cur_cmd->pid = 0;
				}
			}
			cur_cmd = cur_cmd->next;
		}
	}
}

int		ft_test_sig_list(int signo)
{
	if (signo == SIGCHLD || signo == SIGINT || signo == SIGTTIN
		|| signo == SIGTTOU || signo == SIGTSTP || signo == SIGQUIT)
//		|| signo == SIGTERM || signo == SIGKILL || signo == SIGCONT)
		return (1);
	return (0);
}

int		ft_job_stopped(t_job *j)
{
	t_proc *p;

	p = j->first_proc;
	while (p)
	{
		if (!(p->completed) && !(p->stopped))
			return (0);
		p = p->next;
	}
	return (1);
}

int		ft_job_completed(t_job *j)
{
	t_proc *p;

	p = j->first_proc;
	while (p)
	{
		if (!(p->completed))
			return (0);
		p = p->next;
	}
	return (1);
}
