/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:26:15 by robhak            #+#    #+#             */
/*   Updated: 2023/05/18 16:58:24 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 42

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

char	*new_res(char *res)
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (!res[i])
	{
		free(res);
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (ft_strlen(res) - i + 1));
	if (!buffer)
		return (NULL);
	i++;
	j = 0;
	while (res[i])
		buffer[j++] = res[i++];
	buffer[j] = '\0';
	free(res);
	return (buffer);
}

char	*get_line(char *res)
{
	char	*buffer;
	int		i;

	i = 0;
	if (!res[i])
		return (NULL);
	while (res[i] != '\n' && res[i])
		i++;
	buffer = malloc(sizeof(char) * (i + 2));
	if (!buffer)
		return (NULL);
	i = 0;
	while (res[i] != '\n' && res[i])
	{
		buffer[i] = res[i];
		i++;
	}
	if (res[i] == '\n')
	{
		buffer[i] = res[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	*residual_left(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	byte_read = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (byte_read != 0 && !ft_strchr(res, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = '\0';
		res = ft_strjoin(res, buffer);
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	res = residual_left(fd, res);
	if (!res)
		return (NULL);
	line = get_line(res);
	res = new_res(res);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break ;
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return (0);
// }
