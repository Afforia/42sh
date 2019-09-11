/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_great2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:25:30 by wveta             #+#    #+#             */
/*   Updated: 2019/08/28 20:17:32 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_reset_cmd_great(int j, int i, t_cmdlist *cmd)
{
	if (j == 0)
		cmd->avcmd[i][j] = '\0';
	else if ((ft_isdigit(cmd->avcmd[i][j - 1]) == 1) || (
		j == 1 && cmd->avcmd[i][j - 1] == '&'))
		cmd->avcmd[i][j - 1] = '\0';
}
