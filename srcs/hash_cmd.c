/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wveta <wveta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 22:03:52 by thaley            #+#    #+#             */
/*   Updated: 2019/09/13 19:18:01 by wveta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*ft_putfnbr(int nb, char *str)
{
	int		a;
	int		b;
	int		len;
	char	c;

	if (nb == -2147483648)
		str = ft_strcat(str, "-");
	else
	{
		if (nb < 0)
		{
			nb = nb * (-1);
			str = ft_strcat(str, "-");
		}
		a = nb / 10;
		b = nb % 10;
		if (a > 0)
			str = ft_putfnbr(a, str);
		len = ft_strlen(str);
		c = b + 48;
		str[len] = c;
		str[len + 1] = '\0';
	}
	return (str);
}


void	ft_hash_all_del(char *str)
{
	t_listh	*cur;
	t_listh	*prev;
	t_listh	*tmp;

	prev = NULL;
	tmp = NULL;
	cur = g_envi->hash_first;
	while (cur)
	{
		if ((!(str) || ft_strcmp(str, cur->file) == 0))
		{
			tmp = cur;
			if (prev)
				prev->next = cur->next;
			else
				g_envi->hash_first = cur->next;
			cur = cur->next;
			if (tmp->file)
				free(tmp->file);
			if (tmp->path)
				free(tmp->path);
			free(tmp);
			continue;
		}
		prev = cur;
		cur = cur->next;
	}
}

int		ft_print_hash(void)
{
	t_listh	*tmp;
	int		count;
	char	*str;
	int		len;

	count = 0;
	tmp = g_envi->hash_first;
	str = ft_alloc_char(10);
	str[0] = '\0';
	while (tmp)
	{
		if (count == 0)
			ft_putstr("hits	command\n");
		count++;
		str = ft_putfnbr(tmp->hashcount, str);
		len = ft_strlen(str);
		if (len < 4)
			write(STDOUT_FILENO, "    ", 4 - len);
		ft_putstr(str);
		str[0] = '\0';
		ft_putstr("   ");
		ft_putstr(tmp->path);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	free(str);
	return (1);
}

void	ft_print_one(char *av, int code)
{
	t_listh	*tmp;

	tmp = g_envi->hash_first;
	while (tmp)
	{
		if (((av) && ft_strcmp(tmp->file, av) == 0) || (code ==3 && !(av)))
		{	
			if (code == 1)
				ft_putstr(tmp->path);
			else if (code == 2)
			{
				ft_putstr(tmp->file);
				write(STDOUT_FILENO, "          ", 10 - ft_strlen(tmp->file));
				ft_putstr(tmp->path);
			}
			else if (code == 3)
			{
				ft_putstr("builtin hash -p ");
				ft_putstr(tmp->path);
				ft_putstr(" ");
				ft_putstr(tmp->file);
			}
			ft_putchar('\n');
		}
		tmp = tmp->next;
	}
}

int		ft_cmd_hash(char **av)
{
	int 	i;
	char	*tmp;
	int		fl;
	int		start;

	ft_set_shell("?", "0");
	i = 1;
	fl = 0;
	tmp = NULL;
	start = 0;
	if (!(av[1]))
		return (ft_print_hash());
	while (av && av[i])
	{
		if (av[i][0] == '-' && ft_strchr(av[i], 'r'))
		{
			ft_hash_all_del(NULL);
			return (1);
		}
		else if (av[i][0] == '-' && ft_strchr(av[i], 'd'))
			fl = 4;
		else if (av[i][0] == '-' && ft_strchr(av[i], 'p') && fl < 4)
			fl = 3;
		else if (av[i][0] == '-' && ft_strchr(av[i], 't') && fl < 3)
			fl = 2;
		else if (av[i][0] == '-' && ft_strchr(av[i], 'l') && fl < 2
			&& (av[i + 1]))
			fl = 1;
		else if (av[i][0] == '-' && ft_strchr(av[i], 'l') && fl < 2
				&& !(av[i + 1]))
			ft_print_one(NULL, 3);
		else if (av[i][0] == '-')
			return (ft_hash_usage(av[i]));
		else
		{	if (start == 0)
				start = i;
			if (fl == 4)
				ft_hash_all_del(av[i]);
			else if (fl == 3)
			{
				if (i > start)
					ft_hash_cmd_add(av[start], av[i]);
			}
			else if (fl == 2 && ((i - start > 0) || (av[i + 1]))) 
				ft_print_one(av[i], 2);
			else if (fl == 2)
				ft_print_one(av[i], 1);
			else if (fl == 1)
				ft_print_one(av[i], 3);
		}
		i++;
	}
	return (1);
}
