/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 22:46:28 by thaley            #+#    #+#             */
/*   Updated: 2019/09/29 15:36:50 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	free_array(char **arr)
{
	int		i;

	i = 0;
	if (!arr || !arr[i])
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_int_array(int **arr, int size)
{
	if (!arr || !size)
		return ;
	while (--size > 0)
		free(arr[size]);
	free(arr);
	arr = NULL;
}

void	ft_free(char *str)
{
	if (str && *str)
		free(str);
	str = NULL;
}

void	free_struct(t_shell **shell)
{
	ft_free((*shell)->term);
	free(*shell);
	shell = NULL;
	free_int_array(g_input->auto_tab.pos, g_input->auto_tab.amount);
	ft_bzero(g_input->old_input, MAX_CMDS);
	ft_free(g_input->prompt);
	free(g_input);
	g_input = NULL;
}
