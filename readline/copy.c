/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 13:43:20 by thaley            #+#    #+#             */
/*   Updated: 2019/08/24 14:34:34 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int	copy_loop_aux(char *c, int *paste)
{
	int		i;

	i = 0;
	while (!ft_strcmp(c, "\e[1;2C"))
	{
		g_input->copy[i] = g_input->input[g_input->cursor_pos];
		delete_char_two();
		insert_char_color(g_input->copy[i], 0);
		if (g_input->cursor_pos == g_input->input_len)
			break ;
		ft_bzero(c, 10);
		i++;
		read(0, c, 10);
		if (c[0] == '\xe2' && c[1] == '\x88' && c[2] == '\x9a' && !c[3])
		{
			paste++;
			break ;
		}
		else if (ft_strcmp(c, "\e[1;2C"))
			break ;
	}
	return (i);
}

static int	copy_right(char *x)
{
	int		i;
	int		paste;
	int		save_curs;
	char	c[10];

	i = 0;
	paste = 0;
	ft_bzero(c, 10);
	save_curs = g_input->cursor_pos;
	ft_strcpy(c, x);
	i = copy_loop_aux(c, &paste);
	g_input->copy[i] = g_input->input[g_input->cursor_pos];
	delete_char_two();
	insert_char_color(g_input->copy[i], 0);
	if (c[0] == '\xcb' && c[1] == '\x9b' && !c[2])
		return (0);
	while (save_curs < g_input->cursor_pos)
		delete_char();
	insert_char(g_input->copy);
	if (paste)
		return (1);
	return (0);
}

static void	simple_copy(int start)
{
	int		i;

	i = 0;
	ft_bzero(g_input->copy, MAX_CMDS);
	if (g_input->cursor_pos == g_input->input_len)
	{
		while (g_input->input[g_input->cursor_pos - start - 1] != '\0')
			start++;
		ft_strcpy(g_input->copy, g_input->input +
		(g_input->cursor_pos - start));
	}
	else
	{
		start = g_input->cursor_pos;
		while (start < g_input->input_len)
		{
			g_input->copy[i] = g_input->input[start];
			start++;
			i++;
		}
	}
}

int			ft_copy(char *c)
{
	char	*copy;
	char	x[10];
	int		start;

	start = 0;
	ft_bzero(x, 10);
	if (g_input->input_len == 0)
		return (0);
	copy = NULL;
	if (c[0] == '\xc3' && c[1] == '\x87' && !c[2])
	{
		read(0, &x, 10);
		if ((!ft_strcmp(x, "\e[1;2C") &&
		(match_key(x) || match_history_key(x))))
			return (1);
		ft_bzero(g_input->copy, MAX_CMDS);
		if (!ft_strcmp(x, "\e[1;2C"))
		{
			if (copy_right(x))
				return (1);
		}
	}
	else
		simple_copy(start);
	return (0);
}
