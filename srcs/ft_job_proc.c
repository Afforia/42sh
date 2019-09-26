/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/26 23:14:51 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_proc	*ft_new_proc(t_cmdlist *cur_cmd)
{
	t_proc *tmp;

	tmp = NULL;
	if (cur_cmd && (tmp = malloc(sizeof(t_proc))))
	{
		tmp->pgid = g_pgid;
		tmp->pid = cur_cmd->pid;
		tmp->argv = ft_dup_char_matr(cur_cmd->avcmd);
		tmp->status = 0;
		tmp->completed = ' ';
		tmp->stopped = ' ';
		tmp->next = NULL;
	}
	return (tmp);
}

int		ft_put_proc(t_proc *pr, t_job *jb)
{
	t_proc	*tmp;

	tmp = jb->first_proc;
	if (!(tmp))
	{
		jb->first_proc = pr;
		return (1);
	}
	while (tmp)
	{
		if (!(tmp->next) && ((tmp->next = pr)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_add_proc(t_cmdlist *cur_cmd)
{
	t_proc	*tmp;
	t_job	*job;

	if (!(job = g_job_first))
		return ;
	if ((tmp = ft_new_proc(cur_cmd)))
	{
		while (job)
		{
			if (job->pgid == tmp->pgid)
			{
				if (ft_put_proc(tmp, job) == 0)
					free(tmp);
				return ;
			}
			job = job->next;
		}
	}
}

void	ft_del_proc_list(t_proc *proc)
{
	t_proc	*cur;
	t_proc	*next;

	cur = proc;
	while (cur)
	{
		next = cur->next;
		cur->argv = ft_free_char_matr(cur->argv);
		free(cur);
		cur = next;
	}
}
