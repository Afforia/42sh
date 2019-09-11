/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:24:59 by wveta             #+#    #+#             */
/*   Updated: 2019/09/11 22:03:18 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_printenv(char **av)
{
	int		i;
	char	*tmp;

	i = 1;
	if (av && av[i])
	{
		if (av[i][0] == '-')
		{
			ft_print_msg(": usage: printenv [name], error: ", av[1]);
			ft_set_shell("?", "1");
			g_built_rc = 1;
			return (1);
		}
		else if ((tmp = ft_get_env(av[i])))
		{
			ft_putstr(tmp);
			free(tmp);
			return (1);
		}
	}
	ft_print_env();
	ft_set_shell("?", "0");
	return (1);
}
