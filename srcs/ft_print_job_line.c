/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_job_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/26 22:57:59 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_job_line(t_job *job, int fl)
{
	char	*tmp;
	char	*num;
	int		len;
	t_proc	*proc;

	if (fl == 1)
	{
		proc = job->first_proc;
		while (proc)
		{
			if (proc == job->first_proc)
			{
				tmp = ft_print_job_pref(job);
				len = ft_strlen(tmp);
			}
			else
			{
				tmp = ft_strdup("                ");
				tmp[len] = '\0';
			}
			num = ft_num_to_str(proc->pid);
			tmp = ft_strfjoin(tmp, num);
			free(num);
			tmp = ft_strfjoin(tmp, " ");
			if (proc == job->first_proc)
				tmp = ft_strfjoin(tmp, job->stat_job);
			else
				tmp = ft_strfjoin(tmp,"                    ");
			tmp = ft_strfjoin(tmp, proc->argv[0]);
			tmp = ft_strfjoin(tmp, "\n");
			ft_putstr(tmp);
			tmp[len] = '\0';
			proc = proc->next;
		}
	}
	else
	{
//		num = ft_get_status_job(job, fl);
//		tmp = ft_strfjoin(tmp, num);
//		free(num);
		tmp = ft_print_job_pref(job);
		tmp = ft_strfjoin(tmp, job->stat_job);
		tmp = ft_strfjoin(tmp, job->orig_cmd);
		tmp = ft_strfjoin(tmp, "\n");
		ft_putstr(tmp);
		free(tmp);
	}
}

void	ft_print_if_job_(char *str, int fl)
{
	t_job	*job;

	job = g_job_first;
	while (job)
	{
		if (job->num == ft_atoi(str))
		{
			ft_print_job_line(job, fl);
			return ;
		}
		job = job->next;
	}
}