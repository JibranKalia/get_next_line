/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 19:46:18 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/19 22:01:13 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		nl_trim(char **buf, char **line)
{
	char	*tmp;
	size_t	len;
	size_t	i;
	char	*ret;

	tmp = *buf;
	i = 0;
	while (tmp[i] != '\n' && tmp[i])
		i++;
	CHK((*line = ft_strndup(tmp, i)) == 0, -1);
	tmp += i;
	(*tmp == '\n') ? tmp++ : tmp;
	if (!*tmp)
	{
		free(*buf);
		*buf = NULL;
		tmp = NULL;
		return (1);
	}
	len = ft_strlen(tmp);
	CHK1((ret = ft_strndup(tmp, len)) == 0, free(*line), -1);
	free(*buf);
	*buf = ret;
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	t_bool			i;
	char			*t[2];
	int				b_read;
	static char		*buf[FD_BUFFER_MAX];

	if (fd < 0 || !line)
		return (-1);
	i = (!ft_strchr(buf[fd], '\n')) ? false : true;
	while (i == false)
	{
		CHK((t[0] = ft_strnew(BUFF_SIZE)) == NULL, -1);
		CHK1((b_read = read(fd, t[0], BUFF_SIZE)) == -1, free(t[0]), -1);
		CHK2(!(t[1] = (!buf[fd]) ? ft_strdup(t[0]) : ft_strjoin(buf[fd], t[0])),
				free(buf[fd]), free(t[0]), -1);
		free(t[0]);
		if (b_read == 0)
			return ((!buf[fd])) ? 0 : nl_trim(&buf[fd], line);
		free(buf[fd]);
		buf[fd] = t[1];
		i = (!ft_strchr(buf[fd], '\n')) ? false : true;
	}
	CHK(nl_trim(&buf[fd], line) == -1, -1);
	return (1);
}
