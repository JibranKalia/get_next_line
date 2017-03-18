/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 19:46:18 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/17 17:11:22 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

int		nl_loc(char *str)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] == '\n')
	{
		if (src[i + 1] != '\0')
			return (i + 1);
		else
			return (i);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	t_bool			i;
	char			*tmp[3];
	int				b_read;
	static	char*	extra;

	i = false;
	if (extra != NULL)
	{
		if ((tmp[1] = ft_strchr(extra, '\n')) != NULL)
		{
//			printf("tmp[1] = %s\n", tmp[1]);
			i = true;
		}
	}
	while (i == false)
	{
		tmp[0] = ft_strnew(BUFF_SIZE);
		CHK1((b_read = read(fd, tmp[0], BUFF_SIZE)) == -1, free(tmp[0]), -1);
		//printf("b_read = %d\n", b_read);
		if (b_read == 0)
		{
			if (!extra)
				return (0);
			else
			{
				ft_strncpy(*line, extra, ft_strlen(extra));
				free(extra);
				return (0);
			}
		}
		if (!extra)
			extra = ft_strdup(tmp[0]);
		else
			extra = ft_strjoin(extra, tmp[0]);
		free(tmp[0]);
		if (!(tmp[1] = ft_strchr(extra, '\n')))
				i = false;
		else
			i = true;
	}
	tmp[2] = ft_strdup(tmp[1] + 1); //CHECKOUT
	printf("ORIG =	%s\n",tmp[1]);
	printf("AFTER=	%s\n",tmp[2]);
	printf("Extra1=	%s\n",extra);
	bzero(extra, ft_strlen(tmp[2]));
	printf("Extra2=	%s\n",extra);
	ft_strncpy(*line, extra, ft_strlen(extra));
	free(extra);
	extra = tmp[2];
	return (1);
}
