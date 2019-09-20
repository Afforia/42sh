/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/20 15:56:32 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_set_job_str(char *start, int end)
{
	g_job_start = start;
	g_job_end = end;
	start[end] = ';';
	return (1);
}

int			ft_ampers_test(char *str, int i, int start)
{
	if (str[i + start] == '&' && str[i + start - 1] != '&' &&
		str[i + start + 1] != '&' &&
		(str[i + start - 1] != '<') && (str[i + start - 1] != '>') &&
		(str[i + start + 1] != '<') && (str[i + start + 1] != '>'))
		return (1);
	return (0);
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
		else if (qflag == 0 && ((ft_strncmp(str + i + start, "&&", 2) == 0)
		|| (ft_strncmp(str + i + start, "||", 2) == 0)))
			g_and_or_line = 1;
		if (qflag == 0 && str[i + start] == ';')
			return (0);
		if (qflag == 0 && ft_ampers_test(str, i, start) == 1)
			return (ft_set_job_str(str + start, i));
		i++;
	}
	return (0);
}

char		**ft_get_sub_av(void)
{
	char	**ret;

	ret = NULL;
	if ((ret = (char **)malloc(sizeof(char *) * 5)))
	{
		ret[4] = NULL;
		ret[0] = ft_strdup("echo");
		ret[1] = ft_strdup(g_job_start);
		ret[1][g_job_end] = '\0';
		ret[2] = ft_strdup("|");
		ret[3] = ft_strdup(g_app_full_name);
	}
	return (ret);
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

char		*ft_get_shell_str(char *in, int len)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	if ((tmp = malloc(sizeof(char) * (len + 1))))
	{
		tmp[0] = '\0';
		tmp = ft_strncpy(tmp, in, len);
		tmp[len] = '\0';
		ret = ft_strdup("echo '");
		ret = ft_strfjoin(ret, tmp);
		free(tmp);
		ret = ft_strfjoin(ret, "' | ");
		ret = ft_strfjoin(ret, g_app_full_name);
	}
	return (ret);
}
