/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/09/20 16:32:18 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_pipeflag	*ft_pipe_split_ini(void)
{
	t_pipeflag	*fl;

	fl = malloc(sizeof(t_pipeflag));
	fl->i = -1;
	fl->count = 0;
	fl->flag = 0;
	fl->qflag = 0;
	return (fl);
}

void		ft_pipe_split_3(t_pipeflag *fl, char **ret, char const *str)
{
	if (fl->flag == 1)
	{
		ft_get_word(ret, fl->count, fl->i - fl->start, str + fl->start);
		fl->count++;
	}
	ft_get_word(ret, fl->count, 1, str + fl->i);
	fl->count++;
	fl->flag = 0;
}

void		ft_pipe_split_4(t_pipeflag *fl, char **ret, char const *str)
{
	ft_get_word(ret, fl->count, fl->i - fl->start, str + fl->start);
	fl->count++;
	fl->flag = 0;
}
