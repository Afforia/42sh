/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:39:37 by thaley            #+#    #+#             */
/*   Updated: 2019/09/11 18:23:58 by thaley           ###   ########.fr       */
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

int			parse_backslash(int start)
{
	int		count;

	count = 0;
	if (start < 0)
		return (-1);
	if (g_input->input[start] == '\\' && start > -1)
	{
		while (start > -1 && start != g_input->input_len
			&& g_input->input[start] == '\\')
		{
			start--;
			count++;
		}
	}
	return (count);
}

int			check_quotes(void)
{
	int		i;
	int		save;

	i = 0;
	save = -1;
	while (i < g_input->input_len)
	{
		if ((g_input->input[i] == '\'' && i > 0 && g_input->input[i - 1] != '\\'))
		{
			if (!g_input->quotes)
				g_input->quotes = g_input->input[i];
			else if (g_input->quotes)
			{
				save = i;
				g_input->quotes = '\0';
			}
		}
		else if (g_input->quotes && g_input->input[i] == g_input->quotes)
		{
			save = i;
			g_input->quotes = '\0';
		}
		i++;
	}
	if (save != -1)
		return (save);
	return (0);
}

void		check_double_quotes(int i)
{
	int		check;

	check = 0;
	while (i < g_input->input_len)
	{
		if (g_input->input[i] == '\"' && (i > 0 && g_input->input[i - 1] != '\\'))
		{

			if (!g_input->quotes)
				g_input->quotes = g_input->input[i];
			else if (g_input->quotes == g_input->input[i])
				g_input->quotes = '\0';
		}
		else if ((g_input->input[i] == '\"' && (i > 0 && g_input->input[i - 1] == '\\')))
		{
			check = parse_backslash(i - 1);
			if (check % 2 == 0 && g_input->quotes)
				g_input->quotes = '\0';
			else if (check % 2 == 0 && !g_input->quotes)
				g_input->quotes = g_input->input[i];
		}
		i++;
	}
}

int			parse_quotes(void)
{
	int				i;

	i = parse_backslash(g_input->input_len - 1);
	if (i % 2 != 0 && i > -1)
		return (1);
	i = check_quotes();
	if (!g_input->quotes)
		check_double_quotes(i);
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
