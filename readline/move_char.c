/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 20:21:52 by thaley            #+#    #+#             */
/*   Updated: 2019/10/02 20:58:32 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		ft_move_left(void)
{
	if (g_input->cursor_pos == g_input->prompt_len)
		return ;
	if (g_input->input[(g_input->cursor_pos - g_input->prompt_len) - 1] == '\n')
	{
		ft_line_up();
		while (g_input->input[(g_input->cursor_pos - g_input->prompt_len)] != '\n')
			ft_move_right();
	}
	else
	{
		g_input->cursor_pos--;
		ft_putstr_fd(tgetstr("le", NULL), STDIN_FILENO);
	}
}

void		ft_move_right(void)
{
	if ((g_input->cursor_pos - g_input->prompt_len) == g_input->input_len)
		return ;
	if (g_input->input[(g_input->cursor_pos - g_input->prompt_len)] == '\n'
		&& (g_input->cursor_pos - g_input->prompt_len) < g_input->input_len)
	{
		ft_line_down();
		while (g_input->input[(g_input->cursor_pos - g_input->prompt_len) - 1] != '\n')
			ft_move_left();
	}
	else
	{
		g_input->cursor_pos++;
		ft_putstr_fd(tgetstr("nd", NULL), STDIN_FILENO);
	}
}

void		move_word_left(void)
{
	if (g_input->cursor_pos == g_input->prompt_len)
		return ;
	if (g_input->input[(g_input->cursor_pos - g_input->prompt_len) - 1] != '\n')
	{
		g_input->cursor_pos--;
		ft_putstr_fd(tgetstr("le", NULL), STDIN_FILENO);
	}
	if (g_input->input[(g_input->cursor_pos - g_input->prompt_len)] < 33) //if we stand on the /n or space
	{
		while (g_input->cursor_pos - g_input->prompt_len > 0
			&& g_input->input[(g_input->cursor_pos - g_input->prompt_len)] < 33)
		{
			if (g_input->input[(g_input->cursor_pos - g_input->prompt_len) - 1] == '\n')
				ft_line_up(); // at the end of line
			g_input->cursor_pos--;
			ft_putstr_fd(tgetstr("le", NULL), STDIN_FILENO);
		}
		while (g_input->cursor_pos - g_input->prompt_len > 0
			&& g_input->input[(g_input->cursor_pos - g_input->prompt_len) - 1] > 32)
		{
			g_input->cursor_pos--;
			ft_putstr_fd(tgetstr("le", NULL), STDIN_FILENO);
		}
	}
	else if (g_input->input[(g_input->cursor_pos - g_input->prompt_len)] > 32)
	{
		while (g_input->input[(g_input->cursor_pos - g_input->prompt_len) - 1] > 32)
		{
			g_input->cursor_pos--;
			ft_putstr_fd(tgetstr("le", NULL), STDIN_FILENO);
		}
		while (g_input->cursor_pos - g_input->prompt_len > 0
			&& g_input->input[(g_input->cursor_pos - g_input->prompt_len) - 1] < 33)
		{
			if (g_input->input[(g_input->cursor_pos - g_input->prompt_len) - 1] == '\n')
				ft_line_up(); // at the end of line
			else if (g_input->input[(g_input->cursor_pos - g_input->prompt_len) - 1] != '\n')
			{
				g_input->cursor_pos--;
				ft_putstr_fd(tgetstr("le", NULL), STDIN_FILENO);
			}
		}
		while (g_input->input[(g_input->cursor_pos - g_input->prompt_len) - 1] > 32)
		{
			g_input->cursor_pos--;
			ft_putstr_fd(tgetstr("le", NULL), STDIN_FILENO);
		}
	}
}

void		move_word_right(void)
{
	if (g_input->input_len == 0 || (g_input->cursor_pos - g_input->prompt_len) == g_input->input_len)
		return ;
	if (g_input->input[g_input->cursor_pos - g_input->prompt_len] < 33)
	{
		while (g_input->input[g_input->cursor_pos - g_input->prompt_len] < 33)
		{
			if (g_input->input[g_input->cursor_pos - g_input->prompt_len] == '\n')
				ft_line_down();
			else
			{
				g_input->cursor_pos++;
				ft_putstr_fd(tgetstr("nd", NULL), STDIN_FILENO);
			}
		}
	}
	else
	{
		while (g_input->input[(g_input->cursor_pos - g_input->prompt_len)] > 32
			&& g_input->cursor_pos - g_input->prompt_len < g_input->input_len)
		{
			g_input->cursor_pos++;
			ft_putstr_fd(tgetstr("nd", NULL), STDIN_FILENO);
		}
		while (g_input->input[(g_input->cursor_pos - g_input->prompt_len)] < 33
			&& g_input->cursor_pos - g_input->prompt_len < g_input->input_len)
		{
			if (g_input->input[(g_input->cursor_pos - g_input->prompt_len)] == '\n')
				ft_line_down();
			else
			{
				g_input->cursor_pos++;
				ft_putstr_fd(tgetstr("nd", NULL), STDIN_FILENO);
			}
		}
		if (g_input->input[(g_input->cursor_pos - g_input->prompt_len) + 1] == '\0'
			&& g_input->cursor_pos - g_input->prompt_len < g_input->input_len)
		{
			g_input->cursor_pos++;
			ft_putstr_fd(tgetstr("nd", NULL), STDIN_FILENO);
		}
		else if (g_input->input[(g_input->cursor_pos - g_input->prompt_len) + 1] > 32
				&& g_input->input[(g_input->cursor_pos - g_input->prompt_len)] < 33)
		{
			g_input->cursor_pos++;
			ft_putstr_fd(tgetstr("nd", NULL), STDIN_FILENO);
		}
	}
}
