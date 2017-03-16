/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
	//	printf("Line = %s\n", *line);
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 19:46:18 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/16 13:10:26 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		nl_pos(char *str)
{
	size_t	i;
	t_bool	flag;

	flag = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			flag = true;
			break;
		}
		i++;
	}
	return ((flag == true) ? i + 1: 0);
}

void newline(char **s, int *i)
{
	size_t	i;
	char	*str;
	t_bool	flag;

	str = *s;
	flag = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			flag = true;
			break;
		}
		i++;
	}
	*i = (flag == true) ? i + 1: 0;
	if (flag == true)
	{
		ft_memmove((void*)str, (void*)(str + i + 1), ft_strlen((str + i)));
	}
	return ((flag == true) ? str : NULL);
}

int		get_next_line(const int fd, char **line)
{
	char			*tmp;
	size_t			buf;
	int				rd;
	int				i;
	static char		*leftover;

	i = 0;
	tmp = NULL;
	buf = BUFF_SIZE;
	if (leftover)
	{
		if ((i = nl_pos(leftover)))
		{
			CHK1((*line = ft_strnew(i)) == 0, ft_putstr("Error in Malloc\n"), -1);
			ft_strncpy(*line, leftover, i);
			leftover = newline_remove(leftover);
			return (1);
		}
	}
	while (i == 0)
	{
		CHK1((tmp = ft_strnew(buf)) == 0, ft_putstr("Error in Malloc\n"), -1);
		rd = read(fd, tmp, buf);
		if (!rd)
			return (0);
		if (leftover)
			leftover = ft_strjoin(leftover, tmp);
		else
			leftover = tmp;
		i = nl_pos(leftover);
		buf *= 2;
	}

	CHK1((*line = ft_strnew(i)) == 0, ft_putstr("Error in Malloc\n"), -1);
	ft_strncpy(*line, leftover, i - 1); //Not copying ending newline.
	leftover = newline_remove(leftover);
	return (1);
}

