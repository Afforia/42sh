/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsepath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 21:06:43 by thaley            #+#    #+#             */
/*   Updated: 2019/08/30 17:21:47 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char		*calc_path(char *s)
{
	char	*tmp;

	tmp = ft_get_env("PWD");
	if (ft_strncmp(s, "./", 2) == 0)
		tmp = ft_strfjoin(tmp, s + 1);
	else if (s[0] != '.' && s[0] != '/')
	{
		tmp = ft_strfjoin(tmp, "/");
		tmp = ft_strfjoin(tmp, s);
	}
	if (ft_strncmp(s, "../", 2) == 0)
	{
		tmp = ft_path_level_up(tmp);
		tmp = ft_strfjoin(tmp, s + 2);
	}
	return (tmp);
}

char		*find_tail(char *str)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = ft_strlen(str) - 1;
	while (i > -1)
	{
		if (str[i] == '/')
		{
			ret = ft_strdup(str + i + 1);
			str[i + 1] = '\0';
			return (ret);
		}
		i--;
	}
	return (ret);
}

void		parse_path(char *tmp)
{
	char	*path;
	char	*tail;
	char	*temp;

	tail = NULL;
	path = NULL;
	temp = NULL;
	tail = find_tail(tmp);
	if (tmp[0] == '~')
	{
		temp = ft_get_env("HOME");
		path = ft_strjoin(temp, tmp + 1);
		ft_free(temp);
	}
	else if (tmp[0] == '.')
		path = calc_path(tmp);
	else if (tmp[0] != '/')
		path = ft_get_env("PWD");
	else
		path = ft_strdup(tmp);
	if (!tail)
		tail = ft_strdup(tmp);
	g_input->auto_tab.file = find_match(path, tail);
	free(path);
	free(tail);
}
