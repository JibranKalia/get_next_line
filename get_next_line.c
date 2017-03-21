/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 19:46:18 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/20 18:10:39 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

void	insert_extra(char *buf, char **extra, size_t size)
{
	size_t	original_len;

	original_len = size;
	if (!*extra)
	{
		*extra = ft_strdup(buf);
		return ;
	}
	*extra = ft_strjoin(*extra, buf);
}

int		assign_line(char **extra, char **line, size_t size)
{
	if (**extra == '\n')
		size++;
	*line = ft_strndup(*extra, size);
	ft_memmove(*extra, *extra + size + 1, size);
	return (1);
}

int		final_line(char **extra, char **line)
{
	size_t	extra_len;

	printf("Extra2 = %s\n", *extra);
	extra_len = ft_strlen(*extra);
	*line = ft_strndup(*extra, extra_len);
	ft_bzero(*extra, extra_len);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char 			buf[BUFF_SIZE + 1];
	char			*tmp;
	int				b_read;
	static char		*extra[GNL_MAX_FD];

	if (fd < 0 || !line || BUFF_SIZE == 0 || fd > GNL_MAX_FD)
		return (-1);
	while ((b_read = read(fd, buf, BUFF_SIZE)) != 0)
	{
		CHK(b_read == -1, -1);
		insert_extra(buf, &extra[fd], b_read);
		if ((tmp = ft_strchr(extra[fd], '\n')) != 0)
			return (assign_line(&extra[fd], line, tmp - extra[fd]));
	}
	if ((tmp = ft_strchr(extra[fd], '\n')) != 0)
		return (assign_line(&extra[fd], line, tmp - extra[fd]));
	else if (ft_strlen(extra[fd]))
		return (final_line(&extra[fd], line));
	free(extra[fd]);
	return (0);
}
