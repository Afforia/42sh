/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_back_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:59:03 by thaley            #+#    #+#             */
/*   Updated: 2019/08/24 15:59:23 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			history_return_n(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == 7)
		{
			str[i] = '\n';
			count++;
		}
		i++;
	}
	return (count);
}

char		*history_replace_n(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			str[i] = 7;
		i++;
	}
	return (str);
}
