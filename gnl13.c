/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl13.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:02:12 by robhak            #+#    #+#             */
/*   Updated: 2023/05/18 14:21:29 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(s1) + 1;
	dup = malloc(len);
	if (!dup)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		dup[j++] = s1[i++];
	dup[j] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char *ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	joined = malloc(len);
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		joined[j++] = s1[i++];
	i = 0;
	while (s2[i])
		joined[j++] = s2[i++];
	joined[j] = '\0';
	free(s1);
	return (joined);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
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


char	*get_line(char **remainder)
{
	char	*line;
	char	*new_remainder;
	size_t	i;

	i = 0;
	while ((*remainder)[i] && (*remainder)[i] != '\n')
		i++;
	line = ft_substr(*remainder, 0, i + ((*remainder)[i] == '\n'));
	if (!(*line))
	{
		free(line);
		return (NULL);
	}
	if (!(*remainder)[i])
		new_remainder = ft_strdup("");
	else
		new_remainder = ft_strdup(*remainder + i + 1);
	free(*remainder);
	*remainder = new_remainder;
	return (line);
}

char	*get_next_line(int fd)
{
    static char *remainder;
    char *buffer;
    char *line;
    int bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0 || !(buffer = malloc(BUFFER_SIZE + 1)))
        return (NULL);
    if (!remainder)
        remainder = ft_strdup("");
    while (!ft_strchr(remainder, '\n') && (bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        remainder = ft_strjoin_free(remainder, buffer);
    }
    free(buffer);
    if (bytes_read < 0)
        return (NULL);
    line = get_line(&remainder);
    if (!line)
        return (NULL);
    if (bytes_read == 0 && !*remainder)
    {
        free(remainder);
        remainder = NULL;
        return (NULL);
    }
    return (line);
}

int main(int ac, char **av)
{
	int fd;
	char *line;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		while ((line = get_next_line(fd)))
		{
			printf("%s\n", line);
			free(line);
		}
		free(line);
		close(fd);
	}
	return (0);
}