/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:31:19 by thaley            #+#    #+#             */
/*   Updated: 2019/08/31 22:24:16 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		insert_char_color(char c, int all)
{
	int		i;
	int		first;

	first = 1;
	i = g_input->cursor_pos;
	if (g_input->input_len + 1 >= MAX_CMDS)
		return ;
	ft_memmove(g_input->input + g_input->cursor_pos + 1, g_input->input
			+ g_input->cursor_pos, MAX_CMDS - g_input->cursor_pos - 1);
	g_input->input[g_input->cursor_pos] = c;
	ft_putstr_fd(tgetstr("ce", NULL), STDIN_FILENO);
	while (i <= g_input->input_len)
	{
		if (first || all)
		{
			ft_putstr_fd("\033[7m", STDIN_FILENO);
			first = 0;
		}
		write(1, &g_input->input[i], 1);
		ft_putstr_fd("\033[0m", STDERR_FILENO);
		i++;
	}
	g_input->input_len++;
	g_input->cursor_pos++;
	update_cursor();
}

static void	insert_memmove(char c)
{
	int j;

	j = g_input->cursor_pos;
	ft_memmove(g_input->input + g_input->cursor_pos + 1,\
	g_input->input + g_input->cursor_pos,\
	MAX_CMDS - g_input->cursor_pos - 1);
	g_input->input[g_input->cursor_pos] = c;
	while (j <= g_input->input_len && g_input->input[j] != '\0')
		j++;
	if (g_input->input[j] == '\0' && j <= g_input->input_len)
	{
		ft_memmove(g_input->input + j, g_input->input + j + 1,
		g_input->input_len - j);
		g_input->input[g_input->input_len] = '\0';
		g_input->input_len--;
	}
}

static int	insert_loop(char *c, int cur_len, int i)
{
	insert_memmove(c[i]);
	if (c[i] == '\n' && (int)ft_strlen(c) != i)
	{
		g_input->cursor_pos = g_input->cursor_pos +\
		g_input->ws.ws_col - cur_len;
		g_input->input_len = g_input->cursor_pos;
		cur_len = 0;
	}
	else
	{
		ft_putstr_fd(tgetstr("ce", NULL), STDIN_FILENO);
		ft_putstr_fd(g_input->input + g_input->cursor_pos, STDOUT_FILENO);
		cur_len++;
		g_input->input_len++;
		g_input->cursor_pos++;
	}
	return (cur_len);
}

void		insert_char(char *c)
{
	int		i;
	int		cur_len;

	i = 0;
	cur_len = g_input->prompt_len;
	while (c[i])
	{
		if (g_input->input_len + 1 >= MAX_CMDS)
			return ;
		cur_len = insert_loop(c, cur_len, i);
		update_cursor();
		i++;
	}
	update_cursor();
}
