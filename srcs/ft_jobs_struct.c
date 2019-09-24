/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/24 16:32:02 by wveta            ###   ########.fr       */
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
	ft_putstr(cur_job->orig_cmd);
	ft_putstr("\n");
}

void	ft_print_job_stop(t_job *cur_job)
{
	ft_putstr("\n[");
	ft_putnbr(cur_job->num);
	ft_putstr("]");
	ft_putchar(cur_job->flag);
	ft_putstr("  Stopped               ");
	ft_putstr(cur_job->orig_cmd);
	ft_putstr("\n");
}

t_job 	*ft_del_job(t_job *del)
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
			if (del->cmd)
				free(del->cmd);
			if (del->orig_cmd)
				free(del->orig_cmd);
			free(del);
			break ;
		}
		else
			prev = tmp;
		tmp = tmp->next;
	}
	return (prev);
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
		cur_job->cmd = NULL;
		cur_job->orig_cmd = NULL;
		if (!(g_job_first))
		{
			g_job_first = cur_job;
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
				if (tmp == g_job_first && tmp->num > 1)
				{
					cur_job->num = 1;
					cur_job->next = tmp;
					g_job_first = cur_job;
					break ;
				}
				else if (tmp->next && tmp->num + 1 < tmp->next->num)
				{
					cur_job->num = tmp->num + 1;
					cur_job->next = tmp->next;
					tmp->next = cur_job;
					break ;
				}
				else if (!(tmp->next) && tmp != cur_job)
				{
					tmp->next = cur_job;
					cur_job->num = tmp->num + 1;
					break ;
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
		if (cur_cmd->nr == 1 &&
			((cur_job->orig_cmd = ft_strnew((size_t)(g_job_end + 1)))))
			cur_job->orig_cmd = ft_strncpy(cur_job->orig_cmd, g_job_start, g_job_end);
		else
			cur_job->orig_cmd = ft_strdup(cur_job->cmd);
		ft_print_start_job(cur_job);
	}
	return (1);
}
