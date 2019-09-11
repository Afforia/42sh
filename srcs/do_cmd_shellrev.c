/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd_shellrev.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/09/11 20:34:06 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_test_built_in(char *path)
{
	if (path && ft_strcmp(path, "exit") == 0)
		return (1);
	else if (path && g_envi->env && ft_strcmp(path, "set") == 0)
		return (1);
	else if (path && ft_strcmp(path, "cd") == 0)
		return (1);
	else if (path && ft_strcmp(path, "export") == 0)
		return (1);
	else if (path && ft_strcmp(path, "unset") == 0)
		return (1);
	else if (path && ft_strcmp(path, "echo") == 0)
		return (1);
	else if (path && ft_strcmp(path, "type") == 0)
		return (1);
	else if (path && ft_strcmp(path, "printenv") == 0)
		return (1);
	return (0);
}

t_cmdlist	*ft_free_cmd_list(t_cmdlist *first)
{
	t_cmdlist	*cur;
	t_cmdlist	*tmp;

	cur = first;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		if (tmp->avcmd)
			ft_free_char_matr(tmp->avcmd);
		if (tmp->built_in != 1 && tmp->find_path)
			free(tmp->find_path);
		if (tmp->here)
			free(tmp->here);
		free(tmp);
	}
	return (NULL);
}

void		ft_do_cmd_list(t_pipe *p_head, int flpi)
{
	int			fd0[2];
	int			fd1[2];

	ft_init_arr_fd(2, fd0, fd1);
	p_head->cur_cmd = p_head->first_cmd;
	p_head->cur_cmd->avcmd = ft_isnot(p_head->cur_cmd->avcmd);
	while (p_head->cur_cmd)
	{
		ft_get_heretext(p_head->cur_cmd);
		if (flpi > 0 && ((ft_set_fd_pipes(p_head, fd0, fd1) == -1)))
			return ;
		else if (flpi < 1 && (fd_set_nopipe(p_head) == -1))
			return ;
		if (ft_fork(p_head) == -1)
			return ;
		else if (p_head->cur_cmd->pid == 0)
			ft_child_pipe_exec(p_head->cur_cmd, flpi);
		else if (p_head->cur_cmd->pid > 0)
		{
			ft_parent_pipe_next(p_head->cur_cmd, fd0, fd1, flpi);
			p_head->cur_cmd = p_head->cur_cmd->next;
		}
	}
	ft_parent_wait(p_head, flpi, p_head->first_cmd);
}

void		ft_do_cmd_shell(char **av, int start, int flagpipe)
{
	int			nextpipe;
	t_pipe		*p_head;
	int			fl;

	p_head = ft_init_p_head(NULL, NULL);
	while ((start == 0 || av[start - 1]) && av[start])
	{
		fl = 0;
		if (!(p_head->cur_cmd = malloc(sizeof(t_cmdlist))))
			break ;
		ft_init_curcmd(p_head->cur_cmd);
		ft_set_cmd(p_head);
		if (((nextpipe = ft_get_count_in_pipe(av, start)) < 1 && flagpipe > 0)
			|| (ft_test_cmd_pipe(av, start, p_head) == -1))
			break ;
		fl = 1;
		if (flagpipe > 0)
			start = start + nextpipe + 1;
		else
			break ;
	}
	if (fl == 1)
		ft_do_cmd_list(p_head, flagpipe);
	p_head->first_cmd = ft_free_cmd_list(p_head->first_cmd);
	free(p_head);
}
