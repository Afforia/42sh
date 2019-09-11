/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 17:56:56 by thaley            #+#    #+#             */
/*   Updated: 2019/08/29 19:49:53 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			ctrl_d(char *c)
{
	if (c[0] == 4 && !c[1])
	{
		if (!g_input->heredoc && !g_input->input_len)
			return (1);
		else if (g_input->heredoc && !g_input->input_len)
			return (1);
	}
	return (0);
}

char		*finish_loop(char c, t_shell *shell)
{
	tcsetattr(0, TCSANOW, &shell->old_param);
	if (c == 4 && !g_input->heredoc && !g_input->input_len)
		return ("exit");
	else if (c == 12)
		return ("clear");
	else if (c == 3)
		return (NULL);
	else if (c == 4 && g_input->heredoc && !g_input->input_len)
		return ("\x04");
	else
	{
		ft_bzero(g_input->old_input, MAX_CMDS);
		if (!g_input->heredoc)
			update_history();
		g_input->cursor_pos = g_input->input_len;
		if (g_input->input_len == 0 || only_space())
			return (NULL);
		else if (g_input->heredoc)
			return (g_input->input);
		else
			return (g_hist->cmd[g_hist->amount - 1]);
		if (g_hist->cursor)
			g_input->cursor_pos = g_hist->cursor;
	}
	return (NULL);
}
