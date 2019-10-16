/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 20:27:55 by thaley            #+#    #+#             */
/*   Updated: 2019/09/29 15:36:51 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	delete_char_two(void)
{
	if (g_input->cursor_pos == g_input->input_len + g_input->prompt_len)
		return ;
	if (g_input->cursor_pos == g_input->prompt_len)
		ft_memmove(g_input->input + (g_input->cursor_pos - g_input->prompt_len), g_input->input +
				(g_input->cursor_pos - g_input->prompt_len) + 1, MAX_CMDS - (g_input->cursor_pos - g_input->prompt_len));
	else
		ft_memmove(g_input->input + (g_input->cursor_pos - g_input->prompt_len), g_input->input +
				(g_input->cursor_pos - g_input->prompt_len) + 1, MAX_CMDS - (g_input->cursor_pos - g_input->prompt_len) - 1);
	g_input->input_len--;
	ft_putstr_fd(tgetstr("dc", NULL), STDIN_FILENO);
}

void	delete_char(void)
{
	if (g_input->cursor_pos == 0)
		return ;
	ft_move_left();
	ft_memmove(g_input->input + (g_input->cursor_pos - g_input->prompt_len), g_input->input +\
				(g_input->cursor_pos - g_input->prompt_len) + 1,\
				MAX_CMDS - (g_input->cursor_pos - g_input->prompt_len) - 1);
	g_input->input_len--;
	ft_putstr_fd(tgetstr("dc", NULL), STDIN_FILENO);
}
