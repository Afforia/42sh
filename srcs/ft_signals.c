/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:32:55 by wveta             #+#    #+#             */
/*   Updated: 2019/09/27 18:06:13 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_handler_rl(int signo)
{
	t_job		*cur;
	t_proc		*proc;
	t_cmdlist	*cur_cmd;
	pid_t		pid;
	int			status;
	char		*tmp;

	ft_sig_set();
	if (signo == SIGCHLD || signo == SIGINT || signo == SIGTTIN ||
		signo == SIGTTOU || signo == SIGTSTP || signo == SIGQUIT ||
		signo == SIGTERM || signo == SIGKILL || signo == SIGQUIT ||
		signo == SIGCONT)
	{
		pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
		if (g_job_first && ((cur = g_job_first)))
		{
			while (cur)
			{
				proc = cur->first_proc;
				while (proc)
				{
					if (proc->pid == pid)
					{
						proc->status = status;
						if (WIFEXITED(status))
						{
							proc->completed = 1;
							if (!(proc->next))
							{
								cur->stat_job = ft_strcpy(cur->stat_job, "Done                     ");
								cur->ready = 1;
								break ;
							}
						}
						else if (WIFSTOPPED(status))
						{
							proc->stopped = 1;
							cur->stat_job = ft_strcpy(cur->stat_job, "Stopped  by ");
							tmp = ft_num_to_str(WSTOPSIG(status));
							cur->stat_job = ft_strfjoin(cur->stat_job, tmp);
							cur->stat_job = ft_strfjoin(cur->stat_job, "           ");
							free(tmp);
							break ;
						}
						if (WIFSIGNALED(status))
						{
							proc->completed = 1;
							cur->stat_job = ft_strcpy(cur->stat_job, "Terminated by signal ");
							tmp = ft_num_to_str(WTERMSIG(status));
							cur->stat_job = ft_strfjoin(cur->stat_job, tmp);
							cur->stat_job = ft_strfjoin(cur->stat_job, " ");
							free(tmp);
							cur->ready = 1;
							break ;
						}
					}
					proc = proc->next;
				}
				cur = cur->next;
			}
		}

		if (g_pipe)
		{
			cur_cmd = g_pipe->first_cmd;
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
	if (signo == SIGINT)
	{
		if (g_check == 0)
			ft_putchar('\n');
		else
			exit(0);
	}
}

void	ft_sig_set(void)
{
	signal(SIGCHLD, ft_signal_handler_rl);
	signal(SIGINT, ft_signal_handler_rl);
	signal(SIGTTIN, ft_signal_handler_rl);
	signal(SIGTTOU, ft_signal_handler_rl);
	signal(SIGTSTP, ft_signal_handler_rl);
	signal(SIGQUIT, ft_signal_handler_rl);
	signal(SIGKILL, ft_signal_handler_rl);
	signal(SIGTERM, ft_signal_handler_rl);
	signal(SIGQUIT, ft_signal_handler_rl);
	signal(SIGCONT, ft_signal_handler_rl);
}
