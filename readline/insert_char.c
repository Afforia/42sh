/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 18:31:19 by thaley            #+#    #+#             */
/*   Updated: 2019/10/16 19:48:00 by thaley           ###   ########.fr       */
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
}

void		insert_char(char *c)
{
	int		i;
	int		save_curs;
	char	*tmp;

	i = 0;
	save_curs = 0;
	if (c[0] == '\0')
		return ;
	if (g_input->cursor_pos - g_input->prompt_len != g_input->input_len)
	{
		g_input->input_len = g_input->cursor_pos - g_input->prompt_len;
		save_curs = g_input->cursor_pos + ft_strlen(c);
		tmp = ft_strjoin(c, g_input->input + (g_input->cursor_pos - g_input->prompt_len));
	}
	else
		tmp = ft_strdup(c);
	while (tmp[i])
	{
		if (g_input->input_len + 1 >= MAX_CMDS)
			return ;
		// ft_memmove(g_input->input + (g_input->cursor_pos - g_input->prompt_len) + 1,\
		// g_input->input + (g_input->cursor_pos - g_input->prompt_len) ,\
		// MAX_CMDS - ((g_input->cursor_pos - g_input->prompt_len) - 1));
		g_input->input[(g_input->cursor_pos - g_input->prompt_len)] = tmp[i];
		if (g_input->cursor_pos % g_input->ws.ws_col == 0)
			ft_putstr_fd(tgetstr("do", NULL), STDIN_FILENO);
		ft_putstr_fd(tgetstr("ce", NULL), STDIN_FILENO);
		ft_putchar_fd(g_input->input[g_input->cursor_pos - g_input->prompt_len], STDOUT_FILENO);
		g_input->input_len++;
		g_input->cursor_pos++;
		i++;
	}
	if (save_curs != 0)
	{
		while (g_input->cursor_pos > save_curs)
		{
			g_input->cursor_pos--;
			if (g_input->cursor_pos % 80 == 0 && g_input->cursor_pos >= 80)
				ft_line_up();
			else
				ft_putstr_fd(tgetstr("le", NULL), STDIN_FILENO);
		}
	}
	if (tmp)
		free(tmp);
	tmp = NULL;
}
