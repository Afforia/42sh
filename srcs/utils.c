/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:32:55 by wveta             #+#    #+#             */
/*   Updated: 2019/09/06 14:40:42 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_calc_matr_rows(char **in)
{
	int i;

	i = 0;
	while (in && in[i])
		i++;
	return (i);
}

char	**ft_free_char_matr(char **matrix)
{
	int i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
	return (NULL);
}

char	**ft_dup_char_matr(char **in)
{
	char	**out;
	int		i;
	int		j;


	if (!(in))
		return (NULL);
	i = ft_calc_matr_rows(in);
	if (!(out = (char **)malloc(sizeof(char *) * (i + 1))))
		exit_shell();
	out[i] = NULL;
	j = 0;
	while (j < i && in[j])
	{
		if (!(out[j] = ft_strdup(in[j])))
		{
			out = ft_free_char_matr(out);
			exit_shell();
		}
		j++;
	}
	return (out);
}

void	ft_signal_handler_rl(int signo)
{
	if (signo == SIGINT && g_check == 0)
	{
		ft_putchar('\n');
		longjmp(g_cmd->ebuf, g_cmd->jmp_code);
	}
	else if (signo == SIGINT && g_check == 1)
		exit(0);
	else
		exit(0);
}
