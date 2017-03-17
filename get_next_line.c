/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 19:46:18 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/17 15:49:04 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

void	*ft_realloc(void *src, size_t srcsize, size_t newsize)
{
	void	*res;
	size_t	cpylen;

	cpylen = (srcsize < newsize) ? srcsize : newsize;
	CHK(!src, 0);
	CHK(res = ft_memalloc(newsize) == 0, 0);
	ft_memcpy(res, src, cpylen);
	free(src);
	return (res);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	buff;

}
