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
#include <stdlib.h>
# include <stdbool.h>
# define EXIT_SUCCESS
# define EXIT_FAILURE


// just this whole function is bad
//                                 what did read return? how does this function know?
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
	//memdup()
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
	// memlen???
	len = ft_strlen(tmp);
	// memdup()
	CHK1((ret = ft_strndup(tmp, len)) == 0, free(*line), -1);
	free(*buf);
	*buf = ret;
	return (0);
}

int		insert_fd(char **buf, char **extra, size_t size)
{

}


int		assign_line(char **buf, char **line, size_t size)
{
	*line = ft_memalloc(size + 1)
}

int		get_next_line(const int fd, char **line)
{
	bool			i;
	char 			buf[BUFF_SIZE];
	void			*tmp;
	int				b_read;
	static char		*extra[BUFF_SIZE];

	if (fd < 0 || !line || BUFF_SIZE == 0 || fd > GNL_MAX_FD)
		exit(EXIT_FAILURE);
	i = (!ft_memchr(buf[fd], '\n')) ? false : true;
	while ((b_read = read(fd, buf, BUFF_SIZE)) != 0)
	{
		CHK(b_read == -1, -1);
		if (tmp = ft_memchr(buf, '\n', b_read) != 0)
			assign_line(&buf
			

	}
	CHK2(!(t[1] = (!buf[fd]) ? ft_strdup(t[0]) : ft_strjoin(buf[fd], t[0])),
		free(buf[fd]), free(t[0]), -1);
		free(t[0]);
		//this check needs to be done right after the read
		if (b_read == 0)
			//does this function only trim the newline? be careful when naming
			return ((!buf[fd])) ? 0 : nl_trim(&buf[fd], line);
		//so much freeing!!!
		free(buf[fd]);
		//there are so many more elegant ways to do this
		buf[fd] = t[1];
		//WHAT??? also memchr()
		i = (!ft_strchr(buf[fd], '\n')) ? false : true;
	}
	// there is a case here that you are missing
	CHK(nl_trim(&buf[fd], line) == -1, -1);
	return (1);
}
/*
i feel this is a great example of not planning properly. think about what you want to do.
how you want to accomplish it, and what that entails. then as you write the code, refer back to these
two questions. the code is just simply messy. I know that this is against norm, but the next 
revision, i recommend you comment every line of code or every other line of code. this way you
are forced to make the code so simple as to be explainable through a few lines of text.
*/
