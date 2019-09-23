/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/23 22:13:08 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_start_job(t_job *cur_job)
{
	ft_putstr("[");
	ft_putnbr(cur_job->num);
	ft_putstr("] ");
	ft_putnbr(cur_job->pid);
	ft_putstr("\n");
}

void	ft_print_job_term(t_job *cur_job)
{
	ft_putstr("\n[");
	ft_putnbr(cur_job->num);
	ft_putstr("]");
	ft_putchar(cur_job->flag);
	ft_putstr("   ");
	ft_putnbr(cur_job->pid);
	ft_putstr(" Terminated:            ");
	ft_putstr(cur_job->cmd);
	ft_putstr("\n");
}

void	ft_print_done_job(t_job *cur_job)
{
	ft_putstr("\n[");
	ft_putnbr(cur_job->num);
	ft_putstr("]");
	ft_putchar(cur_job->flag);
	ft_putstr("  Done                  ");
	ft_putstr(cur_job->cmd);
	ft_putstr("\n");
}

void	ft_print_job_stop(t_job *cur_job)
{
	ft_putstr("\n[");
	ft_putnbr(cur_job->num);
	ft_putstr("]");
	ft_putchar(cur_job->flag);
	ft_putstr("  Stopped               ");
	ft_putstr(cur_job->cmd);
	ft_putstr("\n");
}

void	ft_del_job(t_job *cur, t_job *prev)
{
	if (cur)
	{
		if (cur->cmd)
			free(cur->cmd);
		if (prev)
			prev->next = cur->next;
		else
			g_job_first = cur->next;
		free(cur);
	}
}

int		ft_if_job(t_cmdlist *cur_cmd, pid_t pid)
{
	t_job	*cur_job;
	t_job	*tmp;
	int		i;

	if (g_job == 1)
	{
		cur_job = malloc(sizeof(t_job));
		cur_job->next = NULL;
		if (!(g_job_first))
		{
			g_job_first = cur_job;
			g_job_last = cur_job;
			cur_job->num = 1;
		}
		else
		{
			tmp = g_job_first;
			while (tmp)
			{
				if (tmp->flag == '+')
					tmp->flag = '-';
				else
					tmp->flag = ' ';
				if (tmp->next && tmp->num + 1 < tmp->next->num)
				{
					cur_job->num = tmp->num + 1;
					cur_job->next = tmp->next;
					tmp->next = cur_job;
					break;
				}
				else if (!(tmp->next) && tmp != cur_job)
				{
					tmp->next = cur_job;
					cur_job->num = tmp->num + 1;
					g_job_last = cur_job;
				}
				tmp = tmp->next;
			}
		}
		cur_job->flag = '+';
		cur_job->pid = pid;
		cur_job->parent_pid = g_parent_pid;
		cur_job->status = 0;
		cur_job->cmd = ft_strdup("");
		i = 0;
		while (cur_cmd->avcmd[i])
		{
			cur_job->cmd = ft_strfjoin(cur_job->cmd, cur_cmd->avcmd[i]);
			cur_job->cmd = ft_strfjoin(cur_job->cmd, " ");
			i++;
		}
		ft_print_start_job(cur_job);
	}
	return (1);
}
