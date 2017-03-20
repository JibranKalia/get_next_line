/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 19:46:18 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/19 17:45:17 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

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
	len = ft_strlen(tmp);
	if (len == 0)
	{
		free(*extra);
		*extra = NULL;
		return (1);
	}
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
	static char*	extra;

	i = (!ft_strchr(extra, '\n')) ? false : true;
	while (i == false)
	{
		tmp[0] = ft_strnew(BUFF_SIZE);
		CHK1((b_read = read(fd, tmp[0], BUFF_SIZE)) == -1, free(tmp[0]), -1);
		if (b_read == 0)
		{
			free(tmp[0]);
			return ((!extra)) ? 0 : nl_trim(&extra, line);
		}
		tmp[1] = (!extra) ? ft_strdup(tmp[0]) : ft_strjoin(extra, tmp[0]);
		free(tmp[0]);
		free(extra);
		extra = tmp[1];
		i = (!ft_strchr(extra, '\n')) ? false : true;
	}
	nl_trim(&extra, line);
	return (1);
}
