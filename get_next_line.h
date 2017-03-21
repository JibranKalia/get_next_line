/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 19:46:41 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/21 16:47:11 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <libft.h>

# define BUFF_SIZE 1
# define GNL_MAX_FD 4864

typedef	enum	e_bool
{
	false,
	true
}				t_bool;
int		get_next_line(const int fd, char **line);
#endif
