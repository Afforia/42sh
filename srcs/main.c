/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 10:27:38 by wveta             #+#    #+#             */
/*   Updated: 2019/09/29 21:22:36 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_set_prcolor(char *ret, char *pr, int j)
{
	if (g_color == 1)
	{
		ret = ft_strcat(ret, CYN);
		if (j > 0)
			ret = ft_strcat(ret, "* ");
		ret = ft_strcat(ret, pr + j);
		ret = ft_strcat(ret, YEL);
		ret = ft_strcat(ret, " > ");
		ret = ft_strcat(ret, RESET);
	}
	else
	{
		if (j > 0)
			ret = ft_strcat(ret, "* ");
		ret = ft_strcat(ret, pr + j);
		ret = ft_strcat(ret, " > ");
	}
	return (ret);
}

char		*ft_get_name(void)
{
	char	*ret;
	char	*pr;
	int		j;

	pr = NULL;
	if (!(pr = ft_strnew(255)))
		exit_shell();
	getcwd(pr, 255);
	j = ft_strlen(pr) - 1;
	while (j >= 0 && pr[j])
	{
		if (pr[j] == '/')
			break ;
		j--;
	}
	if (!(ret = ft_strnew(255)))
		exit_shell();
	ret = ft_set_prcolor(ret, pr, j);
	free(pr);
	return (ret);
}

void		ft_free_list(void)
{
	t_listf	*tmp;

	while (g_envi->first_list)
	{
		if (ft_strequ(g_envi->first_list->file, "") == 1)
		{
			ft_putstr(g_envi->first_list->path);
			ft_putstr("\n");
		}
		if (g_envi->first_list->file)
			free(g_envi->first_list->file);
		if (g_envi->first_list->path)
			free(g_envi->first_list->path);
		tmp = g_envi->first_list;
		g_envi->first_list = g_envi->first_list->next;
		free(tmp);
	}
}

void		ft_final_free(void)
{
	int i;

	g_envi->env = ft_free_char_matr(g_envi->env);
	ft_free_list();
	free(g_envi);
	g_cmd->cmd_list = ft_free_char_matr(g_cmd->cmd_list);
	free(g_cmd);
	g_shell = ft_free_char_matr(g_shell);
	free(g_app_full_name);
	if (g_subshell == 1)
		return ;
	i = get_next_line(-7, NULL);
	ft_history_put();
}

int			main(int argc, char **argv, char **environ)
{
	char	*line_read;
	char	*pr;
	char	**lr;
	int		fd;

	if (!(g_cmd = malloc(sizeof(t_cmd))))
		exit_shell();
	if (!(g_envi = malloc(sizeof(t_env))))
		exit_shell();
	g_envi->first_list = NULL;
	g_envi->env = ft_dup_char_matr(environ);
	ft_init_glvar(argv);
	g_envi->first_list = ft_create_exe_list();
	g_cmd->jmp_code = setjmp(g_cmd->ebuf);
	ft_sig_set();
	while (g_subshell == 0 && argc == 1)
	{
		if (g_check == 1)
			exit(0);
		ft_print_jobs();
		pr = ft_get_name();
		line_read = rl_gets(pr);
		ft_parse_line(line_read);
		free(line_read);
	}
	g_subshell = 1;
	fd = STDIN_FILENO;
	if (argc > 1 && argv[1] && argv[1][0] != '<')
	{
		pr = ft_calc_full_path(ft_strdup(argv[1]));
		if (ft_check_file(pr, R_OK) != 0 || ((fd = open(pr, O_RDONLY)) < 0))
		{
			free(pr);
			ft_final_free();
			return (1);
		}
		free(pr);
	}
	line_read = NULL;
	lr = &line_read;
	while (get_next_line(fd, lr))
	{
		ft_sig_set();
		ft_print_jobs();
		ft_parse_line(line_read);
		free(line_read);
	}
	ft_final_free();
	return (0);
}
