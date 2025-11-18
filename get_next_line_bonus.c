/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:07:36 by rfirat            #+#    #+#             */
/*   Updated: 2025/11/18 21:15:12 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*gnl_consume(char **storage)
{
	char	*line;
	char	*rest;
	int		cut;
	size_t	len;

	if (*storage == NULL || **storage == '\0')
		return (NULL);
	cut = gnl_nl_index(*storage);
	len = gnl_len(*storage);
	if (cut < 0)
	{
		line = gnl_slice(*storage, 0, len);
		rest = NULL;
	}
	else
	{
		line = gnl_slice(*storage, 0, (size_t)cut + 1);
		rest = gnl_slice(*storage, (size_t)cut + 1, len - (size_t)cut - 1);
	}
	free(*storage);
	*storage = rest;
	return (line);
}

static int	gnl_need_more(const char *storage)
{
	if (storage == NULL)
		return (1);
	if (gnl_nl_index(storage) < 0)
		return (1);
	return (0);
}

static char	*gnl_read_fd(int fd, char *storage)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	count;

	count = 1;
	while (count > 0 && gnl_need_more(storage))
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count < 0)
		{
			free(storage);
			return (NULL);
		}
		buffer[count] = '\0';
		if (count == 0)
			break ;
		storage = gnl_merge(storage, buffer);
		if (storage == NULL)
			return (NULL);
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage[fd] = gnl_read_fd(fd, storage[fd]);
	if (storage[fd] == NULL)
		return (NULL);
	line = gnl_consume(&storage[fd]);
	if (line == NULL)
	{
		free(storage[fd]);
		storage[fd] = NULL;
	}
	return (line);
}
