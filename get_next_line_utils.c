/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:07:19 by robhak            #+#    #+#             */
/*   Updated: 2023/05/11 00:25:49 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strcat(char *dest, char *src)
{
	int		i;
	int		j;

	i = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest = '\0';
	return (dest);
}

void	*gnl_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	char	*p;
	char	*q;
	size_t	i;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(size));
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	p = (char *)ptr;
	q = (char *)new_ptr;
	while (i < size && i < sizeof(*ptr))
	{
		q[i] = p[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}

char	*gnl_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if(*s == c)
		return ((char *)s);
	return (NULL);
}

char	*gnl_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}