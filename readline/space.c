/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:39:37 by thaley            #+#    #+#             */
/*   Updated: 2019/08/29 14:04:37 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			ft_isspace2(char st)
{
	if (st == '\0' || st == ' ' || st == '\n' || st == '\t' ||
		st == '\r' || st == '\v' || st == '\f')
		return (1);
	return (0);
}

int			only_space(void)
{
	int		i;

	i = 0;
	while (i < g_input->input_len)
	{
		if (ft_isspace2(g_input->input[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int			parse_quotes(void)
{
	int				i;

	i = 0;
	while (i < g_input->input_len)
	{
		if ((g_input->input[i] == '\'' || g_input->input[i] == '\"')
		&& (i == 0 || g_input->input[i - 1] != '\\'))
		{
			if (!g_input->quotes)
				g_input->quotes = g_input->input[i];
			else if (g_input->quotes == g_input->input[i])
				g_input->quotes = '\0';
		}
		i++;
	}
	if (g_input->quotes)
		return (1);
	return (0);
}

int			printable(char *c, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		if (ft_isprint(c[j]))
			j++;
		else
			return (0);
	}
	return (1);
}
