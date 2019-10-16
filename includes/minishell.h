/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:01:23 by wveta             #+#    #+#             */
/*   Updated: 2019/10/16 17:22:06 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <string.h>

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <pwd.h>
# include <sys/stat.h>
# include <setjmp.h>
# include <fcntl.h>
# include <termios.h>
# include <../readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# define RED		"\x1B[31m"
# define GRN		"\x1B[32m"
# define YEL		"\x1B[33m"
# define BLU		"\x1B[34m"
# define MAG		"\x1B[35m"
# define CYN		"\x1B[1;36m"
# define WHT		"\x1B[37m"
# define BRO		"\x1B[32;31m"
# define BCN		"\x1B[34;46m"
# define BOR		"\x1B[30;41m"
# define BOC		"\x1B[30;46m"
# define BGR		"\x1B[30;42m"
# define BBR		"\x1B[30;42;41m"
# define BLBR		"\x1B[34;43m"
# define RESET		"\x1B[0m"
# define LESS		"<"
# define DLESS		"<<"
# define TLESS		"<<<"
# define LESSAND 	"<&"
# define GREAT		">"
# define DGREAT		">>"
# define GREATAND	">&"
# define CLOBBER	">|"
# define LESSGREAT	"<>"
# define UPR0		"0      abtnvfr            e"

typedef struct 			s_proc
{
	struct s_proc		*next;       
  	char				**argv;
	pid_t				pid;
	pid_t				pgid;
	char				completed;
	char				stopped;
	int					status;
}						t_proc;

typedef struct			s_listf
{
	char				*path;
	char				*file;
	unsigned int		hash;
	struct s_listf		*next;
}						t_listf;

typedef struct			s_listh
{
	char				*path;
	char				*file;
	unsigned int		hash;
	int					hashcount;
	struct s_listh		*next;
}						t_listh;

typedef struct			s_env
{
	char				**env;
	t_listf				*first_list;
	t_listh				*hash_first;
}						t_env;

typedef struct			s_job
{
	char				*orig_cmd;
	char				*stat_job;
	int					num;
	int					ind;
	char				flag;
	pid_t				pgid;
	int					ready;
	struct termios		j_tmod;
	t_proc				*first_proc;
	int					in;
	int					out;
	int					err;
	struct s_job		*next;
}						t_job;

typedef struct			s_cmdlist
{
	int					nr;
	char				**avcmd;
	char				*find_path;
	int					built_in;
	int					fd_pipe_in[2];
	int					fd_pipe_out[2];
	int					fd0;
	int					fd1;
	int					fd2;
	pid_t				pid;
	pid_t				pid_z;
	char				*here;
	char				**locals;
	int					flag_not;
	int					andor;
	int					child_pid;
	char				*original;
	struct s_cmdlist	*next;
}						t_cmdlist;
typedef struct			s_pipe
{
	t_cmdlist			*first_cmd;
	t_cmdlist			*last_cmd;
	t_cmdlist			*cur_cmd;
}						t_pipe;

t_env					*g_envi;
char					*g_app_name;
char					*g_app_full_name;
pid_t					g_pidchild;
int						g_level;
int						g_check;
int						g_color;
char					**g_shell;
int						g_and_or;
int						g_not;
int						g_skip;
int						g_rc;
int						g_built_rc;
int						g_subs_rc;
t_job					*g_job_first;
t_job					*g_job_last;
int						g_job;
char					*g_job_start;
int						g_job_end;
pid_t					g_parent_pid;
int						g_subshell;
int						g_and_or_line;
t_pipe					*g_pipe;
int						g_flpi;
pid_t 					g_pgid;
struct termios			g_tmodes;
int 					g_terminal;
int						g_is_interactive;
int						g_job_ind;
int						g_std_in;
int						g_std_out;
int						g_stderr;

typedef struct			s_cmd
{
	char				**cmd_list;
	jmp_buf				ebuf;
	int					jmp_code;
	jmp_buf				ebuf2;
	int					jmp_code2;
	int					stdin_copy;
	int					stdout_copy;
	int					stderr_copy;
}						t_cmd;
t_cmd					*g_cmd;

typedef struct			s_pipeflag
{
	int					flag;
	int					qflag;
	int					start;
	int					count;
	int					i;
}						t_pipeflag;
typedef struct			s_greatflag
{
	int					j;
	char				*ind;
	char				*file_redir;
	int					pref_fd;
	int					out_fd;
	int					flag_add;
	int					flag_all;
}						t_greatflag;

void					exit_shell();
int						ft_calc_matr_rows(char **in);
char					**ft_free_char_matr(char **matrix);
char					**ft_dup_char_matr(char **in);
int						ft_get_ind_env(char *s, char **shell);
t_listf					*ft_create_exe_list();
t_listf					*ft_add_exe_list(char *paths, int lpath,
						t_listf *first_list);
t_listf					*ft_add_file(t_listf *first_list, char *full);
void					ft_merge_sort(t_listf **headref);
char					*rl_gets(char *str);
char					*commands_generator(const char *text, int state);
char					**commands_completion(const char *text, int start,
						int end);
void					ft_parse_line(char *str);
int						ft_parse_cmd(char *str, int len);
void					ft_do_cmd_shell(char **av, int start, int flagpipe);
char					*ft_get_file_path(char *path, t_listf *first_list);
int						ft_built_in(char *path, char **av, char **locals);
void					ft_signal_handler(int signo);
void					ft_signal_handler_rl(int signo);
void					ft_main_signal_handler(int signo, char *line_read);
int						ft_built_cd(char **av, char **locals);
void					ft_cd(char *path, int flag, char **locals);
char					*ft_get_env(char *parm);
char					**ft_set_shell(char *parm, char *value);
int						ft_unset_env(char **parm);
void					ft_echo_parm(char *s, int flag, int len);
int						ft_echo(char **av);
int						ft_tst_home(char *s, int len);
int						ft_tst_env(char *s, int j);
char					*ft_get_home(char *s, int len);
char					*ft_get_my_home(void);
void					ft_get_cmd_matr(t_listf *lst);
void					ft_free_list(void);
void					ft_reset_cmd_list(void);
int						ft_check_file(char *find_path, int type);
int						ft_check_dir(char *find_path);
int						ft_is_dir(char *path);
int						ft_print_msg(char *s, char *name);
void					ft_del_quotes(char **args);
int						ft_len_list(t_listf	*lst);
char					*ft_set_dirpath(int lpath, char *paths);
char					*ft_set_full_exe(char *d_name, char *path, char *full);
char					*ft_alloc_char(int l);
char					*ft_tilda_path(char *path);
int						ft_print_env(void);
int						ft_tst_tilda(char *s, int j);
char					*ft_get_usr_tilda(char *path);
int						ft_tst_end_til(char *s, int j, int *flag);
void					ft_putstrf(char *s);
void					ft_final_free(void);
char					*ft_get_file(char *path);
char					**ft_split_pipes(char *cmd);
int						ft_get_count_in_pipe(char **av, int start);
char					**ft_get_pipe_av(char **av, int start);
int						ft_test_pipe(char **av, int start);
int						ft_test_built_in(char *path);
t_cmdlist				*ft_free_cmd_list(t_cmdlist *first);
void					ft_do_cmd_list(t_pipe *p_head, int flagpipe);
void					ft_do_cmd_shell(char **av, int start, int flagpipe);
t_cmdlist				*ft_redir_init(t_cmdlist *cmd);
t_cmdlist				*ft_redir_io_restore(t_cmdlist *cmd);
int						ft_do_redir(t_cmdlist *cmd);
char					**ft_press_matr(char **matr);
int						ft_redir_great(t_cmdlist *cmd, int i);
int						ft_redir_less(t_cmdlist *cmd, int i);
int						ft_redir_2less(t_cmdlist *cmd, int i);
int						ft_get_prev_num(char *s, int k);
int						ft_get_next_num(char *s);
char					*ft_calc_full_path(char *s);
char					*ft_get_heredoc(char *s);
int						ft_fd_dup_close(int in_fd, int i, int j,
						t_cmdlist *cmd);
void					ft_rest_in(t_cmdlist *cmd);
void					ft_rest_out(t_cmdlist *cmd);
void					ft_rest_err(t_cmdlist *cmd);
int						ft_set_flag_add(char *ind);
int						ft_test_fd(int fd, char *s);
int						ft_great_dup1(int pref_fd, int out_fd, t_cmdlist *cmd);
int						ft_great_dup2(int pref_fd, int out_fd, t_cmdlist *cmd);
void					ft_reset_cmd_great(int j, int i, t_cmdlist *cmd);
int						ft_set_pref_fd(t_cmdlist *cmd, int i, int j);
char					*ft_heredoc(char *eof);
void					ft_init_arr_fd(int code, int fd0[2], int fd1[2]);
void					ft_set_cmd_pipe(int code, t_cmdlist *cur_cmd,
						int fd0[2], int fd1[2]);
void					ft_set_cmd_pipe_out(int code, t_cmdlist *cur_cmd,
						int fd0[2], int fd1[2]);
void					ft_pipe_dup_ch_in(t_cmdlist *cur_cmd);
void					ft_pipe_dup_ch_out(t_cmdlist *cur_cmd);
void					ft_parent_close_pipe(int code, int fd0[2], int fd1[2]);
void					ft_parent_pipe_next(t_cmdlist *cur_cmd, int fd0[2],
						int fd1[2], int flpi);
void					ft_child_pipe_exec(t_cmdlist *cur_cmd, int flpi);
void					ft_pipe_wait_ch_fin(t_cmdlist *cur_cmd,
						t_cmdlist *first_cmd, t_cmdlist *last_cmd, int flpi);
t_pipe					*ft_init_p_head(t_cmdlist *first_cmd,
						t_cmdlist *last_cmd);
int						ft_set_fd_pipes(t_pipe	*p_head, int fd0[2],
						int fd1[2]);
int						ft_set_fd_pipes_2(t_pipe *p_head, int fd0[2],
						int fd1[2]);
int						fd_set_nopipe(t_pipe *p_head);
void					ft_parent_wait(t_pipe *p_head, int flpi/*,
						t_cmdlist *first_cmd*/);
