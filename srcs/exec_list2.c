/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 21:00:14 by wveta             #+#    #+#             */
/*   Updated: 2019/09/09 10:43:39 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_set_var_ex_lst(int *j, int *l)
{
	char	*ret;
	
//	*i = ft_get_ind_env("PATH", g_envi->env);
	ret = ft_get_env("PATH");
	*j = 5;
	*l = 0;
	return (ret);
}

int		ft_test_cmd_file(t_cmdlist *cur_cmd)
{
	struct stat	buff;
	int			k;

	if (!(cur_cmd->find_path))
		return (-1);
	if (ft_check_file(cur_cmd->find_path) != 0)
		return (-1);
	if ((k = stat(cur_cmd->find_path, &buff)) == 0 &&
		(buff.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_putstr_fd(g_app_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cur_cmd->find_path, 2);
		ft_putstr_fd(" : is a directory\n", 2);
		ft_set_shell("?", "1");
		return (-1);
	}
	return (0);
}

