/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 19:46:18 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/19 20:37:34 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include "libft/libft.h"
#include <libft.h>


# define FD_BUFFER_MAX 200

int		nl_trim(char **extra, char **line)
{
	char	*tmp;
	size_t	len;
	size_t	i;
	char	*ret;

	tmp = *extra;
	i = 0;
	while (tmp[i] != '\n' && tmp[i])
		i++;
	*line = ft_strndup(tmp, i);
	tmp += i;
	(*tmp == '\n') ? tmp++ : tmp;
	if (!*tmp)
	{
		free(*extra);
		*extra = NULL;
		tmp = NULL;
		return (1);
	}
	len = ft_strlen(tmp);
	ret = ft_strndup(tmp, len);
	free(*extra);
	*extra = ret;
	return (0);
}


int		get_next_line(const int fd, char **line)
{
	t_bool			i;
	char			*tmp[2];
	int				b_read;
	static char*	extra[FD_BUFFER_MAX];

	if (fd < 0 || !line)
		return (-1);
	i = (!ft_strchr(extra[fd], '\n')) ? false : true;
	while (i == false)
	{
		tmp[0] = ft_strnew(BUFF_SIZE);
		CHK1((b_read = read(fd, tmp[0], BUFF_SIZE)) == -1, free(tmp[0]), -1);
		if (b_read == 0)
		{
			free(tmp[0]);
			return ((!extra[fd])) ? 0 : nl_trim(&extra[fd], line);
		}
		tmp[1] = (!extra[fd]) ? ft_strdup(tmp[0]) : ft_strjoin(extra[fd], tmp[0]);
		free(tmp[0]);
		free(extra[fd]);
		extra[fd] = tmp[1];
		i = (!ft_strchr(extra[fd], '\n')) ? false : true;
	}
	nl_trim(&extra[fd], line);
	return (1);
}
