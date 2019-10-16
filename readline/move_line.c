/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 20:54:11 by thaley            #+#    #+#             */
/*   Updated: 2019/10/02 21:57:16 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	goto_home_of_line(void)
{
	if (g_input->cursor_pos == g_input->prompt_len)
		return ;
	while (g_input->cursor_pos > g_input->prompt_len)
	{
		if (g_input->input[(g_input->cursor_pos - g_input->prompt_len) - 1] == '\n')
			move_line_up();
		else
		{
			g_input->cursor_pos--;
			ft_putstr_fd(tgetstr("le", NULL), STDIN_FILENO);	
		}
	}
}

void	goto_end_of_line(void)
{
	if (g_input->cursor_pos - g_input->prompt_len == g_input->input_len)
		return ;
	while (g_input->cursor_pos - g_input->prompt_len < g_input->input_len)
	{
		if (g_input->input[g_input->cursor_pos - g_input->prompt_len] == '\n')
			move_line_down();
		else
		{
			g_input->cursor_pos++;
			ft_putstr_fd(tgetstr("nd", NULL), STDIN_FILENO);
		}
	}
}

void	move_line_up(void)
{
	int		i;
	int		start;
	int		n_count;
	int		prompt;

	prompt = -1;
	n_count = 0;
	i = -1;
	start = g_input->cursor_pos - g_input->prompt_len;
	while (++i < start)
	{
		if (g_input->input[i] == '\n')
			n_count++;
	}
	if (!n_count)
		return ;
	i = 0;
	while (g_input->cursor_pos > g_input->prompt_len
		&& g_input->input[g_input->cursor_pos - g_input->prompt_len - 1] != '\n')
	{
		g_input->cursor_pos--;
		ft_putstr_fd(tgetstr("le", NULL), STDIN_FILENO);
		i++;
	}
	start_of_line(1);
	while (i && g_input->input[g_input->cursor_pos - g_input->prompt_len] != '\n')
	{
		g_input->cursor_pos++;
		ft_putstr_fd(tgetstr("nd", NULL), STDIN_FILENO);
		i--;
	}
}

void	move_line_down(void)
{
	int		i;
	int		start;

	i = 0;
	start = g_input->cursor_pos - g_input->prompt_len;
	while (start && g_input->input[start - 1] != '\n')
	{
		start--;
		i++;
	}
	while (g_input->cursor_pos - g_input->prompt_len < g_input->input_len
		&& g_input->input[g_input->cursor_pos - g_input->prompt_len] != '\n')
	{
		g_input->cursor_pos++;
		ft_putstr_fd(tgetstr("nd", NULL), STDIN_FILENO);
	}
	start_of_line(0);
	while (i && g_input->cursor_pos - g_input->prompt_len < g_input->input_len
		&& g_input->input[g_input->cursor_pos - g_input->prompt_len] != '\n')
	{
		g_input->cursor_pos++;
		ft_putstr_fd(tgetstr("nd", NULL), STDIN_FILENO);
		i--;
	}
}

void	ft_line_up(void)
{
	char	*tmp;
	int		i;

	tmp = ft_strchr(g_input->input, '\n');
	i = (int)ft_strlen(tmp);
	if (!tmp || (i - g_input->cursor_pos) == g_input->prompt_len)
		return ;
	start_of_line(1);
	if (g_input->input[(g_input->cursor_pos - g_input->prompt_len)] == '\n')
		return ;
	while (g_input->input[(g_input->cursor_pos - g_input->prompt_len) + 1] != '\n' &&
		g_input->cursor_pos - g_input->prompt_len < g_input->input_len)
	{
		g_input->cursor_pos++;
		ft_putstr_fd(tgetstr("nd", NULL), STDIN_FILENO);
	}
}

void	ft_line_down(void)
{
	if (g_input->cursor_pos - g_input->prompt_len >= g_input->input_len)
		return ;
	if (g_input->input[(g_input->cursor_pos - g_input->prompt_len) + 1] == '\n'
		&& g_input->input[(g_input->cursor_pos - g_input->prompt_len)] != '\n')
	{
		g_input->cursor_pos++;
		ft_putstr_fd(tgetstr("nd", NULL), STDIN_FILENO);
	}
	start_of_line(0);
}

void	start_of_line(int up_down)
{
	int		i;

	i = -1;
	if (up_down == 1)
	{
		ft_putstr_fd(tgetstr("up", NULL), STDIN_FILENO);
		g_input->cursor_pos--;
	}
	else
	{
		ft_putstr_fd(tgetstr("do", NULL), STDIN_FILENO);
		g_input->cursor_pos++;
	}
	ft_putstr_fd(tgetstr("cr", NULL), STDIN_FILENO);
	while (g_input->input[g_input->cursor_pos - g_input->prompt_len - 1] != '\n'
		&& g_input->cursor_pos > g_input->prompt_len)
		g_input->cursor_pos--;
	if (g_input->cursor_pos == g_input->prompt_len)
	{
		while (++i < g_input->prompt_len)
			ft_putstr_fd(tgetstr("nd", NULL), STDIN_FILENO);
	}
}
