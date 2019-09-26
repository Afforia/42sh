/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:25:12 by wveta             #+#    #+#             */
/*   Updated: 2019/09/26 22:16:48 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_init_shell(void)
{
	int i;
	
	i = ft_calc_matr_rows(g_envi->env);
	if (!(g_shell = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	g_shell[i + 1] = NULL;
	i = -1;
	while (g_envi->env[++i])
		g_shell[i] = ft_strdup(g_envi->env[i]);
	if (!(g_shell[i] = ft_strdup("?=0")))
	{
		ft_free_char_matr(g_shell);
		g_shell = NULL;
		return (g_shell);
	}
	return (g_shell);
}

void	ft_init_glvar(char **av)
{
	g_check = 0;
	g_color = 1;
	g_shell = NULL;
	g_shell = ft_init_shell();
	g_and_or = 0;
	g_and_or_line = 0;
	g_not = 0;
	g_rc = 0;
	g_built_rc = 0;
	g_job_first = NULL;
	g_job_last = NULL;
	g_job_ind = 1;
	g_job = 0;
	g_envi->hash_first = NULL;
	g_subshell = 1 - isatty(STDIN_FILENO);
	g_parent_pid = getpid();
	g_app_name = ft_get_app_name(av[0]);
	if ((av[0][0] == '.') || (ft_check_file(av[0], X_OK) == -1))
	{
		g_app_full_name = ft_get_env("PWD");
		g_app_full_name = ft_strfjoin(g_app_full_name,"/");
		g_app_full_name = ft_strfjoin(g_app_full_name, g_app_name);
	}
	else
		g_app_full_name = ft_strdup(av[0]);
//	return ;
	g_terminal = STDIN_FILENO;
	g_is_interactive = isatty(g_terminal);
	if (g_is_interactive)
    {
    	while (tcgetpgrp (g_terminal) != (g_pgid = getpgrp ()))
        	kill (- g_pgid, SIGTTIN);
      	signal (SIGINT, SIG_IGN);
      	signal (SIGQUIT, SIG_IGN);
      	signal (SIGTSTP, SIG_IGN);
      	signal (SIGTTIN, SIG_IGN);
      	signal (SIGTTOU, SIG_IGN);
      	signal (SIGCHLD, SIG_IGN);
		g_pgid = getpid();
    	if (setpgid (g_pgid, g_pgid) < 0)
        {
        	perror ("Couldn't put the shell in its own process group");
        	exit (1);
        }
		tcsetpgrp(g_terminal, g_pgid);
		tcgetattr(g_terminal, &g_tmodes);
    }
}

int		ft_exit(char **av)
{
	int		rc;
	char	*str;

	rc = 0;
	if (av && av[2])
	{
		ft_print_msg(" : exit: too many arguments", " ");
		ft_set_shell("?", "1");
		g_built_rc = 1;
		return (1);
	}
	else if (av && av[1])
	{
		str = av[1];
		while (str && *str != '\0')
		{
			if (!(ft_isdigit(*str) && ((rc = rc * 10 + (*str - 48)) >= 0)))
			{
				ft_print_msg(" : exit: numeric argument required: ", av[1]);
				ft_set_shell("?", "1");
				g_built_rc = 1;
				return (1);
			}
			str++;			
		}
	}
	ft_final_free();
	exit(0);
	return (rc);
}

char	**ft_isnot(char **in)	
{
	char **av;
	
	av = in;
	if (ft_strcmp(av[0], "!") == 0)
	{
		g_not = 1;
		av[0][0] = '\0';
		av = ft_press_matr(av);
	}
	return (av);
}
