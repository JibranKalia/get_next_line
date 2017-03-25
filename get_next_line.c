/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 19:46:18 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/24 16:59:54 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

void	insert_extra(char *buf, t_arr *extra)
{
	char	*tmp;

	if (extra->ptr == 0)
	{
		extra->ptr = ft_strdup(buf);
		ft_bzero(buf, BUFF_SIZE + 1);
		return ;
	}
	tmp = ft_strjoin(extra->ptr, buf);
	free(extra->ptr);
	ft_bzero(buf, BUFF_SIZE + 1);
	extra->ptr = tmp;
}

int		assign_line(t_arr *extra, char **line, size_t size)
{
	*line = ft_strndup(extra->ptr, size);
	extra->ptr = ft_memmove(extra->ptr, extra->ptr + size + 1, ft_strlen(extra->ptr));
	return (1);
}

int		final_line(t_arr *extra, char **line)
{
	size_t extra_len;

	extra_len = ft_strlen(extra->ptr);
	*line = ft_strdup(extra->ptr);
	ft_bzero(extra->ptr, extra_len);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	ssize_t			b_read;
	static t_arr	extra[GNL_MAX_FD];

	if (fd < 0 || !line || BUFF_SIZE == 0 || fd > GNL_MAX_FD)
		return (-1);
	ft_bzero(buf, BUFF_SIZE + 1);
	while ((b_read = read(fd, buf, BUFF_SIZE)) != 0)
	{
		CHK(b_read == -1, -1);
		insert_extra(buf, &extra[fd]);
		if ((tmp = ft_strchr(extra[fd].ptr, '\n')) != 0)
			return (assign_line(&extra[fd], line, tmp - extra[fd].ptr));
	}
	if (extra[fd].ptr == 0)
		return (0);
	else if ((tmp = ft_strchr(extra[fd].ptr, '\n')) != 0)
		return (assign_line(&extra[fd], line, tmp - extra[fd].ptr));
	else if (ft_strlen(extra[fd].ptr) > 0)
		return (final_line(&extra[fd], line));
	ft_strdel(&extra[fd].ptr);
	return (0);
}
