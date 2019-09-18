/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/18 21:20:01 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_set_job_str(char *start, int end)
{
	g_job_start = start;
	g_job_end = end;
	return (1);
}

int			ft_test_job(char *str, int start)
{
	int i;
	int qflag;

	i = 0;
	qflag = 0;
	while (str && str[i + start])
	{
		if (qflag == 0 && str[i + start] == '"')
			qflag = 1;
		else if ((qflag == 1 && str[i + start] == '"') ||
			(qflag == 2 && str[i] == '\''))
			qflag = 0;
		else if (qflag == 0 && str[i + start] == '\'')
			qflag = 2;
		if (qflag == 0 && str[i + start] == ';')
			return (0);
		if (qflag == 0 && str[i + start] == '&' && str[i + start - 1] == ' ' &&
			((str[i + start + 1] == '\0') || (str[i + start + 1] == ' ')))
			return (ft_set_job_str(str + start, i));
		i++;
	}
	return (0);
}

void		ft_locals_to_env(char **locals)
{
	int		i;
	char	*parm;
	char	*val;
	int		j;

	i = 0;
	while (locals && locals[i])
	{
		if ((val = ft_strchr(locals[i], '=')) &&
				((j = val - locals[i]) > 0))
		{
			parm = ft_strdup(locals[i]);
			parm[j] = '\0';
			val = ft_strdup(locals[i] + j + 1);
			ft_exp_env(parm, val);
		}
		i++;
	}
}
