/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:07:19 by robhak            #+#    #+#             */
/*   Updated: 2023/04/29 20:57:34 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	if (!s1)
		return (gnl_strdup(s2));	
	if (!s2)
		return (NULL);
	len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	if (!(joined = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	for (size_t i = 0; i < len1; i++)
		joined[i] = s1[i];
	for (size_t i = 0; i < len2; i++)
		joined[len1 + i] = s2[i];
	joined[len1 + len2] = '\0';
	free((char *)s1);
	return (joined);
}

char	*gnl_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = gnl_strlen(s);
	if (!(dup = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	for (size_t i = 0; i < len; i++)
		dup[i] = s[i];
	dup[len] = '\0';
	return (dup);
}
