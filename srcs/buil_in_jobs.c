/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_in_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/09/29 22:51:24 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t mark_process_status (pid_t pid, int status)
{
  t_job *j;
  t_proc *p;

	if (pid > 0)
    {
		return (ft_test_job_status(pid, status));
		j = g_job_first;
		while(j)
		{
			p = j->first_proc;
			while(p)
			{
				if (p->pid == pid)
            	{
              		p->status = status;
              		if (WIFSTOPPED (status))
                		p->stopped = 1;
              		else
                	{
                  		p->completed = 1;
                  		if (WIFSIGNALED (status))
                    		ft_print_job_line(j, 0);
                	}
            		return (0);
             	}
				p = p->next;
			}
			j = j->next;
		}
    }
	return (-1);
}

void	ft_restore_io(void)
{
	if (g_std_in > -1)
		dup2(g_std_in, STDIN_FILENO);
	if (g_std_out > -1)
		dup2(g_std_out, STDOUT_FILENO);
	if (g_stderr > -1)
		dup2(g_stderr, STDERR_FILENO);
}
void	ft_job_fg(t_job *j)
{
	int 	status;
	pid_t	pid;


	tcsetpgrp(g_terminal, j->pgid);
	if (kill(- j->pgid, SIGCONT) < 0)
    	ft_print_msg(": SIGCONT error ", " ");
	while (1)
	{
		if ((pid = waitpid (WAIT_ANY, &status, WUNTRACED)) > 0)
			mark_process_status(pid, status);
			if ((ft_job_stopped(j)) || (ft_job_completed(j)))
				break ;
	}
	tcsetpgrp(0, g_parent_pid);
}

int		ft_cmd_fg(char **av)
{
	t_job	*j;
	int 	i;
	char	*num;

	j = g_job_first;
	i = 0;
	while(j)
	{
		num = ft_num_to_str(j->num);	
		if (((av && av[1] && ft_strcmp(av[1], num) == 0) ||
			((!(av[1]) && j->flag == '+'))) && ((i = 1)))
			ft_job_fg(j);
		free(num);
		if (i == 1)
			break ;
		j = j->next;
	}
	if (i == 0)
	{
		if (av[1])
			ft_print_msg(": jobs: no such job: ", av[1]);
		else
			ft_print_msg(": jobs: current: no such job", " ");
		ft_set_shell("?", "1");
	}
	else
		ft_set_shell("?", "0");		
	return (1);
}