int						ft_fork(t_pipe *p_head);
void					ft_init_curcmd(t_cmdlist *cur_cmd);
void					ft_set_cmd(t_pipe *p_head);
int						ft_test_cmd_pipe (char **av, int start, t_pipe *p);
t_pipeflag				*ft_pipe_split_ini(void);
void					ft_pipe_split_3(t_pipeflag *fl, char **ret,
						char const *str);
void					ft_pipe_split_4(t_pipeflag *fl, char **ret,
						char const *str);
void					ft_pipe_split_5(t_pipeflag *fl, char **ret,
						char const *str);
void					ft_pipe_split_6(t_pipeflag *fl, char const *str);
int						ft_get_word(char **ret, int count, int size,
						char const *s);
t_greatflag				*ft_ini_great_fl(void);
int						ft_tst_great_fd(t_greatflag *f, t_cmdlist *cmd, int i);
int						ft_great_testfile(t_greatflag *f);
int						ft_tst_great_getfile(t_greatflag *f, t_cmdlist *cmd,
						int i);
int						ft_great_test_out(t_greatflag *f, t_cmdlist *cmd,
						int i);
int						ft_get_heretext(t_cmdlist *cur);
int						ft_get_redir_hd(t_cmdlist *cmd);
char					*ft_get_heof(char *ind, t_cmdlist *cmd, int i, int j);
int						ft_redir_2lesshd(t_cmdlist *cmd, int i);
int						ft_get_tless(t_cmdlist *cmd, int i, int j, char *ind);
unsigned int			hashly(char *str);
char					*ft_clear_quotes(char *s);
char					*ft_replays(char *s);
char					*ft_repl_parm(char *s, int flag, int len);
char					*ft_repl_env(char *s, int *j);
char					*ft_repl_tilda(char *s, int j);
char					*ft_repl_end_til(char *s, int j, int *flag);
int						ft_repl_sym(char *s, int j);
char					*ft_set_var_ex_lst(int *j, int *l);
char					*ft_path_level_up(char *tmp);
char					*ft_tst_cdpath(char *str);
int						ft_test_cmd_file(t_cmdlist *cur_cmd);
char					*ft_get_app_name(char *s);
char					**ft_init_shell(void);
void					ft_init_glvar(char **av);
char					**ft_add_shell(char *str, char **shell);
int						ft_unset_shell(char *parm);
int						ft_export(char **av);
int						ft_check_exp_name(char *str, int j);
char					*ft_get_env2(char *parm, char **shell);
void					ft_unset_env_parm(char *str);
char					**ft_cmd_replays(char **str);
t_cmdlist				*ft_local_assig(t_cmdlist *cur_cmd);
char					**ft_put_locals(char **av);
void					ft_go_export(char *str, int flag);
int						ft_test_andor(void);
int						ft_exit(char **av);
char					**ft_isnot(char **in);
int						ft_shell_put_test(char *str);
int						ft_type(char **av);
int						ft_test_put_env(char *str);
int						ft_printenv(char **av);
char					*ft_repl_subs(char *s, int *k, int i);
int						ft_cmd_hash(char **av);
void					ft_print_one(char *av, int code);
int						ft_print_hash(void);
char					*ft_putfnbr(int nb, char *str);
void					ft_hash_all_del(char *str);
void					ft_hash_cmd_add(char *path, char *name);
int						ft_hash_usage(char *av);
char					*ft_get_hash_path(char *path);
int						ft_test_sub(char *str, int i);
char					*ft_get_parm_simple(char *s, int *k, int i);
int						ft_test_job(char *str, int start);
void					ft_exp_env(char *parm, char *value);
void					ft_locals_to_env(char **locals);
char					*ft_get_shell_str(char *in, int len);
void				    ft_sig_set(void);
int						ft_test_args(char *args);
int						ft_parse_pipe(char **ret);
int						ft_if_job(t_cmdlist *cur_cmd);
void					ft_print_start_job(t_job *cur_job);
t_job					*ft_del_job(t_job *del);
int						ft_set_job_str(char *start, int end);
void					ft_add_proc(t_cmdlist *cur_cmd);
char					*ft_print_job_pref(t_job *cur_job);
void					ft_update_job_status(t_job *cur);
void					ft_print_jobs(void);
void					ft_del_proc_list(t_proc *proc);
void					ft_print_job_list(int i, int start, int fl, char **av);
void					ft_print_job_line(t_job *job, int fl);
void					ft_print_if_job(char *str, int fl);
int						ft_cmd_jobs(char **av);
char					*ft_num_to_str(int i);
int						ft_ampers_test(char *str, int i, int start);
void					ft_set_job_plus(void);
int						ft_cmd_bg(char **av);
int						ft_cmd_fg(char **av);
int						ft_cmd_kill(char **av);
void					ft_test_cmd_list(pid_t pid, int status);
int						ft_test_sig_list(int signo);
int						ft_job_stopped (t_job *j);
int						ft_job_completed (t_job *j);
char					*ft_add_strnum(char *str, int i);
void					ft_test_job_status(pid_t pid, int status);
int						ft_put_job_status(t_job *job, t_proc *proc, int stat);
int						ft_cmd_bg(char **av);
int						ft_cmd_kill(char **av);
void					ft_test_tstp(pid_t pid);
t_job					*ft_new_job(t_cmdlist *cur_cmd);
void					ft_insert_job(t_job *cur_job);
void					ft_set_job_cont(t_job *j);

#endif
