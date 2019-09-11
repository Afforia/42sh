/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 20:54:11 by thaley            #+#    #+#             */
/*   Updated: 2019/08/31 20:56:17 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	goto_home_of_line(void)
{
	if (g_input->cursor_pos == 0)
		return ;
	g_input->cursor_pos = 0;
	update_cursor();
}

void	goto_end_of_line(void)
{
	if (g_input->cursor_pos == g_input->input_len)
		return ;
	g_input->cursor_pos = g_input->input_len;
	update_cursor();
}

void	move_line_down(void)
{
	if (g_input->cursor_pos + g_input->cursor.col <= g_input->input_len)
	{
		if (g_input->cursor_pos + g_input->ws.ws_col + 1 >= g_input->input_len)
			g_input->cursor_pos = g_input->input_len;
		else if (g_input->ws.ws_col - g_input->cursor.col\
				+ 1 <= g_input->cursor_pos)
			g_input->cursor_pos = g_input->cursor_pos + g_input->ws.ws_col;
		else
			g_input->cursor_pos = g_input->ws.ws_col - g_input->cursor.col + 1;
	}
	else
		g_input->cursor_pos = g_input->input_len;
	update_cursor();
}

void	ft_line_up(void)
{
	if (g_input->input_len == 0 || g_input->cursor_pos +\
		g_input->cursor.col <= g_input->ws.ws_col)
		return ;
	g_input->cursor_pos = g_input->cursor_pos - g_input->ws.ws_col;
	if (g_input->cursor_pos < 0)
		g_input->cursor_pos = g_input->cursor_pos + g_input->cursor.col - 1;
	while (g_input->input[g_input->cursor_pos] == '\0'\
			&& g_input->cursor_pos > 0)
		g_input->cursor_pos--;
	update_cursor();
}

void	ft_line_down(void)
{
	if (g_input->cursor_pos >= g_input->input_len)
		return ;
	if (g_input->cursor_pos + g_input->cursor.col < g_input->ws.ws_col)
		g_input->cursor_pos = g_input->cursor_pos +\
		g_input->ws.ws_col - g_input->cursor.col + 1;
	else
		g_input->cursor_pos = g_input->cursor_pos + g_input->ws.ws_col;
	while (g_input->input[g_input->cursor_pos] == '\0'\
		&& g_input->cursor_pos != g_input->input_len)
		g_input->cursor_pos--;
	update_cursor();
}
