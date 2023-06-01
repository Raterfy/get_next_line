/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:07:19 by robhak            #+#    #+#             */
/*   Updated: 2023/06/01 22:35:54 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src;

	if (!dst && !src)
		return (NULL);
	ptr_dst = (unsigned char *)dst;
	ptr_src = (const unsigned char *)src;
	while (n--)
		*ptr_dst++ = *ptr_src++;
	return (dst);
}

char	*ft_strjoin(char *res, char *buffer)
{
	size_t	res_len;
	size_t	buffer_len;
	char	*joined;

	if (!res)
	{
		res = malloc(sizeof(char));
		if (!res)
			return (NULL);
		*res = '\0';
	}
	if (!buffer || !res)
		return (NULL);
	res_len = ft_strlen(res);
	buffer_len = ft_strlen(buffer);
	joined = malloc(sizeof(char) * (res_len + buffer_len + 1));
	if (!joined)
		return (NULL);
	ft_memcpy(joined, res, res_len);
	ft_memcpy(joined + res_len, buffer, buffer_len);
	joined[res_len + buffer_len] = '\0';
	free(res);
	return (joined);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	n;

	srclen = ft_strlen(src);
	if (size > 0)
	{
		n = size - 1;
		if (n > srclen)
		n = srclen;
		ft_memcpy(dst, src, n);
		dst[n] = '\0';
	}
	return (srclen);
}
