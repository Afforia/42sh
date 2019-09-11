/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 20:21:52 by thaley            #+#    #+#             */
/*   Updated: 2019/09/01 13:16:35 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		ft_move_left(void)
{
	if (g_input->cursor_pos == 0)
		return ;
	if (g_input->input[g_input->cursor_pos - 1] == '\0')
	{
		ft_line_up();
		while (g_input->input[g_input->cursor_pos] != '\n')
			ft_move_right();
	}
	else
		g_input->cursor_pos--;
	update_cursor();
}

void		ft_move_right(void)
{
	if (g_input->cursor_pos == g_input->input_len)
		return ;
	if (g_input->input[g_input->cursor_pos] == '\n'\
		&& g_input->cursor_pos < g_input->input_len)
	{
		ft_line_down();
		while (g_input->input[g_input->cursor_pos - 1] != '\0')
			ft_move_left();
	}
	else
		g_input->cursor_pos++;
	update_cursor();
}

void		move_word_left(void)
{
	if (g_input->cursor_pos == 0)
		return ;
	g_input->cursor_pos--;
	while (g_input->cursor_pos > 0 &&
			(ft_isspace2(g_input->input[g_input->cursor_pos]) != 0))
		g_input->cursor_pos--;
	while (g_input->cursor_pos > 0 &&
	ft_isspace2(g_input->input[g_input->cursor_pos - 1]) == 0)
		g_input->cursor_pos--;
	update_cursor();
}

static int	check_last(void)
{
	ft_line_down();
	if (g_input->input[g_input->cursor_pos] == '\0'
		|| g_input->input[g_input->cursor_pos] == '\n')
	{
		while (g_input->input[g_input->cursor_pos - 1] != '\0')
			g_input->cursor_pos--;
		return (1);
	}
	return (0);
}

void		move_word_right(void)
{
	int		line;

	line = 0;
	if (g_input->input_len == 0 || g_input->cursor_pos == g_input->input_len)
		return ;
	if ((g_input->input[g_input->cursor_pos] == '\0' ||\
		g_input->input[g_input->cursor_pos] == '\n')\
		&& g_input->cursor_pos < g_input->input_len)
		line = check_last();
	if (!line)
	{
		while (g_input->input[g_input->cursor_pos] &&
			g_input->cursor_pos <= g_input->input_len &&
			ft_isspace2(g_input->input[g_input->cursor_pos]) == 0)
			g_input->cursor_pos++;
		while (g_input->cursor_pos <= g_input->input_len &&
			ft_isspace2(g_input->input[g_input->cursor_pos]) != 0)
			g_input->cursor_pos++;
		if (g_input->input[g_input->cursor_pos - 1] == '\n')
			g_input->cursor_pos--;
		if (g_input->cursor_pos > g_input->input_len)
			g_input->cursor_pos = g_input->input_len;
	}
	update_cursor();
}
