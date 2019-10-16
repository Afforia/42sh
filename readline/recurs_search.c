/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:55:35 by thaley            #+#    #+#             */
/*   Updated: 2019/10/16 19:11:03 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	home_of_rec_hist(char *str)
{
	int		i;

	i = ft_strlen(str);
	while (i > 0)
	{
		if (str[i - 1] == '\n')
			ft_putstr_fd(tgetstr("up", NULL), STDIN_FILENO);
		i--;
	}
	ft_putstr_fd(tgetstr("cr", NULL), STDIN_FILENO);
}

static void	remade_search_input(char *str, int i, char c)
{
	if (c == 127)
		str[i] = '\0';
	else if (ft_isprint(c))
		str[i] = c;
	home_of_rec_hist(g_input->dop_input);
	ft_putstr_fd(tgetstr("cd", NULL), STDIN_FILENO);
	ft_putstr_fd("rev-i-search `", STDIN_FILENO);
	ft_putstr_fd(str, STDIN_FILENO);
	ft_putstr_fd("\033[5m", STDIN_FILENO);
	ft_putstr_fd("_", STDIN_FILENO);
	ft_putstr_fd(RESET, STDIN_FILENO);
	ft_putstr_fd(": ", STDIN_FILENO);
	if (c == 127)
		ft_bzero(g_input->dop_input, MAX_CMDS);
}

static void	return_cmd(char *tmp, int his_pos)
{
	g_input->cursor_pos = g_input->prompt_len;
	home_of_rec_hist(g_hist->cmd[his_pos]);
	ft_putstr_fd(tgetstr("cr", NULL), STDIN_FILENO);
	ft_putstr_fd(tgetstr("cd", NULL), STDIN_FILENO);
	ft_putstr_fd(g_input->prompt, STDIN_FILENO);
	if (his_pos > -1 && tmp[0] != '\0')
		insert_char(g_hist->cmd[his_pos]);
	ft_bzero(tmp, MAX_BSIZE);
}

static int	find_match_hist(int j, char *tmp, int i, char c)
{
	remade_search_input(tmp, i, c);
	i++;
	while (j > -1)
	{
		if (ft_strstr(g_hist->cmd[j], tmp))
		{
			ft_bzero(g_input->dop_input, MAX_CMDS);
			ft_strcpy(g_input->dop_input, g_hist->cmd[j]);
			ft_putstr_fd(g_hist->cmd[j], STDIN_FILENO);
			break ;
		}
		j--;
	}
	return (j);
}

static int	recur_search_loop(char *c, int j, char *tmp)
{
	int		i;

	i = 0;
	while (c[0] != '\n' && c[0] != 3 && c[0] != 4)
	{
		ft_bzero(c, 6);
		read(0, c, 6);
		if (ft_isprint(c[0]))
		{
			j = find_match_hist(j, tmp, i, c[0]);
			i++;
		}
		else if ((c[0] == 127 || c[0] == 3 || c[0] == 4) && !c[1])
		{
			if (c[0] == 3)
				tmp[0] = '\0';
			if (c[0] == 4)
				tmp = ft_strcpy(tmp, "exit");
			remade_search_input(tmp, i > 0 ? --i : i, c[0]);
			j = g_hist->amount - 1;
			if (tmp[0])
				j = find_match_hist(j, tmp, i, c[0]);
		}
	}
	return (j);
}

int			search_in_hist(void)
{
	char	tmp[MAX_BSIZE];
	char	c[6];
	int		j;

	if (g_input->input_len != 0)
		return (0);
	j = g_hist->amount - 1;
	ft_bzero(g_input->dop_input, MAX_CMDS);
	ft_bzero(tmp, MAX_BSIZE);
	move_cursor_hist();
	remade_search_input("\0", 0, '\0');
	j = recur_search_loop(c, j, tmp);
	return_cmd(tmp, j);
	return (1);
}
