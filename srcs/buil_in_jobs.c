/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_in_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:41 by wveta             #+#    #+#             */
/*   Updated: 2019/09/27 17:45:56 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_job_fg(t_job *j)
{
//	int status;
//  	pid_t pid;

	tcsetpgrp (g_terminal, j->pgid);
    tcsetattr(g_terminal, TCSADRAIN, &g_tmodes);
    if (kill(- j->pgid, SIGCONT) < 0)
        ft_print_msg(": SIGCONT error ", " ");
//	else
//	{
	while (1)
		{
//	 		pid = waitpid (WAIT_ANY, &status, WUNTRACED);
		if (j && j->stat_job && ft_strncmp(j->stat_job, "Stopped", 7) != 0)
				break ;
	}
//	}
	tcsetpgrp (g_terminal, g_pgid);
	tcgetattr (g_terminal, &g_tmodes);
  	tcsetattr (g_terminal, TCSADRAIN, &g_tmodes);
}

int		ft_cmd_fg(char **av)
{
	t_job	*j;
	int 	i;
	char	*num;

	j = g_job_first;
	i = 0;
	while(j)
	{
		num = ft_num_to_str(j->num);	
		if (((av && av[1] && ft_strcmp(av[1], num) == 0) ||
			((!(av[1]) && j->flag == '+'))) && ((i = 1)))
			ft_job_fg(j);
		free(num);
		if (i == 1)
			break ;
		j = j->next;
	}
	if (i == 0)
	{
		if (av[1])
			ft_print_msg(": jobs: no such job: ", av[1]);
		else
			ft_print_msg(": jobs: current: no such job", " ");
		ft_set_shell("?", "1");
	}
	else
		ft_set_shell("?", "0");		
	return (1);
}

int		ft_cmd_bg(char **av)
{
	(void)av;
	return (1);
}

int		ft_cmd_kill(char **av)
{
	(void)av;
	return (1);
}
