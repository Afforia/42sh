/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe_split2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/09/20 16:34:47 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_pipe_split_5(t_pipeflag *fl, char **ret, char const *str)
{
	fl->qflag = 0;
	ft_get_word(ret, fl->count, fl->i + 1 - fl->start, str + fl->start);
	fl->count++;
	fl->flag = 0;
}

void		ft_pipe_split_6(t_pipeflag *fl, char const *str)
{
	if (ft_isspace(str[fl->i]) == 0 && str[fl->i] != '\0' &&
		fl->qflag == 0 &&
		fl->flag == 0 && (fl->i == 0 ||
		ft_isspace(str[fl->i - 1]) == 1
		|| str[fl->i - 1] == '|'))
	{
		fl->flag = 1;
		fl->start = fl->i;
	}
}

int			ft_parse_pipe(char **ret)
{
	int i;

	i = 0;
	while (ret && ret[i])
	{
		if (ft_strcmp(ret[i], "|") == 0)
		{
			if  (i == 0 ||  ft_strcmp(ret[i - 1], "|") == 0)
				return ((-1) * ft_print_msg(": parse error in pipeline: ", ret[0]));
		}
		i++;
	}
	if (ft_strcmp(ret[i - 1], "|") == 0)
		return ((-1) * ft_print_msg(": parse error in pipeline: ", ret[0]));
	return (0);
}
