/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:54:28 by thaley            #+#    #+#             */
/*   Updated: 2019/10/16 19:09:40 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "../libft/libft.h"
# include "../includes/minishell.h"
# include "get_next_line.h"
# include <unistd.h>
# include <signal.h>
# include <term.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>
# include "define.h"
# include "struct.h"

char		*read_line(char *prompt);
void		open_fd(void);

void		creat_history(void);
void		history_move(int direct);
void		ft_history_put(void);

void		init_input(char *prompt);
t_shell		*init_term(t_shell *shell);
char		*init_loop(t_shell *shell);

void		signal_handler(int sign);
void		signal_handler_tab(int cursor);
void		signal_handler_quote(void);
void		ft_signal_win_size(int signo);

int			match_key(char *c);
int			match_history_key(char *c);

t_cursor	get_cursor_pos(void);
void		update_cursor(void);

void		ft_move_left(void);
void		ft_move_right(void);
void		move_word_left(void);
void		move_word_right(void);

void		goto_home_of_line(void);
void		goto_end_of_line(void);
void		move_line_down(void);
void		ft_line_up(void);
void		ft_line_down(void);
void		old_input(void);
void		modify_input(char *str);
void		input_from_file(char *str);
void		input_from_array(char *str);

int			autocomplition(char *c);
void		count_amount(char *path, char *tmp);
void		print_cmds(char **str);

char		**find_match(char *path, char *tmp);
void		search_cmd(void);
void		search_file(char *tmp);
char		*find_tail(char *str);
void		parse_path(char *tmp);

void		ft_free(char *str);
void		free_array(char **arr);
void		free_struct(t_shell **shell);

void		print_cmds(char **str);
void		ascii_sort(char **array);

void		ft_paste(void);
void		ft_cut(char *c);
int			ft_copy(char *c);
int			only_space(void);
int			parse_quotes(void);
int			printable(char *c, int i);
int			ft_isspace2(char st);

int			search_in_hist(void);

void		update_history(void);
void		remade_hist(void);

int			history_return_n(char *str);
char		*history_replace_n(char *str);
char		*finish_loop(char c, t_shell *shell);
int			ctrl_d(char *c);

void		insert_char_color(char c, int all);
void		insert_char(char *c);

void		delete_char_two(void);
void		delete_char(void);

char		*calc_path(char *s);

void		mall_check(void);

int			not_move_hist(int direct);
int			count_n(void);
void		move_cursor_hist(void);

void		move_line_up(void);
void		start_of_line(int up_down);

#endif
