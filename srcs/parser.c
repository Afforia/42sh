/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:17:45 by wveta             #+#    #+#             */
/*   Updated: 2019/09/13 19:05:24 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_file_path(char *path, t_listf *first_list)
{
	t_listf			*cur;
	char			*ret;
	unsigned int	hash;

	if (!(path) || !(cur = first_list))
		return (NULL);
	if ((ret = ft_get_hash_path(path)))
		return (ret);
	hash = hashly(path);
	while (cur)
	{
		if (hash == cur->hash && ft_strequ(path, cur->file) == 1)
		{
			ret = ft_strdup(cur->path);
			return (ret);
		}
		cur = cur->next;
	}
	return (NULL);
}

void	ft_parse_cmd(char *str, int len)
{
	char *cmd;
	char **args;

	if (!(str) || str[0] == '\0' || str[0] == ';' || ft_test_andor() == 0)
		return ;
	if (!(cmd = ft_strnew((size_t)len)))
		exit_shell();
	cmd = ft_strncpy(cmd, str, (size_t)len);
	args = ft_split_pipes(cmd);
	if (args && *args)
	{
		ft_do_cmd_shell(args, 0, ft_test_pipe(args, 0));
	}
	args = ft_free_char_matr(args);
	free(cmd);
}

void	ft_init_parse_int(int *i, int *i_cmd, int *qflag)
{
	*i = 0;
	*i_cmd = 0;
	*qflag = 0;
}

void	ft_parse_line(char *str)
{
	int i;
	int i_cmd;
	int qflag;

	ft_init_parse_int(&i, &i_cmd, &qflag);
	while (str && str[i + i_cmd])
	{
		if (qflag == 0 && str[i + i_cmd] == '"')
			qflag = 1;
		else if ((qflag == 1 && str[i + i_cmd] == '"') ||
			(qflag == 2 && str[i + i_cmd] == '\''))
			qflag = 0;
		else if (qflag == 0 && str[i + i_cmd] == '\'')
			qflag = 2;
		if (qflag == 0 && str[i + i_cmd] == ';' )
		{
			ft_parse_cmd(str + i_cmd, i);
			i_cmd = i_cmd + i + 1;
			i = 0;
		}
		else if (qflag == 0 && ft_strncmp(str + i + i_cmd, "&&", 2) ==0)
		{
			ft_parse_cmd(str + i_cmd, i);
			i_cmd = i_cmd + i + 2;
			i = 0;
			g_and_or = 1;
		}
		else if (qflag == 0 && ft_strncmp(str + i + i_cmd, "||", 2) ==0)
		{
			ft_parse_cmd(str + i_cmd, i);
			i_cmd = i_cmd + i + 2;
			i = 0;
			g_and_or = 2;
		}	
		i++;
	}
	ft_parse_cmd(str + i_cmd, i);
	free(str);
}
