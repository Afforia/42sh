/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:58:21 by thaley            #+#    #+#             */
/*   Updated: 2019/08/29 19:49:21 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "readline.h"

typedef struct		s_his
{
	char			**cmd;
	char			*path;
	int				amount;
	int				pos;
	int				cursor;
}					t_his;
t_his				*g_hist;

typedef struct		s_tab
{
	char			**file;
	int				**pos;
	int				amount;
}					t_tab;

typedef struct		s_cursor
{
	int				col;
	int				row;
}					t_cursor;

typedef struct		s_shell
{
	char			*term;
	struct termios	new_param;
	struct termios	old_param;
}					t_shell;

typedef struct		s_input
{
	t_cursor		cursor;
	struct winsize	ws;
	t_tab			auto_tab;
	char			input[MAX_CMDS];
	char			copy[MAX_CMDS];
	char			*prompt;
	char			old_input[MAX_CMDS];
	int				input_len;
	int				cursor_pos;
	int				save_row;
	int				save_col;
	int				old_cursor;
	int				heredoc;
	char			quotes;
	char			oldquotes;
	int				quotes_check;
	int				start;
	char			head;
	int				old_width;
	int				prompt_len;
}					t_input;
t_input				*g_input;

#endif
