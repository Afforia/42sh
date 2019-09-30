/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:32:55 by wveta             #+#    #+#             */
/*   Updated: 2019/09/30 16:02:32 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_add_strnum(char *str, int i)
{
	char	*tmp;

	if (str)
	{
		tmp = ft_num_to_str(i);
		str = ft_strfjoin(str, tmp);
		free(tmp);
	}
	return (str);
}

int		ft_set_job_status(t_job *job, int n, int status)
{
	job->ready = 1;
	free(job->stat_job);
	if (n == 2)
	{
		job->stat_job = ft_strdup("Stopped  by ");
		job->stat_job = ft_add_strnum(job->stat_job, WSTOPSIG(status));
		job->stat_job = ft_strfjoin(job->stat_job, "           ");
		job->ready = 2;
	}
	else if (n == 3)
	{
		job->stat_job = ft_strdup("Terminated by signal ");
		job->stat_job = ft_add_strnum(job->stat_job, WTERMSIG(status));
		job->stat_job = ft_strfjoin(job->stat_job, " ");
		if (WTERMSIG(status) != 9)
			job->ready = 2;
	}
	else if (n == 4)
	{
		job->stat_job = ft_strdup("Continued      ");
		job->ready = 2;
	}
	else if (n == 1)
	{
		job->stat_job = ft_strdup("Done                     ");
		job->stat_job = ft_add_strnum(job->stat_job, WEXITSTATUS(status));
		job->stat_job = ft_strfjoin(job->stat_job, " ");
	}
	return (1);
}

int		ft_put_job_status(t_job *job, t_proc *proc, int status)
{
	if (WIFCONTINUED(status))
	{
		proc->stopped = 0;
		return (ft_set_job_status(job, 4, status));
	}
	if (WIFSTOPPED(status))
	{
		proc->stopped = 1;
		return (ft_set_job_status(job, 2, status));
	}
	if (WIFSIGNALED(status))
	{
		proc->completed = 1;
		return (ft_set_job_status(job, 3, status));
	}
	if (WIFEXITED(status))
	{
		proc->completed = 1;
		if (!(proc->next))
			return (ft_set_job_status(job, 1, status));
	}
	return (0);
}

void	ft_test_job_status(pid_t pid, int status)
{
	t_job		*job;
	t_proc		*proc;

	if (g_job_first && ((job = g_job_first)))
	{
		while (job)
		{
			proc = job->first_proc;
			while (proc)
			{
				if (proc->pid == pid)
				{
					proc->status = status;
					ft_put_job_status(job, proc, status);
				}
				proc = proc->next;
			}
			job = job->next;
		}
	}
	return ;
}

void	ft_signal_handler_rl(int signo)
{
	pid_t		pid;
	int			status;

	ft_sig_set();
	if (ft_test_sig_list(signo))
	{
		pid = waitpid(-1, &status, WNOHANG | WCONTINUED | WUNTRACED);
		if (signo == SIGTSTP)
			ft_test_tstp(pid);
		ft_test_job_status(pid, status);
		ft_test_cmd_list(pid, status);
	}
	if (signo == SIGINT || signo == SIGTSTP)
	{
		if (g_check == 0)
			ft_putchar('\n');
		else
			exit(0);
	}
}
