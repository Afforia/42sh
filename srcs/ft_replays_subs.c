/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replays_subs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/12 21:53:05 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_ret_subs(char *str, int i)
{
	char *tmp;

	tmp = ft_alloc_char(i + 4);
	tmp[0] = '\0';
	tmp = ft_strncat(tmp, str - 2, i + 3);
	ft_print_msg(": bad substitution: ", tmp);
	free(tmp);
	g_subs_rc = 1;
	ft_set_shell("?", "1");
	return (1);
}

int		ft_test_sub(char *str, int i)
{
	int j;

	j = 0;
	if (i > 0)
	{
		while (j <= i)
		{
			if (ft_strchr("!#%@\"\'^*()=\\.:$", str[j]))
				return (ft_ret_subs(str, i));
			j++;
		}
		return (0);
	}
	return (ft_ret_subs(str, i));
}

char	*ft_repl_subs(char *s, int *k, int i)
{
	char	*tmp;
	char	*val;
	int		len;

	if (ft_test_sub(s + *k + 2, i - 2) == 1)
		return (s);
	tmp = ft_alloc_char(i - 1);
	tmp = ft_strncpy(tmp, s + *k + 2, i - 2);
	tmp[i - 2] = '\0';
	i = i + 1;
	len = 0;
	if ((val = ft_get_env(tmp)))
		len = ft_strlen(val);
	free(tmp);
	tmp = ft_alloc_char(ft_strlen(s) + len - (i - 1) + 1);
	tmp[0] = '\0';
	tmp = ft_strncat(tmp, s, *k);
	if (len > 0 && ((tmp = ft_strcat(tmp, val))))
		free(val);
	tmp = ft_strcat(tmp, s + *k + i);
	if (len == 0)
		(*k)--;
	free(s);
	return (tmp);
}

char	*ft_repl_env(char *s, int *k)
{
	int		i;
	char	*tmp;
	char	*val;

	if (s[*k + 1] == '{' && ((i = (ft_strchr(s + *k, '}') - (s + *k))) > 1))
		return (ft_repl_subs(s, k, i));
	i = ft_repl_sym(s, *k);
	tmp = ft_alloc_char(i);
	tmp = ft_strncpy(tmp, s + *k + 1, i - 1);
	tmp[i - 1] = '\0';
	if ((val = ft_get_env(tmp)))
	{
		free(tmp);
		tmp = ft_alloc_char(ft_strlen(s) + ft_strlen(val) - (i - 1) + 1);
		tmp[0] = '\0';
		tmp = ft_strncat(tmp, s, *k);
		tmp = ft_strcat(tmp, val);
		tmp = ft_strcat(tmp, s + *k + i);
		free(val);
		free(s);
		return (tmp);
	}
	free(tmp);
	return (s);
}
