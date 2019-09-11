/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_less.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/09 17:53:46 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_get_fd_byname(int i, t_cmdlist *cmd, char *ind)
{
	char		*file_redir;
	int			len;

	if (((int)ft_strlen(cmd->avcmd[i]) >= ind - cmd->avcmd[i] + 2) &&
		(cmd->avcmd[i][ind - cmd->avcmd[i] + 2] == '-'))
		file_redir = ft_strdup("/dev/null");
	else if ((int)ft_strlen(cmd->avcmd[i]) > ind - cmd->avcmd[i] + 1)
		file_redir = ft_strdup(ind + 1);
	else if (cmd->avcmd[i + 1])
	{
		file_redir = ft_strdup(cmd->avcmd[i + 1]);
		cmd->avcmd[i + 1][0] = '\0';
	}
	else
	{
		ft_print_msg(" : sintax error in command ", "");
		return (-1);
	}
	cmd->avcmd[i][ind - cmd->avcmd[i]] = '\0';
	file_redir = ft_calc_full_path(file_redir);
	len = open(file_redir, O_RDONLY);
	if (len == -1)
		ft_print_msg(" : Error open file ", file_redir);
	free(file_redir);
	return (len);
}

int		ft_get_fd_bynum(int i, int j, t_cmdlist *cmd)
{
	int			in_fd;
	char		buf[5];

	in_fd = -1;
	if (cmd->avcmd[i][j + 1] == '&' &&
		ft_isdigit(cmd->avcmd[i][j + 2]) == 1)
	{
		in_fd = ft_get_next_num(cmd->avcmd[i] + j + 2);
		if (in_fd > 2 && read(in_fd, buf, 0) == -1)
		{
			ft_print_msg(" : Bad file descriptor ", cmd->avcmd[i] + j + 2);
			in_fd = -2;
		}
	}
	return (in_fd);
}

int		ft_get_next_num(char *s)
{
	int	ret;
	int	i;

	ret = -1;
	i = 0;
	while (s[i])
	{
		if (!(ft_isdigit(s[i])))
			return (ret);
		i++;
	}
	ret = ft_atoi(s);
	return (ret);
}

int		ft_get_prev_num(char *s, int k)
{
	int	ret;
	int	i;

	ret = -1;
	i = 0;
	while (i < k && s[i])
	{
		if (!(ft_isdigit(s[i])))
			return (ret);
		i++;
	}
	ret = ft_atoi(s);
	return (ret);
}

int		ft_redir_less(t_cmdlist *cmd, int i)
{
	int			j;
	char		*ind;
	int			in_fd;

	if (cmd && cmd->avcmd[i] && (cmd->avcmd[i][0] != '\'' && cmd->avcmd[i][0]
		!= '"') && (ind = (ft_strchr(cmd->avcmd[i], '<'))))
	{
		in_fd = -1;
		j = ind - cmd->avcmd[i];
		if (ft_strncmp(ind, LESS, 1) == 0 &&
			((int)ft_strlen(cmd->avcmd[i]) - 1 == j || (cmd->avcmd[i][j + 1]
			!= '<' && cmd->avcmd[i][j + 1] != '>')))
		{
			if ((in_fd = ft_get_fd_bynum(i, j, cmd)) == -2)
				return (-1);
			if (in_fd == -1 &&
				((in_fd = ft_get_fd_byname(i, cmd, ind)) < 0))
				return (-1);
			return (ft_fd_dup_close(in_fd, i, j, cmd));
		}
	}
	return (0);
}
