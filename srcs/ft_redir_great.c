/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_great.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/04 21:21:50 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_redir_great(t_cmdlist *cmd, int i)
{
	t_greatflag	*f;
	char		*tmp;

	if (cmd->avcmd[i] && (cmd->avcmd[i][0] != '\'' && cmd->avcmd[i][0] != '"')
		&& (tmp = (ft_strchr(cmd->avcmd[i], '>'))))
	{
		if (!(f = ft_ini_great_fl()))
		{
			ft_print_msg(" : Error malloc ", "ft_redir_great");
			return (-1);
		}
		f->ind = (ft_strchr(cmd->avcmd[i], '>'));
		if ((ft_tst_great_fd(f, cmd, i) == -1) ||
		(ft_great_test_out(f, cmd, i) == -1) ||
		(ft_great_dup1(f->pref_fd, f->out_fd, cmd) == -1))
		{
			free(f);
			return (-1);
		}
		ft_reset_cmd_great(f->j, i, cmd);
		free(f);
	}
	return (0);
}
