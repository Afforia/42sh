/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 20:27:22 by thaley            #+#    #+#             */
/*   Updated: 2019/08/31 18:20:50 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_cursor	get_cursor_pos(void)
{
	t_cursor	cursor;
	char		pos[20];
	int			ret;

	ft_bzero(pos, 20);
	ft_putstr_fd("\e[6n", STDIN_FILENO);
	ret = read(STDIN_FILENO, pos, 20);
	if (pos[0] != '\e')
	{
		g_input->head = pos[0];
		ft_bzero(pos, 20);
		ft_putstr_fd("\e[6n", STDIN_FILENO);
		ret = read(STDIN_FILENO, pos, 20);
	}
	pos[ret] = 0;
	ret = 2;
	cursor.row = ft_atoi(pos + ret);
	while (ft_isdigit(pos[ret]))
		ret++;
	cursor.col = ft_atoi(pos + ret + 1);
	return (cursor);
}

void		update_cursor(void)
{
	int		x;
	int		y;

	if (g_input->cursor.col + g_input->cursor_pos == g_input->ws.ws_col)
		x = g_input->ws.ws_col;
	else
		x = (g_input->cursor.col + g_input->cursor_pos) % g_input->ws.ws_col;
	if (g_input->cursor.col + g_input->cursor_pos == g_input->ws.ws_col)
		y = g_input->cursor.row;
	else
		y = g_input->cursor.row + ((g_input->cursor.col + g_input->cursor_pos)
		/ g_input->ws.ws_col);
	if (x == 0)
	{
		y--;
		x = g_input->ws.ws_col;
	}
	if (y > g_input->ws.ws_row)
	{
		y--;
		g_input->cursor.row--;
		ft_putstr_fd(tgetstr("sf", NULL), STDIN_FILENO);
	}
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), x - 1, y - 1), STDIN_FILENO);
}
