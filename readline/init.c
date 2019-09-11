/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:15:47 by thaley            #+#    #+#             */
/*   Updated: 2019/08/30 19:43:03 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void		null_all(void)
{
	ft_bzero(g_input->input, MAX_CMDS);
	ft_bzero(g_input->copy, MAX_CMDS);
	ft_bzero(g_input->old_input, MAX_CMDS);
	g_input->old_cursor = -1;
	g_input->heredoc = 0;
	g_input->quotes = '\0';
	g_input->quotes_check = 0;
	g_input->head = '\0';
	g_input->input_len = 0;
	g_input->cursor_pos = 0;
	g_input->auto_tab.pos = 0;
	g_input->auto_tab.amount = 0;
	g_input->auto_tab.file = NULL;
}

void			init_input(char *prompt)
{
	open_fd();
	if (!g_hist)
		creat_history();
	else
		g_hist->pos = g_hist->amount;
	if (!(g_input = (t_input *)malloc(sizeof(t_input))))
		mall_check();
	g_input->prompt = ft_strdup(prompt);
	null_all();
	g_input->prompt_len = ft_strlen(prompt);
	if (!ft_strncmp(prompt, "heredoc", 7))
		g_input->heredoc++;
	else
		g_input->prompt_len -= 16;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_input->ws);
	g_input->old_width = g_input->ws.ws_col;
}

t_shell			*init_term(t_shell *shell)
{
	if (!(shell = (t_shell *)malloc(sizeof(t_shell))))
		mall_check();
	if (!(shell->term = ft_get_env("TERM")))
		shell->term = ft_strdup("xterm-256color");
	if (tgetent(NULL, shell->term) == -1)
		return (shell);
	if (tcgetattr(0, &shell->new_param) == -1)
		return (shell);
	if (tcgetattr(0, &shell->old_param) == -1)
		return (shell);
	shell->new_param.c_lflag &= ~(ICANON | ECHO | ISIG);
	shell->new_param.c_cc[VMIN] = 1;
	shell->new_param.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &shell->new_param) == -1)
		return (shell);
	return (shell);
}

static char		multi_line(void)
{
	free(g_input->prompt);
	g_input->prompt = ft_strdup(" > ");
	signal_handler_quote();
	return (0);
}

char			*init_loop(t_shell *shell)
{
	char		c[20];
	int			i;

	g_cmd->jmp_code2 = setjmp(g_cmd->ebuf2);
	signal(SIGWINCH, ft_signal_win_size);
	while (1)
	{
		ft_bzero(c, 20);
		i = read(0, &c, 20);
		if (match_key(c) || match_history_key(c) || autocomplition(c))
			continue ;
		else if (c[0] == '\x12' && !c[1] && search_in_hist())
		{
			ft_bzero(c, 20);
			c[0] = 10;
		}
		else if (c[0] == 10 && !c[1] && parse_quotes())
			c[0] = multi_line();
		if ((c[0] == 10 || c[0] == 3 || ctrl_d(c) ||
			c[0] == 12 || c[0] == 7) && !c[1])
			return (ft_strdup(finish_loop(c[0], shell)));
		if (printable(c, i))
			insert_char(c);
	}
	return (NULL);
}
