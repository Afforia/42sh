/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/12 21:47:12 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_repl_check(char *s, int len, char *q, int j)
{
	char	*tmp;

	if (s[j] == '\\' && j + 1 < len && (s[j + 1] == '\''
		|| s[j + 1] == '"' || s[j + 1] == '\\'))
	{
		tmp = s + j;
		ft_strcpy(tmp, s + j + 1);
		return (1);
	}
	else if (*q == ' ' && (s[j] == '\'' || s[j] == '"'))
	{
		*q = s[j];
		tmp = s + j;
		ft_strcpy(tmp, s + j + 1);
		return (-1);
	}
	else if (*q != ' ' && (s[j] == *q))
	{
		*q = ' ';
		tmp = s + j;
		ft_strcpy(tmp, s + j + 1);
		return (1);
	}
	else if (s[j] == '\\' && *q != '\'')
	{
		tmp = s + j;
		ft_strcpy(tmp, s + j + 1);
	}
	return (0);
}

char	*ft_repl_parm(char *s, int flag, int len)
{
	int		j;
	char	q;
	int		k;

	j = -1;
	q = ' ';
	while (++j < len)
	{
		k = ft_repl_check(s, len, &q, j);
		if (k == 1)
			continue;
		else if (k == -1)
		{
			j--;
			continue;
		}
		if (q == ' ' && flag == 1)
			s = ft_repl_end_til(s, j, &flag);
		else if (q != '\'' && s[j] == '$')
		{
			if (flag == 1)
			{
				flag = 0;
				s = ft_repl_tilda(s, j);
			}
			s = ft_repl_env(s, &j);
		}
		len = ft_strlen(s);
	}
	if (flag == 1)
		s = ft_repl_tilda(s, j);
	return (s);
}

int		ft_repl_sym(char *s, int j)
{
	int		i;

	i = 1;
	while (s[j + i])
	{
		if (ft_strchr("!#%@\"\'^*()=\\.:$", s[j + i]))
			break ;
		i++;
	}
	return (i);
}

char	**ft_cmd_replays(char **str)
{
	char	**ret;
	int		i;

	ret = NULL;
	g_subs_rc = 0;
	if (str)
	{
		i = 0;
		while (str[i])
		{
			str[i] = ft_replays(str[i]);
			i++;
		}
		return (str);
	}
	return (ret);
}
