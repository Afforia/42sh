/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/27 16:59:56 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_insert_job(t_job *cur_job)
{
	t_job	*tmp;

	tmp = g_job_first;
	while (tmp)
	{
		if (tmp == g_job_first && tmp->num > 1)
		{
			cur_job->num = 1;
			cur_job->next = tmp;
			g_job_first = cur_job;
		}
		else if (tmp->next && tmp->num + 1 < tmp->next->num)
		{
			cur_job->num = tmp->num + 1;
			cur_job->next = tmp->next;
			tmp->next = cur_job;
		}
		else if (!(tmp->next) && tmp != cur_job)
		{
			tmp->next = cur_job;
			cur_job->num = tmp->num + 1;
		}
		else
			tmp = tmp->next;
	}
}

t_job	*ft_del_job(t_job *del)
{
	t_job	*prev;
	t_job	*tmp;

	tmp = g_job_first;
	prev = NULL;
	while (tmp && del)
	{
		if (tmp == del)
		{
			if (prev)
				prev->next = del->next;
			else
			{
				g_job_first = del->next;
				prev = g_job_first;
			}
			if (del->orig_cmd)
				free(del->orig_cmd);
			if (del->first_proc)
				ft_del_proc_list(del->first_proc);
			free(del);
			break ;
		}
		else
			prev = tmp;
		tmp = tmp->next;
	}
	ft_set_job_plus();
	return (prev);
}

int		ft_if_job(t_cmdlist *cur_cmd)
{
	t_job	*cur_job;

	cur_job = NULL;
	if (g_job == 1)
	{
		if (cur_cmd->nr == 1)
		{
			cur_job = malloc(sizeof(t_job));
			cur_job->stat_job = ft_strdup("Running               ");
			cur_job->ind = g_job_ind;
			g_job_ind++;
			cur_job->next = NULL;
			cur_job->first_proc = NULL;
			cur_job->orig_cmd = NULL;

			if (g_pgid == 0)
				g_pgid = cur_cmd->pid;
			cur_job->pgid = g_pgid;
			cur_job->ready = 0;
			if (!(g_job_first))
			{
				g_job_first = cur_job;
				cur_job->num = 1;
			}
			else
				ft_insert_job(cur_job);
			cur_job->orig_cmd = ft_strncpy(ft_strnew((size_t)
			(g_job_end + 1)), g_job_start, g_job_end);
			ft_set_job_plus();
			ft_print_start_job(cur_job);
		}
		ft_add_proc(cur_cmd);
	}
//	else
//		tcsetpgrp(g_terminal, g_pgid);
	return (1);
}
