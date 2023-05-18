/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl11.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:36:58 by robhak            #+#    #+#             */
/*   Updated: 2023/05/18 11:23:39 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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

char	*ft_strchr(char *s, int c)
{
	if (!s || !c)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return (s);
		s++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	size_t	len;
	char	*joined;

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
	free(s1);
	free(s2);
	joined[j] = '\0';
	return (joined);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;

	dest = malloc(ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = (char)s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start])
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}

char	*get_line(int fd, char *residual, char *buffer, int byte_read)
{
	char	*line;
	char	*tmp;

	while (byte_read > 0)
	{
		buffer[byte_read] = '\0';
		if (ft_strchr(buffer, '\n'))
		{
			tmp = residual;
			residual = ft_strjoin(residual, buffer);
			free(tmp);
			break ;
		}
		tmp = residual;
		residual = ft_strjoin(residual, buffer);
		free(tmp);
		byte_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (byte_read == 0)
	{
		line = ft_strdup(residual);
		free(residual);
		residual = NULL;
		return (line);
	}
	line = ft_substr(residual, 0, ft_strchr(residual, '\n') - residual);
	tmp = residual;
	residual = ft_substr(residual, ft_strchr(residual, '\n') - residual + 1,
			ft_strlen(residual) - (int)ft_strchr(residual, '\n') + 1);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	residual;
	char		*buffer;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	

int main(int ac, char **av)
{
	char	*line;
	int		fd;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	while(line)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);	
}