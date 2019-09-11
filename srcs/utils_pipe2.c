/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:50:36 by wveta             #+#    #+#             */
/*   Updated: 2019/09/11 13:16:43 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parent_close_pipe(int code, int fd0[2], int fd1[2])
{
	if (code == 0)
	{
		if (fd0[0] != -1)
			close(fd0[0]);
		if (fd0[1] != -1)
			close(fd0[1]);
		ft_init_arr_fd(0, fd0, fd1);
	}
	else
	{
		if (fd1[0] != -1)
			close(fd1[0]);
		if (fd1[1] != -1)
			close(fd1[1]);
		ft_init_arr_fd(1, fd0, fd1);
	}
}

void	ft_parent_pipe_next(t_cmdlist *cur_cmd, int fd0[2],
		int fd1[2], int flpi)
{
	if (flpi > 0 && cur_cmd->nr % 2 == 1)
		ft_parent_close_pipe(0, fd0, fd1);
	else if (flpi > 0 && cur_cmd->nr % 2 != 1)
		ft_parent_close_pipe(1, fd0, fd1);
}

void	ft_child_pipe_exec(t_cmdlist *cur_cmd, int flpi)
{
	int i;
	
	g_check = 1;
	if (flpi > 0)
		cur_cmd->avcmd = ft_cmd_replays(cur_cmd->avcmd);
	if (cur_cmd->built_in == 0)
	{
		if (!(cur_cmd->find_path = ft_get_file_path(
			cur_cmd->avcmd[0], g_envi->first_list)))
			cur_cmd->find_path = ft_strdup(cur_cmd->avcmd[0]);
	}
	if (flpi > 0)
	{
		ft_pipe_dup_ch_in(cur_cmd);
		ft_pipe_dup_ch_out(cur_cmd);
		if (cur_cmd->here && ft_get_redir_hd(cur_cmd) != 0)
			exit(1);
		if (ft_do_redir(cur_cmd) != 0)
			exit(1);
		cur_cmd = ft_local_assig(cur_cmd);
		if (!(cur_cmd->avcmd[0]))
		{
			cur_cmd->locals = ft_put_locals(cur_cmd->locals);
			exit(0);
		}
		if ((ft_test_built_in(cur_cmd->avcmd[0]) == 1)
			&& ft_built_in(cur_cmd->avcmd[0], cur_cmd->avcmd) == 1)
			exit(g_built_rc);
	}
	else
	{
		if (cur_cmd->here && ft_get_redir_hd(cur_cmd) != 0)
			exit(1);
	}
	if ((i = ft_test_cmd_file(cur_cmd)) == 0)
		execve(cur_cmd->find_path, cur_cmd->avcmd, g_envi->env);
	exit (1);
}

void	ft_pipe_wait_ch_fin(t_cmdlist *cur_cmd, t_cmdlist *first_cmd,
	t_cmdlist *last_cmd)
{
	int			status;
	int 		i;

	while (1)
	{
		cur_cmd = first_cmd;
		while (cur_cmd)
		{
			if (cur_cmd->pid != 0)
			{
				status = 0;
				if (cur_cmd->pid == waitpid(cur_cmd->pid, &status, 0))
				{
					if ((!(cur_cmd->next)) && (WIFEXITED(status)))
					{
						if ((i = WEXITSTATUS(status)) != 0)
							ft_set_shell("?", "1");
						else
							ft_set_shell("?", "0");			
					}
					cur_cmd->pid = 0;
				}
			}
			cur_cmd = cur_cmd->next;
			if (last_cmd->pid == 0)
				return ;
		}
	}
}
