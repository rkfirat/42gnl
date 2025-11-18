/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:07:08 by rfirat            #+#    #+#             */
/*   Updated: 2025/11/18 21:09:46 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_len(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

static char	*gnl_alloc(size_t count)
{
	char	*buf;
	size_t	idx;

	buf = (char *)malloc(count);
	if (!buf)
		return (NULL);
	idx = 0;
	while (idx < count)
	{
		buf[idx] = '\0';
		idx++;
	}
	return (buf);
}

char	*gnl_slice(const char *src, size_t from, size_t count)
{
	char	*res;
	size_t	idx;

	res = gnl_alloc(count + 1);
	if (!res)
		return (NULL);
	idx = 0;
	while (idx < count && src[from + idx] != '\0')
	{
		res[idx] = src[from + idx];
		idx++;
	}
	res[idx] = '\0';
	return (res);
}

char	*gnl_merge(char *left, const char *right)
{
	t_merge	merge;

	merge.llen = gnl_len(left);
	merge.rlen = gnl_len(right);
	merge.joined = gnl_alloc(merge.llen + merge.rlen + 1);
	if (!merge.joined)
	{
		free(left);
		return (NULL);
	}
	merge.idx = -1;
	while (++merge.idx < merge.llen)
		merge.joined[merge.idx] = left[merge.idx];
	merge.idx = -1;
	while (++merge.idx < merge.rlen)
	{
		merge.joined[merge.llen + merge.idx] = right[merge.idx];
	}
	merge.joined[merge.llen + merge.rlen] = '\0';
	free(left);
	return (merge.joined);
}

int	gnl_nl_index(const char *s)
{
	int	idx;

	if (!s)
		return (-1);
	idx = 0;
	while (s[idx] != '\0')
	{
		if (s[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}
