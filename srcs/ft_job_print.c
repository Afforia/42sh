/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/26 23:14:55 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_num_to_str(int i)
{
	char	*num;

	num = ft_strnew(20);
	num[0] = '\0';
	num = ft_putfnbr(i, num);
	return (num);
}

char	*ft_print_job_pref(t_job *cur_job)
{
	char	*tmp;
	char	*num;
	int		i;

	tmp = NULL;
	if ((tmp = ft_strdup("")))
	{
		tmp = ft_strfjoin(tmp, "[");
		num = ft_num_to_str(cur_job->num);
		tmp = ft_strfjoin(tmp, num);
		free(num);
		tmp = ft_strfjoin(tmp, "]");
		i = ft_strlen(tmp);
		tmp = ft_strfjoin(tmp, " ");
		ft_strncpy(tmp + i, &cur_job->flag, 1);
		tmp = ft_strfjoin(tmp, " ");
	}
	return (tmp);
}

void	ft_print_start_job(t_job *cur_job)
{
	char	*tmp;
	char	*num;

	if ((tmp = ft_print_job_pref(cur_job)))
	{
		num = ft_num_to_str(cur_job->pgid);
		tmp = ft_strfjoin(tmp, num);
		free(num);
		tmp = ft_strfjoin(tmp, "\n");
		ft_putstr(tmp);
		free(tmp);
	}
}

void	ft_print_job_term(t_job *cur_job)
{
	char	*tmp;
	char	*num;

	if ((tmp = ft_print_job_pref(cur_job)))
	{
		num = ft_num_to_str(cur_job->pgid);
		tmp = ft_strfjoin(tmp, num);
		free(num);
		tmp = ft_strfjoin(tmp, "Terminated:            ");
		tmp = ft_strfjoin(tmp, cur_job->orig_cmd);
		tmp = ft_strfjoin(tmp, "\n");
		ft_putstr(tmp);
		free(tmp);
	}
}

void	ft_print_done_job(t_job *cur_job)
{
	char	*tmp;

	if (cur_job && ((cur_job->flag = ' ')) && (tmp = ft_print_job_pref(cur_job)))
	{
		tmp = ft_strfjoin(tmp, "Done                   ");
		tmp = ft_strfjoin(tmp, cur_job->orig_cmd);
		tmp = ft_strfjoin(tmp, "\n");
		ft_putstr(tmp);
		free(tmp);
	}
}
