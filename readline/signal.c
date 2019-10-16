/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 20:07:10 by thaley            #+#    #+#             */
/*   Updated: 2019/10/03 07:53:52 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int	delete_nulls(char *buf)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < g_input->input_len)
	{
		while (g_input->input[i] == '\0' && i < g_input->input_len)
			i++;
		if (g_input->input[i] != '\0')
		{
			buf[j] = g_input->input[i];
			j++;
			i++;
		}
	}
	return (j);
}

void		signal_handler_quote(void)
{
	char	*tmp;
	char	buf[4097];
	int		j;

	j = 0;
	g_hist->cursor = g_hist->cursor + g_input->input_len;
	ft_bzero(buf, 4097);
	tmp = NULL;
	write(1, "\n", 1);
	// ft_putstr_fd(tgetstr("do", NULL), STDIN_FILENO);
	ft_putstr_fd(g_input->prompt, STDIN_FILENO);
	// g_input->cursor = get_cursor_pos();
	g_input->cursor_pos = g_input->prompt_len;
	if (g_hist->amount > 99)
		remade_hist();
	j = delete_nulls(buf);
	g_hist->cursor = j + 1;
	tmp = ft_strjoin(g_hist->cmd[g_hist->amount], buf);
	free(g_hist->cmd[g_hist->amount]);
	g_hist->cmd[g_hist->amount] = ft_strjoin(tmp, "\n");
	free(tmp);
	ft_bzero(g_input->input, g_input->input_len);
	g_input->input_len = 0;
	// g_input->cursor_pos = 0;
}

void		signal_handler_tab(int cursor)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_input->ws);
	g_input->cursor_pos = 0;
	update_cursor();
	ft_putstr_fd(g_input->prompt, 0);
	g_input->cursor = get_cursor_pos();
	ft_putstr_fd(g_input->input, 0);
	g_input->cursor_pos = cursor;
	update_cursor();
}

void		signal_handler(int sign)
{
	int		saved_cursor;

	(void)sign;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_input->ws);
	saved_cursor = g_input->cursor_pos;
	g_input->cursor_pos = 0;
	update_cursor();
	ft_putstr_fd(tgetstr("cl", NULL), 0);
	ft_putstr_fd(g_input->prompt, 0);
	g_input->cursor = get_cursor_pos();
	ft_putstr_fd(g_input->input, 0);
	g_input->cursor_pos = saved_cursor;
	update_cursor();
}

void		ft_signal_win_size(int signo)
{
	(void)signo;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_input->ws);
	if (g_input->ws.ws_col < (g_input->input_len + g_input->cursor.col)\
		&& g_input->input_len > 0)
	{
		ft_putstr_fd(tgetstr("cl", NULL), STDIN_FILENO);
		ft_putstr_fd(g_input->prompt, STDIN_FILENO);
		g_input->cursor_pos = g_input->prompt_len;
		ft_putstr_fd(g_input->input, STDIN_FILENO);
	}
	longjmp(g_cmd->ebuf2, g_cmd->jmp_code2);
}
