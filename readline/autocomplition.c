/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 13:39:13 by thaley            #+#    #+#             */
/*   Updated: 2019/08/31 16:38:08 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		count_amount(char *path, char *tmp)
{
	DIR				*dir;
	struct dirent	*dn;

	g_input->auto_tab.amount = 0;
	if (!(dir = opendir(path)))
		return ;
	while ((dn = readdir(dir)))
	{
		if (!ft_strncmp(dn->d_name, tmp, ft_strlen(tmp)) &&
		(ft_strcmp(dn->d_name, ".") && ft_strcmp(dn->d_name, "..")))
			g_input->auto_tab.amount++;
	}
	closedir(dir);
}

static char	*find_arg(void)
{
	char	*ret;

	ret = &g_input->input[g_input->input_len - 1];
	while (*ret)
	{
		if (*ret == SPACE)
			break ;
		ret--;
	}
	return (ret);
}

static int	count_words(int i)
{
	int		count;

	count = 0;
	while (i < g_input->input_len)
	{
		if (ft_isspace2(g_input->input[i]))
		{
			count++;
			while (ft_isspace2(g_input->input[i] && i < g_input->input_len))
				i++;
		}
		i++;
	}
	return (count);
}

static int	check_input(void)
{
	int		i;
	int		count;

	i = 0;
	count = -1;
	while (i < g_input->input_len)
	{
		if (!ft_isspace(g_input->input[i]))
		{
			count = count_words(i);
			break ;
		}
		else
			count = -1;
		i++;
	}
	return (count);
}

int			autocomplition(char *c)
{
	char	*tmp;
	char	*str;
	int		count;

	tmp = NULL;
	str = NULL;
	count = 0;
	if (c[0] == 9 && !c[1])
	{
		if ((count = check_input()) == -1)
			return (1);
		if (count)
		{
			tmp = find_arg();
			str = ft_strdup(tmp + 1);
			search_file(str);
		}
		else if (g_input->input[0] == '/')
			search_file(str = ft_strdup(g_input->input));
		else
			search_cmd();
		return (1);
	}
	return (0);
}
