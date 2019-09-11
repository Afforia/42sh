/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_less_tst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/04 21:21:23 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_get_tless(t_cmdlist *cmd, int i, int j, char *ind)
{
	if ((int)ft_strlen(cmd->avcmd[i]) > j + 3)
		cmd->here = ft_strdup(ind + 3);
	else
	{
		if (cmd->avcmd[i + 1])
		{
			cmd->here = ft_strdup(cmd->avcmd[i + 1]);
			cmd->avcmd[i + 1][0] = '\0';
		}
		else
		{
			ft_print_msg(" : sintax error in command: ", cmd->avcmd[i]);
			return (-1);
		}
	}
	ind[0] = '\0';
	return (0);
}

int		ft_redir_2lesshd(t_cmdlist *cmd, int i)
{
	int			j;
	char		*ind;
	char		*heof;

	if (cmd->avcmd[i] && (cmd->avcmd[i][0] != '\'' && cmd->avcmd[i][0] != '"')
		&& (ind = (ft_strchr(cmd->avcmd[i], '<'))))
	{
		j = ind - cmd->avcmd[i];
		if (ft_strncmp(ind, TLESS, 3) == 0)
		{
			if (ft_get_tless(cmd, i, j, ind) == -1)
				return (-1);
		}
		else if (ft_strncmp(ind, DLESS, 2) == 0 && cmd->avcmd[i][j + 2] != '<')
		{
			if (!(heof = ft_get_heof(ind, cmd, i, j)))
				return (-1);
			cmd->here = ft_heredoc(heof);
			free(heof);
		}
	}
	return (0);
}

int		ft_get_heretext(t_cmdlist *cmd)
{
	int	i;

	i = 0;
	while (cmd->avcmd[i])
	{
		if (ft_redir_2lesshd(cmd, i) == -1)
			return (-1);
		i++;
	}
	cmd->avcmd = ft_press_matr(cmd->avcmd);
	return (0);
}
