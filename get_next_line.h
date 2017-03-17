/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 19:46:41 by jkalia            #+#    #+#             */
/*   Updated: 2017/03/16 17:54:57 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE
# define BUFF_SIZE 1


#include <fcntl.h>
#include <stdio.h>
#include <string.h>


#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

typedef	enum	e_bool
{
	false,
	true
}				t_bool;

int		get_next_line(const int fd, char **line);

#endif
