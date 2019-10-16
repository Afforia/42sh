/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_paste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 13:43:13 by thaley            #+#    #+#             */
/*   Updated: 2019/10/16 19:11:03 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		ft_paste(void)
{
	int		i;
	int		j;
	char	buf[4096];

	i = -1;
	j = -1;
	ft_bzero(buf, 4096);
	if (g_input->copy[0] == '\0')
		return ;
	if (g_input->input_len < g_input->cursor_pos)
	{
		g_input->input_len = g_input->cursor_pos;
		while (g_input->input[g_input->input_len] != '\0'
		&& g_input->input[g_input->input_len] != '\n')
			g_input->input_len++;
	}
	while (++i < 4096)
	{
		while (g_input->copy[i] == '\0' && i < 4096)
			i++;
		if (i == 4096)
			break ;
		buf[++j] = g_input->copy[i];
	}
	insert_char(buf);
}

static void	option_x_cut(int ret_cursor)
{
	if (g_input->cursor_pos == 0)
		g_input->cursor_pos = g_input->input_len;
	if (g_input->cursor_pos == g_input->input_len)
	{
		ft_copy("\xc3\xa7");
		while (g_input->cursor_pos != 0)
			delete_char();
		g_input->cursor_pos = 0;
	}
	else if (g_input->cursor_pos > 0)
	{
		ft_copy("\xc3\xa7");
		g_input->cursor_pos = g_input->input_len;
		update_cursor();
		while (g_input->cursor_pos != ret_cursor)
			delete_char();
		update_cursor();
	}
}

void		ft_cut(char *c)
{
	int		ret_cursor;

	ret_cursor = g_input->cursor_pos;
	if (c[0] == '\xcb' && c[1] == '\x9b' && !c[2])
	{
		if (ft_copy("\xc3\x87"))
			return ;
		while (g_input->cursor_pos != ret_cursor)
			delete_char();
		update_cursor();
	}
	else
	{
		option_x_cut(ret_cursor);
	}
}
