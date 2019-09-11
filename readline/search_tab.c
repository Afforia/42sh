/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 12:50:01 by thaley            #+#    #+#             */
/*   Updated: 2019/08/31 17:01:12 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char		**find_match(char *path, char *tmp)
{
	DIR				*dir;
	struct dirent	*dn;
	char			**ret;
	int				i;

	count_amount(path, tmp);
	if (!g_input->auto_tab.amount)
		return (NULL);
	if (!(ret = (char **)malloc(sizeof(char *) *
		(g_input->auto_tab.amount + 1))))
		mall_check();
	if (!(dir = opendir(path)))
		return (ret);
	ret[g_input->auto_tab.amount] = (char *)NULL;
	i = -1;
	while ((dn = readdir(dir)))
	{
		if (!ft_strncmp(dn->d_name, tmp, ft_strlen(tmp)) &&
		(ft_strcmp(dn->d_name, ".") && ft_strcmp(dn->d_name, "..")))
			ret[++i] = ft_strdup(dn->d_name);
	}
	closedir(dir);
	return (ret);
}

static void	take_cmds(void)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_cmd->cmd_list[i])
	{
		if (!ft_strncmp(g_cmd->cmd_list[i], g_input->input, g_input->input_len))
		{
			g_input->auto_tab.file[j] = ft_strdup(g_cmd->cmd_list[i]);
			j++;
		}
		i++;
	}
	g_input->auto_tab.file[j] = NULL;
}

void		search_cmd(void)
{
	int		i;

	i = -1;
	while (g_cmd->cmd_list[++i])
	{
		if (!ft_strncmp(g_cmd->cmd_list[i], g_input->input, g_input->input_len))
			g_input->auto_tab.amount++;
	}
	if (!(g_input->auto_tab.file = (char **)malloc(sizeof(char *)\
	* (g_input->auto_tab.amount + 1))))
		mall_check();
	take_cmds();
	if (g_input->auto_tab.amount > 1)
		print_cmds(g_input->auto_tab.file);
	else if (g_input->auto_tab.amount == 1 &&\
	ft_strcmp(g_input->auto_tab.file[0], g_input->input))
		modify_input(g_input->auto_tab.file[0]);
	g_input->auto_tab.amount = 0;
	g_input->start = 0;
	free_array(g_input->auto_tab.file);
}

void		search_file(char *tmp)
{
	int				i;

	i = ft_strlen(tmp) - 1;
	g_input->start = 0;
	while (i > 0 && g_input->input[g_input->input_len\
		- g_input->start - 1] == tmp[i])
	{
		g_input->start++;
		i--;
	}
	parse_path(tmp);
	if (g_input->auto_tab.amount == 1)
		input_from_array(g_input->auto_tab.file[0]);
	else if (g_input->auto_tab.amount > 1)
	{
		ascii_sort(g_input->auto_tab.file);
		print_cmds(g_input->auto_tab.file);
	}
	g_input->auto_tab.amount = 0;
	free_array(g_input->auto_tab.file);
	ft_free(tmp);
}
