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
	// try and use ! only for bool statements or comparison statements like !(this || this)
	// for this use *extra == 0, makes it clearer as to what you want to do.
	if (!*extra)
	{
		// no str functions allowed, remember they all stop when they hit a \0
		*extra = ft_strdup(buf);
		return ;
	}
	// str function.
	*extra = ft_strjoin(*extra, buf);
}

int		assign_line(char **extra, char **line, size_t size)
{
	// what are you doing here? what is this if statement's purpose?
	if (**extra == '\n')
		size++;
	// use of strndup is nice but it will still stop at \0
	*line = ft_strndup(*extra, size);
	//                        why plus one?
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
	// does't read return a ssize_t? correct me if i am wrong, implicit typecasts are not good
	int				b_read;
	static char		*extra[GNL_MAX_FD];

	if (fd < 0 || !line || BUFF_SIZE == 0 || fd > GNL_MAX_FD)
		return (-1);
	while ((b_read = read(fd, buf, BUFF_SIZE)) != 0)
	{
		CHK(b_read == -1, -1);
		insert_extra(buf, &extra[fd], b_read);
		// str function
		if ((tmp = ft_strchr(extra[fd], '\n')) != 0)
			return (assign_line(&extra[fd], line, tmp - extra[fd]));
	}
	/// str function
	if ((tmp = ft_strchr(extra[fd], '\n')) != 0)
		return (assign_line(&extra[fd], line, tmp - extra[fd]));
	// str function
	else if (ft_strlen(extra[fd]))
		return (final_line(&extra[fd], line));
	free(extra[fd]);
	return (0);
}
// so by now you should have realized that you can't only use mem functions.
// why? because this function will be called multiple times, and the only information
// that will remain through the calls is the static var, you static var does not hold
// the current size of the array. so, that is an issue. so, pretty hard to fix this without
// a struct. so for now simply try to make sure that you handle nulls everywhere that you can
// and if a null ends up between calls. that's ok.
// finally, much cleaner code, definitely easier to read and better designed. good job.
