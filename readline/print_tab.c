/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 13:02:01 by thaley            #+#    #+#             */
/*   Updated: 2019/09/01 14:44:32 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	print_loop(char **str, int len)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (len + ft_strlen(str[i]) >= g_input->ws.ws_col - ft_strlen(str[i]))
		{
			len = 0;
			if (g_input->cursor.row >= g_input->ws.ws_row)
				ft_putstr_fd(tgetstr("sf", NULL), STDIN_FILENO);
			else
				g_input->cursor.row++;
			g_input->cursor_pos = 0;
			update_cursor();
		}
		ft_putstr_fd(str[i], STDIN_FILENO);
		write(1, "  ", 2);
		len = len + ft_strlen(str[i]) + 2;
		i++;
	}
}

void		print_cmds(char **str)
{
	int		save_col;
	int		save_pos;
	int		len;

	len = 0;
	save_col = g_input->cursor.col;
	save_pos = g_input->cursor_pos;
	if (g_input->cursor.row >= g_input->ws.ws_row)
		ft_putstr_fd(tgetstr("sf", NULL), STDIN_FILENO);
	else
		g_input->cursor.row++;
	g_input->cursor.col = 1;
	g_input->cursor_pos = 0;
	update_cursor();
	print_loop(str, len);
	if (g_input->cursor.row >= g_input->ws.ws_row)
		ft_putstr_fd(tgetstr("sf", NULL), STDIN_FILENO);
	else
		g_input->cursor.row++;
	g_input->auto_tab.amount = 0;
	signal_handler_tab(save_pos);
}
