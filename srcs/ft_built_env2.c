/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:24:59 by wveta             #+#    #+#             */
/*   Updated: 2019/09/18 12:33:54 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_unset_shell(char *parm)
{
	int i;

	if ((i = ft_get_ind_env(parm, g_shell)) != -1)
	{
		free(g_shell[i]);
		while (g_shell[i])
		{
			g_shell[i] = g_shell[i + 1];
			i++;
		}
	}
	i = 0;
	if ((i = ft_strequ(parm, "PATH")) == 1)
		ft_reset_cmd_list();
	return (1);
}

void	ft_exp_env(char *parm, char *value)
{
	int		i;
	char	*str;

	if (!(value) || !(parm))
		return ;
	if (!(str = malloc(sizeof(char) * (2 + ft_strlen(parm) +
			ft_strlen(value)))))
		exit_shell(1);
	str[0] = '\0';
	str = ft_strcat(str, parm);
	str = ft_strcat(str, "=");
	str = ft_strcat(str, value);
	if ((i = ft_get_ind_env(parm, g_envi->env)) == -1)
		g_envi->env = ft_add_shell(str, g_envi->env);
	else
	{
		free(g_envi->env[i]);
		g_envi->env[i] = str;
	}
}

void	ft_do_export(char *str, int flag, int j)
{
	int		i;
	char	*val;
	char	*parm;

	i = ft_strlen(str);
	if (j == (int)ft_strlen(str) && flag == 0 &&
	((val = ft_get_env2(str, g_shell))))
		ft_exp_env(ft_strdup(str), val);
	else if (j != (int)ft_strlen(str))
	{
		parm = ft_alloc_char(1 + j);
		parm[0] = '\0';
		parm = ft_strncpy(parm, str, j);
		val = ft_alloc_char(ft_strlen(str) - j);
		val[0] = '\0';
		val = ft_strcat(val, str + j + 1);
		ft_set_shell(parm, val);
		if (flag == 0)
			ft_exp_env(parm, val);
	}
	else if (j == (int)ft_strlen(str) && flag == 1)
		ft_unset_env_parm(str);
}

void	ft_go_export(char *str, int flag)
{
	char	*ptr;
	int		j;

	j = ft_strlen(str);
	if ((ptr = ft_strchr(str, '=')))
		j = ptr - str;
	if (ft_check_exp_name(str, j) == 0)
	{
		ptr = ft_alloc_char(37 + j);
		ptr[0] = '\0';
		ft_strcat(ptr, " : export: not a valid identifier '");
		ft_strncat(ptr, str, j);
		ft_strcat(ptr, "'");
		ft_print_msg(ptr, " ");
		ft_set_shell("?", "1");
		g_built_rc = 1;
		free(ptr);
	}
	else
		ft_do_export(str, flag, j);
}

int		ft_export(char **av)
{
	int i;
	int j;
	int flag;

	flag = 0;
	i = 0;
	while (av && av[++i])
	{
		if ((av[i][0] == '-') && ((j = 0) == 0))
		{
			while (av[i][++j])
			{
				if (av[i][j] != 'n')
				{
					ft_print_msg(" : usage: export [-n]", g_app_name);
					ft_set_shell("?", "2");
					g_built_rc = 2;
					return (1);
				}
				flag = 1;
			}
		}
		else
			ft_go_export(av[i], flag);
	}
	return (1);
}
