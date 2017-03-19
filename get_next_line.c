/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 19:46:18 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/18 23:25:22 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

void	nl_trim(char **extra, char **line)
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
		return ;
	}
	ret = ft_strndup(tmp, len);
	free(*extra);
	*extra = ret;
}


int		get_next_line(const int fd, char **line)
{
	t_bool			i;
	char			*tmp;
	int				b_read;
	static	char*	extra;

	i = false;
	if (ft_strchr(extra, '\n') != NULL)
		i = true;
	while (i == false)
	{
		tmp = ft_strnew(BUFF_SIZE);
		CHK1((b_read = read(fd, tmp, BUFF_SIZE)) == -1, free(tmp), -1);
		if (b_read == 0 && !extra)
			return (0);
		if (b_read == 0)
		{
			nl_trim(&extra, line);
			return (1);
		}
		extra = (!extra) ? ft_strdup(tmp) : ft_strjoin(extra, tmp);
		free(tmp);
		if (ft_strchr(extra, '\n') == NULL)
			i = false;
		else
			i = true;
	}
	nl_trim(&extra, line);
	return (1);
}
