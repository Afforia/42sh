/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_hist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 16:01:43 by thaley            #+#    #+#             */
/*   Updated: 2019/10/03 09:33:13 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		move_cursor_hist(void)
{
	goto_home_of_line();
	ft_putstr_fd(tgetstr("cr", NULL), STDIN_FILENO);
	ft_putstr_fd(tgetstr("cd", NULL), STDIN_FILENO);
}

void		remade_hist(void)
{
	int		i;

	i = 0;
	while (i < g_hist->amount)
	{
		if (i == 0)
			free(g_hist->cmd[i]);
		if (i < 99)
			g_hist->cmd[i] = g_hist->cmd[i + 1];
		else
			g_hist->cmd[i] = NULL;
		i++;
	}
	g_hist->amount = 99;
}

static void	put_in_buff(char *buf)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < g_input->input_len)
	{
		if (g_input->input[j] != '\0')
		{
			buf[i] = g_input->input[j];
			i++;
		}
		j++;
	}
}

void		update_history(void)
{
	int		i;
	char	buf[MAX_CMDS];

	if (g_hist->amount > 99)
		remade_hist();
	i = -1;
	while (g_input->input[++i])
	{
		if (g_input->input[i] > 32)
			break ;
	}
	if (g_input->input[i] == '\0')
		return ;
	ft_bzero(buf, MAX_CMDS);
	put_in_buff(buf);
	g_hist->cmd[g_hist->amount] = ft_strfjoin(g_hist->cmd[g_hist->amount], buf);
	g_hist->amount++;
	g_hist->pos = g_hist->amount;
}
