/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:07:19 by robhak            #+#    #+#             */
/*   Updated: 2023/05/18 17:05:50 by robhak           ###   ########.fr       */
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
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *res, char *buffer)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (!res)
	{
		res = malloc(sizeof(char) * 1);
		res[0] = '\0';
	}
	if (!buffer || !res)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(buffer) + 1) + ft_strlen(res)));
	if (str == 0)
		return (NULL);
	if (res)
		while (res[++i] != '\0')
			str[i] = res[i];
	while (buffer[j] != '\0')
		str[i++] = buffer[j++];
	str[ft_strlen(res) + ft_strlen(buffer)] = '\0';
	free(res);
	return (str);
}