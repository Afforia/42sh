/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_full_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:14:54 by wveta             #+#    #+#             */
/*   Updated: 2019/08/29 13:06:41 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_path_level_up(char *tmp)
{
	int i;

	i = ft_strlen(tmp) - 1;
	while (i > -1)
	{
		if (tmp[i] == '/')
			break ;
		i--;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_calc_full_path(char *s)
{
	char	*tmp;

	if (s[0] == '/')
		return (s);
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
	free(s);
	s = tmp;
	return (s);
}
