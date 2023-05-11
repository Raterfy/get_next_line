/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:07:19 by robhak            #+#    #+#             */
/*   Updated: 2023/05/11 14:53:30 by robhak           ###   ########.fr       */
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

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	s = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
	}
	free (s1);
	j = 0;
	while (s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}

void	*gnl_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	char	*p;
	char	*q;
	size_t	i;

	i = 0;
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
	if (*s == c)
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

char	*gnl_strdup(const char *s)
{
	size_t	len;
	char	*str;
	int		i;

	i = 0;
	len = 0;
	while (*s)
		len++;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (NULL);
}

char	*gnl_strcpy(char *dest, const char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (dest);
}
