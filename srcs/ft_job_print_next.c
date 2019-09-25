/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_job_print_next.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/25 18:14:38 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_job_stop(t_job *cur_job)
{
	char	*tmp;

	if ((tmp = ft_print_job_pref(cur_job)))
	{
		tmp = ft_strfjoin(tmp, "  Stopped               ");
		tmp = ft_strfjoin(tmp, cur_job->orig_cmd);
		tmp = ft_strfjoin(tmp, "\n");
		ft_putstr(tmp);
		free(tmp);
	}
}
