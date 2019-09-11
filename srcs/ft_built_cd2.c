/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_cd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 14:10:12 by wveta             #+#    #+#             */
/*   Updated: 2019/08/31 16:29:10 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_dir_exist(char *find_path)
{
	if ((access(find_path, F_OK)) == -1)
		return (-1);
	return (0);
}

char	*ft_get_test_path(int l, char *cdpath, char *str)
{
	char	*ret;

	ret = NULL;
	if ((ret = malloc(sizeof(char) * (l + ft_strlen(str) + 2))))
	{
		ret[0] = '\0';
		ret = ft_strncat(ret, cdpath, l);
		ret = ft_strcat(ret, "/");
		ret = ft_strcat(ret, str);
		if (ft_check_dir_exist(ret) != 0)
		{
			free(ret);
			ret = NULL;
		}
	}
	return (ret);
}

char	*ft_tst_cdpath_loop(char *cdpath, char *str, int j, int l)
{
	char	*ret;

	ret = NULL;
	while (cdpath[j + l])
	{
		if (cdpath[j + l] == ':')
		{
			if ((ret = ft_get_test_path(l, &cdpath[j], str)))
				return (ret);
			else
			{
				j = j + l + 1;
				l = 0;
			}
		}
		else
			l++;
	}
	ret = ft_get_test_path(l, &cdpath[j], str);
	return (ret);
}

char	*ft_tst_cdpath(char *str)
{
	char	*cdpath;
	int		j;
	int		l;
	char	*ret;

	if (!(str) || (str[0] == '/' || str[0] == '.'
		|| !(cdpath = ft_get_env("CDPATH"))))
		return (str);
	j = 0;
	l = 0;
	ret = ft_tst_cdpath_loop(cdpath, str, j, l);
	free(cdpath);
	if (ret)
	{
		free(str);
		return (ret);
	}
	return (str);
}
