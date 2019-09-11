/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 19:32:32 by thaley            #+#    #+#             */
/*   Updated: 2019/08/30 19:41:19 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		mall_check(void)
{
	ft_putstr_fd("ERROR: Cannot allocate memory.", STDERR_FILENO);
	finish_loop(4, NULL);
}
