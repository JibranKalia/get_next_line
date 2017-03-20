/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 19:46:18 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/19 21:04:44 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	*line = ft_strndup(tmp, i);
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
	ret = ft_strndup(tmp, len);
	free(*buf);
	*buf = ret;
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	t_bool			i;
	char			*tmp[2];
	int				b_read;
	static char		*buf[FD_BUFFER_MAX];

	if (fd < 0 || !line)
		return (-1);
	i = (!ft_strchr(buf[fd], '\n')) ? false : true;
	while (i == false)
	{
		tmp[0] = ft_strnew(BUFF_SIZE);
		CHK1((b_read = read(fd, tmp[0], BUFF_SIZE)) == -1, free(tmp[0]), -1);
		if (b_read == 0)
		{
			free(tmp[0]);
			return ((!buf[fd])) ? 0 : nl_trim(&buf[fd], line);
		}
		tmp[1] = (!buf[fd]) ? ft_strdup(tmp[0]) : ft_strjoin(buf[fd], tmp[0]);
		free(tmp[0]);
		free(buf[fd]);
		buf[fd] = tmp[1];
		i = (!ft_strchr(buf[fd], '\n')) ? false : true;
	}
	nl_trim(&buf[fd], line);
	return (1);
}
