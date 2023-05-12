/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:07:19 by robhak            #+#    #+#             */
/*   Updated: 2023/05/12 13:04:02 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*gnl_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_cpy;
	const unsigned char	*src_cpy;

	if (!dest || !src)
		return (NULL);
	dest_cpy = dest;
	src_cpy = src;
	while (n-- > 0)
		*dest_cpy++ = *src_cpy++;
	return (dest);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	new_str = malloc(s1_len + s2_len + 1);
	if (new_str == NULL)
		return (NULL);
	gnl_memcpy(new_str, s1, s1_len);
	gnl_memcpy(new_str + s1_len, s2, s2_len);
	new_str[s1_len + s2_len] = '\0';
	return (new_str);
}


void	*gnl_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	char	*p;
	char	*q;
	size_t	i;

	i = 0;
	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
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
	unsigned char	character;

	character = c;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == character)
		{
			printf("s = %s\n\n", s);
			return ((char *)s);
		}
		s++;
	}
	if (character == '\0')
		return ((char *)s);
	return (NULL);
}


char	*gnl_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if ((!src) || (!dest))
		return (NULL);
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

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*gnl_strdup(const char *s)
{
	size_t	len;
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	len = 0;
	while (s[len])
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
	return (str);
}

char	*gnl_strcpy(char *dest, const char *src)
{
	if (!src)
		return (NULL);
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (dest);
}
