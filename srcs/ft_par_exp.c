/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_par_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/16 22:08:36 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_parm_ll(char *tmp)
{
	char	*val;

	ft_strcpy(tmp, tmp + 1);
	if ((val = ft_get_env(tmp)))
	{
		tmp[0] = '\0';
		tmp = ft_putfnbr(ft_strlen(val), tmp);
	}
	else
	{
		tmp[0] = '0';
		tmp[1] = '\0';
	}
	return (tmp);
}

char	*ft_get_parm_qq(char *s)
{
	char	*val;
	int		j;
	char	*tmp;

	if (((j = ft_strchr(s, ':') - s)) > 1)
	{
		tmp = ft_strnew(j + 1);
		tmp = ft_strncpy(tmp, s, j);
		if (!(val = ft_get_env(tmp)))
		{
			if (s[j + 1] == '-' || s[j + 1] == '=' || s[j + 1] == '?')
			{
				val = ft_strnew(ft_strlen(s) - (j + 1) + 1);
				val = ft_strcpy(val, s + j + 2);
				if (s[j + 1] == '=')
					ft_set_shell(tmp, val);
				else if (s[j + 1] == '?' && val[0] == '\0')
				{
					if (g_level == 0)
					{
						g_subs_rc = 1;
						ft_print_msg(": parameter null or not set: ", tmp);
						free(tmp);
						free(val);
						return (s);
					}
					else
						exit_shell(1);
				}
			}
		}
		else if (s[j + 1] == '+')
		{
			free(val);
			val = ft_strnew(ft_strlen(s) - (j + 1) + 1);
			val = ft_strcpy(val, s + j + 2);
		}
		free(tmp);
		free(s);
		if (!(val))
			val = ft_strdup("");
		return (val);
	}
	return (s);
}

char	*ft_get_parm_rr(char *s)
{
	char	*val;
	int		j;
	char	*tmp;

	if (((j = ft_strchr(s, '#') - s)) > 1)
	{
		tmp = ft_strnew(j + 1);
		tmp = ft_strncpy(tmp, s, j);
		if (s[j + 1] == '#')
			j++;
		if ((val = ft_get_env(tmp)))
		{
			free(tmp);
			tmp = ft_strnew(ft_strlen(s) - j + 1);
			tmp = ft_strcat(tmp, s + j + 1);
			j = ft_strlen(val) - ft_strlen(tmp);
			if (ft_strcmp(val + j, tmp) == 0)
				val[j] = '\0';
		}
		else
			val = ft_strdup("");
		free(tmp);
		free(s);
		return (val);
	}
	return (s);
}

char	*ft_get_parm_prc(char *s)
{
	char	*val;
	int		j;
	char	*tmp;

	if (((j = ft_strchr(s, '%') - s)) > 1)
	{
		tmp = ft_strnew(j + 1);
		tmp = ft_strncpy(tmp, s, j);
		if (s[j + 1] == '%')
			j++;
		if ((val = ft_get_env(tmp)))
		{
			free(tmp);
			tmp = ft_strnew(ft_strlen(s) - j + 1);
			tmp = ft_strcat(tmp, s + j + 1);
			if (ft_strncmp(val, tmp, ft_strlen(tmp)) == 0)
				val = ft_strcpy(val, val + ft_strlen(tmp));
		}
		else
			val = ft_strdup("");
		free(tmp);
		free(s);
		return (val);
	}
	return (s);
}

char	*ft_repl_subs(char *s, int *k, int i)
{
	char	*tmp;
	char	*ret;

	if (ft_test_sub(s + *k + 2, i - 2) == 1)
		return (s);
	tmp = ft_strncpy(ft_alloc_char(i - 1), s + *k + 2, i - 2);
	tmp[i - 2] = '\0';
	if (tmp[0] == '#')
		tmp = ft_get_parm_ll(tmp);
	else if (ft_strchr(tmp, ':'))
		tmp = ft_get_parm_qq(tmp);
	else if (ft_strchr(tmp, '#'))
		tmp = ft_get_parm_rr(tmp);
	else if (ft_strchr(tmp, '%'))
		tmp = ft_get_parm_prc(tmp);
	else
	{
		free(tmp);
		tmp = ft_get_parm_simple(s, k, i);
	}
	ret = ft_alloc_char(*(k) + ft_strlen(tmp) + ft_strlen(s + *(k) + i) + 1);
	ret[0] = '\0';
	ret = ft_strncat(ret, s, *(k));
	ret = ft_strcat(ret, tmp);
	ret = ft_strcat(ret, s + *k + i + 1);
	free(tmp);
	free(s);
	return (ret);
}
