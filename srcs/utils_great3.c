/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_great3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:25:30 by wveta             #+#    #+#             */
/*   Updated: 2019/09/04 21:23:35 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_greatflag	*ft_ini_great_fl(void)
{
	t_greatflag *f;

	if (!(f = malloc(sizeof(t_greatflag))))
		return (NULL);
	f->pref_fd = -7;
	f->file_redir = NULL;
	f->flag_all = 0;
	f->out_fd = -7;
	f->j = 0;
	return (f);
}

int			ft_tst_great_fd(t_greatflag *f, t_cmdlist *cmd, int i)
{
	f->j = f->ind - cmd->avcmd[i];
	f->flag_add = ft_set_flag_add(f->ind);
	if ((f->pref_fd = ft_set_pref_fd(cmd, i, f->j)) == -2)
		return (-1);
	if (cmd->avcmd[i][f->j + 1 + f->flag_add] == '&')
	{
		f->flag_all = 1;
		if ((int)ft_strlen(cmd->avcmd[i]) ==
			f->j + 1 + f->flag_all + f->flag_add)
			f->pref_fd = -1;
		else if (ft_isdigit(cmd->avcmd[i]
				[f->j + 1 + f->flag_all + f->flag_add]) == 1)
		{
			f->out_fd = ft_get_next_num(cmd->avcmd[i]
				+ f->j + 1 + f->flag_all + f->flag_add);
			if (ft_test_fd(f->out_fd, cmd->avcmd[i]) == -1)
				return (-1);
		}
	}
	return (0);
}

int			ft_tst_great_getfile(t_greatflag *f, t_cmdlist *cmd, int i)
{
	int l;

	l = f->j + 1 + f->flag_all + f->flag_add;
	if (f->flag_all == 1 && cmd->avcmd[i][l] == '-')
		f->file_redir = ft_strdup("/dev/null");
	else if ((int)ft_strlen(cmd->avcmd[i]) > l)
		f->file_redir = ft_strdup(f->ind + l - f->j);
	else if (cmd->avcmd[i + 1])
	{
		f->file_redir = ft_strdup(cmd->avcmd[i + 1]);
		cmd->avcmd[i + 1][0] = '\0';
	}
	else
	{
		ft_print_msg(" : sintax error in command ", "");
		return (-1);
	}
	cmd->avcmd[i][f->j] = '\0';
	f->file_redir = ft_calc_full_path(f->file_redir);
	return (0);
}

int			ft_great_testfile(t_greatflag *f)
{
	if (f->file_redir)
	{
		if (f->flag_add == 0 && (ft_strlen(f->file_redir) > 0))
			f->out_fd = open(f->file_redir, O_RDWR | O_CREAT |
			O_TRUNC, S_IRUSR | S_IWUSR);
		else if ((ft_strlen(f->file_redir) > 0))
			f->out_fd = open(f->file_redir, O_RDWR | O_CREAT |
			O_APPEND, S_IRUSR | S_IWUSR);
		if (f->out_fd == -1)
		{
			ft_print_msg(" : Error open file ", f->file_redir);
			free(f->file_redir);
			return (-1);
		}
		free(f->file_redir);
		f->file_redir = NULL;
		return (0);
	}
	return (-1);
}

int			ft_great_test_out(t_greatflag *f, t_cmdlist *cmd, int i)
{
	if (f->out_fd == -7)
	{
		if (ft_tst_great_getfile(f, cmd, i) == -1)
			return (-1);
		if (ft_great_testfile(f) == -1)
			return (-1);
	}
	return (0);
}
