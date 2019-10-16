/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 21:15:50 by thaley            #+#    #+#             */
/*   Updated: 2019/10/16 19:11:03 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		old_input(void)
{
	int		i;

	ft_bzero(g_input->input, MAX_CMDS);
	goto_home_of_line();
	g_input->cursor_pos = 0;
	ft_putstr_fd(tgetstr("cd", NULL), STDIN_FILENO);
	if (g_input->old_input[0] == '\0')
		g_input->input_len = 0;
	else
	{
		ft_strcpy(g_input->input, g_input->old_input);
		g_input->input_len = ft_strlen(g_input->input);
	}
	i = g_input->input_len + g_input->prompt_len;
	ft_putstr_fd(g_input->input, STDIN_FILENO);
	g_input->cursor_pos = g_input->old_cursor;
	while (i > g_input->cursor_pos)
	{
		ft_putstr_fd(tgetstr("le", NULL), STDIN_FILENO);
		i--;
	}
	g_input->old_cursor = -1;
	ft_bzero(g_input->old_input, MAX_CMDS);
}

char		*ft_find_start(char *s1, char *s2)
{
	while (*s1)
	{
		while (*s2 && *s1 == *s2)
		{
			s1++;
			s2++;
		}
		if (*s1 != *s2)
			break ;
	}
	return ((char *)s1);
}

void		input_from_array(char *str)
{
	int			i;
	int			j;
	struct stat	buf;

	j = 0;
	buf.st_mode = 0;
	i = g_input->input_len - 1;
	while (i > 0 && g_input->input[i] != ' ' && g_input->input[i] != '/')
	{
		delete_char();
		i--;
	}
	insert_char(str);
	stat(g_input->input + i, &buf);
	if (S_ISDIR(buf.st_mode))
		insert_char("/");
}

void		modify_input(char *str)
{
	if (g_input->old_cursor == -1)
	{
		ft_bzero(g_input->old_input, MAX_CMDS);
		ft_strcpy(g_input->old_input, g_input->input);
		g_input->old_cursor = g_input->cursor_pos;
	}
	ft_bzero(g_input->input, g_input->input_len);
	goto_home_of_line();
	g_input->input_len = 0;
	ft_putstr_fd(tgetstr("cd", NULL), STDIN_FILENO);
	insert_char(str);
}
