/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 20:27:55 by thaley            #+#    #+#             */
/*   Updated: 2019/08/24 20:28:22 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	delete_char_two(void)
{
	if (g_input->cursor_pos == g_input->input_len)
		return ;
	if (g_input->cursor_pos == 0)
		ft_memmove(g_input->input + g_input->cursor_pos, g_input->input +
				g_input->cursor_pos + 1, MAX_CMDS - g_input->cursor_pos);
	else
		ft_memmove(g_input->input + g_input->cursor_pos, g_input->input +
				g_input->cursor_pos + 1, MAX_CMDS - g_input->cursor_pos - 1);
	g_input->input_len--;
	ft_putstr_fd(tgetstr("ce", NULL), STDIN_FILENO);
	if (g_input->cursor_pos != g_input->input_len)
		ft_putstr_fd(g_input->input + g_input->cursor_pos, 1);
	update_cursor();
}

void	delete_char(void)
{
	if (g_input->cursor_pos == 0)
		return ;
	ft_move_left();
	ft_memmove(g_input->input + g_input->cursor_pos, g_input->input +
				g_input->cursor_pos + 1, MAX_CMDS - g_input->cursor_pos - 1);
	g_input->input_len--;
	ft_putstr_fd(tgetstr("ce", NULL), STDIN_FILENO);
	ft_putstr_fd(g_input->input + g_input->cursor_pos, 1);
	update_cursor();
}
