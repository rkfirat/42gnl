/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:07:44 by rfirat            #+#    #+#             */
/*   Updated: 2025/11/19 00:04:30 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t		gnl_len(const char *s);
char		*gnl_merge(char *left, const char *right);
int			gnl_nl_index(const char *s);
char		*gnl_slice(const char *src, size_t from, size_t count);
char		*get_next_line(int fd);

typedef struct s_merge
{
	size_t	llen;
	size_t	rlen;
	char	*joined;
	size_t	idx;
}			t_merge;

typedef struct s_consume
{
	char	*line;
	char	*rest;
	int		cut;
	size_t	len;
}			t_consume;

#endif
