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
#include "libft/libft.h"

void	*ft_realloc(void **buf, size_t size, size_t new_size)
{
	unsigned char	*res;
	unsigned char	*tmp;
	size_t			i;

	res = (unsigned char*)ft_memalloc(new_size);
	tmp = (unsigned char*)*buf;
	i = 0;
	while (i < size)
	{
		res[i] = tmp[i];
		i++;
	}
	free(*buf);
	return ((void*)(res));
}

int		nl_pos(char *str)
{
	size_t	i;
	t_bool	flag;

	if (!str)
		return (0);
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
	return ((flag == true) ? i + 1: 0); //Pos after nl
}

void	newline_remove(char **str, int i)
{
	size_t	len;

	len = ft_strlen(*str + i - 1);
	*str = (char *)ft_realloc((void**)(*str + i), ft_strlen(*str), len);
}

int		get_next_line(const int fd, char **line)
{
	char			*tmp;
	char			*tmp1;
	int				b_size;
	int				b_read;
	int				i;
	static char		*leftover;

	if (!line || fd < 0)
		return (-1);
	i = 0;
	tmp = NULL;
	i = nl_pos(leftover);
	b_size = BUFF_SIZE;
	while (i == 0)
	{
		CHK1((tmp = ft_strnew(b_size)) == 0, ft_putstr("Error in Malloc\n"), -1);
		CHK1((b_read = read(fd, tmp, b_size)) == -1, free(tmp), -1);
		if (b_read == 0)
		{
			if (!leftover)
				return (0);
			else
			{
				i = ft_strlen(leftover);
				break;
			}
		}
		if (leftover)
		{
			tmp1 = leftover;
			leftover = ft_strjoin(leftover, tmp);
			free(tmp1);
			free(tmp);
		}
		else
			leftover = tmp;
		i = nl_pos(leftover);
	}
	CHK1((*line = ft_strnew(i)) == 0, ft_putstr("Error in Malloc\n"), -1);
	ft_strncpy(*line, leftover, i - 1); //Not copying ending newline.
	newline_remove(&leftover, i);
	return (1);
}
