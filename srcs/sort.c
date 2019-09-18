/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:17:05 by wveta             #+#    #+#             */
/*   Updated: 2019/09/18 20:07:04 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_listf	*ft_lst_sort_merge(t_listf *a, t_listf *b)
{
	t_listf *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((ft_strcmp(a->file, b->file) <= 0))
	{
		result = a;
		result->next = ft_lst_sort_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = ft_lst_sort_merge(a, b->next);
	}
	return (result);
}

int		ft_lst_len(t_listf *head)
{
	int		count;
	t_listf	*current;

	count = 0;
	if (head)
	{
		current = head;
		while (current)
		{
			count++;
			if (current->next)
				current = current->next;
			else
				break ;
		}
	}
	return (count);
}

void	ft_lst_split(t_listf *source, t_listf **frontref, t_listf **backref)
{
	int		len;
	int		i;
	int		half;
	t_listf	*current;

	current = source;
	len = ft_lst_len(source);
	if (len < 2)
	{
		*frontref = source;
		*backref = NULL;
	}
	else
	{
		half = (len - 1) / 2;
		i = 0;
		while (i < half)
		{
			current = current->next;
			i++;
		}
		*frontref = source;
		*backref = current->next;
		current->next = NULL;
	}
}

void	ft_merge_sort(t_listf **headref)
{
	t_listf *head;
	t_listf *a;
	t_listf *b;

	head = *headref;
	if ((head == NULL) || (head->next == NULL))
		return ;
	ft_lst_split(head, &a, &b);
	ft_merge_sort(&a);
	ft_merge_sort(&b);
	*headref = ft_lst_sort_merge(a, b);
}

int		ft_check_file(char *find_path, int type)
{
	if (!(find_path))
		return (-1);
	if ((access(find_path, F_OK)) == -1)
	{
		ft_putstr_fd(g_app_name, 2);
		if (find_path[0] == '/' || find_path[0] == '.' || find_path[0] == '~')
			ft_putstr_fd(" : no such file or directory: ", 2);
		else
			ft_putstr_fd(" : command not found: ", 2);
		ft_putstr_fd(find_path, 2);
		ft_putstr_fd("\n", 2);
		ft_set_shell("?", "1");
		return (-1);
	}
	else if ((access(find_path, type)) == -1)
	{
		ft_putstr_fd(g_app_name, 2);
		ft_putstr(" : permission denied: ");
		ft_putstr(find_path);
		ft_putstr("\n");
		ft_set_shell("?", "1");
		return (-1);
	}
	return (0);
}
