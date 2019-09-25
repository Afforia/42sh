/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:32:55 by wveta             #+#    #+#             */
/*   Updated: 2019/09/25 20:33:14 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_handler_rl(int signo)
{
	t_job		*cur;
	t_job		*prev;
	t_proc		*proc;
	t_cmdlist	*cur_cmd;
	pid_t		pid;
	int			status;
	int			i;

	ft_sig_set();
	if (signo == SIGCHLD)
	{
		pid = waitpid(-1, &status, WNOHANG | WUNTRACED);

		if (g_job_first && ((cur = g_job_first)))
		{
			prev = NULL;
			i = 0;
			while (cur && i == 0)
			{
				proc = cur->first_proc;
				while (proc && i == 0)
				{
					if (proc->pid == pid)
					{
						proc->status = status;
						if (WIFSTOPPED(status))
							proc->stopped = 1;
						else
							proc->completed = 1;
//						ft_update_job_status(cur);
						i = 1;
					}
					proc = proc->next;
				}
				cur = cur->next;
			}
		}
/*				if (cur->pid == pid)
				{
					if (WIFEXITED(status))
					{
						ft_print_done_job(cur);
						cur = ft_del_job(cur);
						ft_set_shell("?", "0");
					}
					else if (WIFSTOPPED(status))
					{
						ft_print_job_stop(cur);
						s = ft_strdup("");
						ft_set_shell("?", "1");
						//ft_putfnbr(WSTOPSIG(status), s));
						free(s);
					}
					else if (WIFSIGNALED(status))
					{
//						ft_print_job_term(cur);
						cur = ft_del_job(cur);
						s = ft_strdup("");
						ft_set_shell("?", "1");
						//ft_putfnbr(WTERMSIG(status), s));
						free(s);
					}
					else
						ft_set_shell("?", "1");
				}
				if (cur)
				{
					prev = cur;
					cur = prev->next;
				}
			}
		}*/
		if (g_pipe)
		{
			cur_cmd = g_pipe->first_cmd;
			while (cur_cmd)
			{
				if (cur_cmd->pid != 0)
				{
					status = 0;
					if (cur_cmd->pid == pid)
					{
						if ((!(cur_cmd->next)) && (WIFEXITED(status)))
						{
							if ((WEXITSTATUS(status)) != 0)
								ft_set_shell("?", "1");
							else
								ft_set_shell("?", "0");
						}
						cur_cmd->pid = 0;
					}
				}
				cur_cmd = cur_cmd->next;
/*				if (g_pipe->last_cmd->pid == 0)
				{
					if (g_flpi == 0)
						g_pipe->first_cmd = ft_redir_io_restore(g_pipe->first_cmd);
					return ;
				}*/
			}
		}
	}
	else if (signo == SIGINT)
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
}
