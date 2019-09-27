/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 14:10:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/27 12:54:41 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_get_cmd_matr(t_listf *lst)
{
	int		j;
	int		count;
	t_listf	*cur;

	count = ft_len_list(lst);
	if (!(g_cmd->cmd_list = (char **)malloc(sizeof(char *) * (count + 12 + 1))))
		exit_shell();
	j = 0;
	cur = lst;
	while (j < count)
	{
		if (!(g_cmd->cmd_list[j] = ft_strdup(cur->file)))
		{
			g_cmd->cmd_list = ft_free_char_matr(g_cmd->cmd_list);
			exit_shell();
		}
		cur = cur->next;
		j++;
	}
	g_cmd->cmd_list[j] = ft_strdup("exit");
	g_cmd->cmd_list[j + 1] = ft_strdup("export");
	g_cmd->cmd_list[j + 2] = ft_strdup("unset");
	g_cmd->cmd_list[j + 3] = ft_strdup("set");
	g_cmd->cmd_list[j + 4] = ft_strdup("cd");
	g_cmd->cmd_list[j + 5] = ft_strdup("type");
	g_cmd->cmd_list[j + 6] = ft_strdup("printenv");
	g_cmd->cmd_list[j + 7] = ft_strdup("hash");
	g_cmd->cmd_list[j + 8] = ft_strdup("jobs");
	g_cmd->cmd_list[j + 9] = ft_strdup("fg");
	g_cmd->cmd_list[j + 10] = ft_strdup("bg");
	g_cmd->cmd_list[j + 11] = ft_strdup("kill");
	g_cmd->cmd_list[j + 12] = NULL;
}

int		ft_get_ind_env(char *s, char **shell)
{
	int i;

	if (!(shell) || !(s))
		return (-1);
	i = 0;
	while (shell[i])
	{
		if (ft_strncmp(shell[i], s, ft_strlen(s)) == 0
		&& shell[i][ft_strlen(s)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

t_listf	*ft_add_file(t_listf *first_list, char *full)
{
	t_listf *cur;
	char	*file;

	file = ft_get_file(full);
	if (!(cur = malloc(sizeof(t_listf))))
		exit_shell();
	cur->file = file;
	cur->path = full;
	cur->hash = hashly(file);
	cur->next = first_list;
	return (cur);
}

t_listf	*ft_add_exe_list(char *paths, int lpath, t_listf *first_list)
{
	DIR				*pdir;
	struct dirent	*drn;
	char			*path;
	char			*full;

	path = ft_set_dirpath(lpath, paths);
	if ((pdir = opendir(path)))
	{
		while ((drn = readdir(pdir)) != NULL)
		{
			if (!((ft_strequ(drn->d_name, ".")) ||
			(ft_strequ(drn->d_name, ".."))))
			{
				full = ft_alloc_char(lpath + drn->d_namlen + 2);
				full = ft_set_full_exe(drn->d_name, path, full);
				if (access(full, F_OK) == 0 && access(full, X_OK) == 0)
					first_list = ft_add_file(first_list, full);
				else
					free(full);
			}
		}
		closedir(pdir);
	}
	free(path);
	return (first_list);
}

t_listf	*ft_create_exe_list(void)
{
	int 	j;
	int 	l;
	char	*paths;

	g_envi->first_list = NULL;
	paths = ft_set_var_ex_lst(&j, &l);
	while (paths && paths[j + l])
	{
		if (paths[j + l] == ':')
		{
			g_envi->first_list = ft_add_exe_list(&paths[j],
			l, g_envi->first_list);
			j = j + l + 1;
			l = 0;
		}
		else
			l++;
	}
	if ((paths) && (g_envi->first_list = ft_add_exe_list(&paths[j],
		l, g_envi->first_list)))
		free (paths);
	ft_merge_sort(&g_envi->first_list);
	ft_get_cmd_matr(g_envi->first_list);
	return (g_envi->first_list);
}
