/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/17 20:18:22 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_test_job(char *str)
{
	int i;
	int qflag;

	i = 0;
	qflag = 0;
	while (str && str[i])
	{
		if (qflag == 0 && str[i] == '"')
			qflag = 1;
		else if ((qflag == 1 && str[i] == '"') ||
			(qflag == 2 && str[i] == '\''))
			qflag = 0;
		else if (qflag == 0 && str[i] == '\'')
			qflag = 2;
		if (qflag == 0 && str[i] == ';')
			return (0);
		if (qflag == 0 && str[i] == '&' && str[i - 1] == ' ' &&
			((str[i + 1] == '\0') || (str[i + 1] == ' ')))
			return (i);
		i++;
	}
	return (0);
}
