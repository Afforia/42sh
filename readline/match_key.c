/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 20:12:29 by thaley            #+#    #+#             */
/*   Updated: 2019/10/02 21:16:17 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		not_move_hist(int direct)
{
	int		i;

	i = g_input->cursor_pos - g_input->prompt_len;
	while (i > 0 && !direct)
	{
		if (g_input->input[i] == '\n')
		{
			move_line_up();
			return (1);
		}
		i--;
	}
	while (i < g_input->input_len && direct)
	{
		if (g_input->input[i] == '\n')
		{
			move_line_down();
			return (1);
		}
		i++;
	}
	return (0);
}

void	clean_all(void)
{
	if (g_input->input_len == 0)
		return ;
	ft_bzero(g_input->input, g_input->input_len);
	g_input->input_len = 0;
	g_input->cursor_pos = g_input->prompt_len;
	ft_putstr_fd(tgetstr("cd", NULL), STDIN_FILENO);
}

int		match_key(char *c)
{
	if (c[0] == 127 && c[1] == '\0')
		delete_char();
	else if (!ft_strcmp(c, "\e[3~"))
		delete_char_two();
	else if (!ft_strcmp(c, "\e[D"))
		ft_move_left();
	else if (!ft_strcmp(c, "\e[C"))
		ft_move_right();
	else if (c[0] == 27 && c[1] == 91 && c[2] == 72)
		goto_home_of_line();
	else if (c[0] == 27 && c[1] == 91 && c[2] == 70)
		goto_end_of_line();
	else if (!ft_strcmp(c, "\e[1;5D"))
		move_word_left();
	else if (!ft_strcmp(c, "\e[1;5C"))
		move_word_right();
	if (c[0] == 7 && c[1] == '\0')
	{
		g_color = g_color * (-1);
		return (0);
	}
	else
		return (0);
	return (1);
}

int		match_history_key(char *c)
{
	if (!ft_strcmp(c, "\e[A"))
		history_move(0);
	else if (!ft_strcmp(c, "\e[B"))
		history_move(1);
	else if (!ft_strcmp(c, "\e[1;5A"))
		move_line_up();
	else if (c[0] == '\xc3' && c[1] == '\xa7' && !c[2])
		ft_copy(c);
	else if (c[0] == '\xc3' && c[1] == '\x87' && !c[2])
		ft_copy(c);
	else if (c[0] == '\xe2' && c[1] == '\x88' && c[2] == '\x9a' && !c[3])
		ft_paste();
	else if (c[0] == '\xe2' && c[1] == '\x89' && c[2] == '\x88' && !c[3])
		ft_cut(c);
	else if (c[0] == '\xcb' && c[1] == '\x9b' && !c[2])
		ft_cut(c);
	else if (!ft_strcmp(c, "\e[1;5B"))
		move_line_down();
	else if (c[0] == '\v' && !c[1])
		clean_all();
	else
		return (0);
	return (1);
}
