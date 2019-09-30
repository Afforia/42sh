/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_in_jobs_bg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/09/30 16:44:52 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_cmd_bg(char **av)
{
	t_job	*j;
	int 	i;
	char	*num;
	int		l;

	if ((!(av[1])))
	{
		j = g_job_first;
		while(j)
		{
			if (j->flag == '+')
			{
				kill (-j->pgid, SIGCONT);
				break ;
			}
			j = j->next;
		}
	}
	else
	{
		l = 0;
		while (av && av[++l])
		{
			i = 0;
			j = g_job_first;
			while(j)
			{
				num = ft_num_to_str(j->num);
				if (ft_strcmp(av[l], num) == 0 && ((i = 1)))
					kill (-j->pgid, SIGCONT);
				free(num);
				j = j->next;
			}
			if (i == 0)
			{
				if (av[l])
					ft_print_msg(": jobs: no such job: ", av[l]);
				ft_set_shell("?", "1");
			}
			else
				ft_set_shell("?", "0");
		}
	}	
	return (1);
}

char	*ft_get_str_cmd(char **s)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup("");
	while(s && s[i])
	{
		tmp = ft_strfjoin(tmp, s[i]);
		tmp = ft_strfjoin(tmp, " ");
		i++;
	}
	return (tmp);
}

void	ft_test_tstp(pid_t pid2)
{
	t_job		*job;
	t_proc		*proc;
	t_cmdlist	*cmd;
	t_job		*job_new;
	pid_t		pid;

	job = g_job_first;
	job_new = NULL;
	if (pid2 == 0 && g_pipe)
		pid = g_pipe->first_cmd->pid_z;
	while(job)
	{
		if (pid == job->pgid)
			return ;
		proc = job->first_proc;
		while(proc)
		{
			if (pid == proc->pid)
				return ;
			proc = proc->next;
		}
		job = job->next;
	}
	if (g_pipe && ((cmd = g_pipe->first_cmd)))
	{
		while(cmd)
		{
			if (cmd->pid_z == pid)
			{
				job_new = ft_new_job(cmd);
				job_new->orig_cmd = ft_get_str_cmd(cmd->avcmd);
				free(job_new->stat_job);
				job_new->stat_job = ft_strdup("Suspended            ");
				break ;
			}	
			cmd = cmd->next;
		}
	}
	if (job_new)
	{
		if (!(g_job_first))
		{
			g_job_first = job_new;
			job_new->num = 1;
		}
		else
			ft_insert_job(job_new);
		ft_set_job_plus();
		ft_print_job_line(job_new, 0);
		ft_add_proc(cmd);
	}
}

int		ft_cmd_kill(char **av)
{
	(void)av;
	return (1);
}

