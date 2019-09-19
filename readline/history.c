/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:04:04 by thaley            #+#    #+#             */
/*   Updated: 2019/09/19 17:28:15 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	from_file(char *buf)
{
	int		i;
	int		j;

	i = 0;
	j = open(g_hist->path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	while ((get_next_line(j, &buf)) > 0)
	{
		g_hist->cmd[g_hist->amount] = ft_strdup(buf);
		i = ft_strlen(g_hist->cmd[g_hist->amount]);
		while (i > -1 && g_hist->cmd[g_hist->amount][i] == 7)
		{
			g_hist->cmd[g_hist->amount][i] = '\0';
			i--;
		}
		history_return_n(g_hist->cmd[g_hist->amount]);
		buf[0] = '\0';
		g_hist->amount++;
	}
	close(j);
}

void		creat_history(void)
{
	char	*buf;
	char	*tmp;

	if (!(g_hist = (t_his *)malloc(sizeof(t_his))))
		mall_check();
	g_hist->cursor = 0;
	if (!(g_hist->cmd = (char **)malloc(sizeof(char *) * 101)))
		mall_check();
	ft_bzero(g_hist->cmd, 101);
	if (!(buf = (char *)malloc(sizeof(char) * 4097)))
		mall_check();
	ft_bzero(buf, 4097);
	g_hist->path = ft_alloc_char(500);
	g_hist->path[0] = '\0';
	g_hist->amount = 0;
	if ((tmp = ft_get_my_home()))
	{
		g_hist->path = ft_strcat(g_hist->path, tmp);
		free(tmp);
	}
	g_hist->path = ft_strcat(g_hist->path, "/.history");
	from_file(buf);
	g_hist->pos = g_hist->amount;
	free(buf);
}

int			count_n(void)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (i < g_input->input_len)
	{
		if (g_input->input[i] == '\n')
			count++;
		i++;
	}
	if (count > 1)
		return (1);
	return (0);
}

void		history_move(int direct)
{
	if (not_move_hist(direct))
		return ;
	if (direct && g_hist->pos < g_hist->amount)
		g_hist->pos++;
	else if (!direct && g_hist->pos > -1)
		g_hist->pos--;
	if (!g_hist->cmd[g_hist->pos] && g_hist->pos == g_hist->amount
		&& g_input->old_cursor != -1)
		old_input();
	else if (g_hist->pos != -1 && g_hist->cmd[g_hist->pos])
		modify_input(g_hist->cmd[g_hist->pos]);
	else if (g_hist->pos == -1)
		g_hist->pos = 0;
}

void		ft_history_put(void)
{
	int		fd;
	int		i;

	i = 0;
	fd = open(g_hist->path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd > 0)
	{
		while (g_hist->cmd[i])
		{
			write(fd, history_replace_n(g_hist->cmd[i]),
				ft_strlen(g_hist->cmd[i]));
			write(fd, "\n", 1);
			free(g_hist->cmd[i]);
			i++;
		}
		close(fd);
		free(g_hist->path);
		free(g_hist->cmd);
		g_hist->cmd = NULL;
		free(g_hist);
	}
}
