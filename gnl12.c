/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl12.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:38:12 by robhak            #+#    #+#             */
/*   Updated: 2023/05/18 11:52:07 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*get_next_line(int fd)
{
	static char *remainder;
	char		*line;
	char		*buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	int			len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (!ft_strchr(remainder, '\n') && bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		remainder = ft_strjoin(remainder, buffer);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (NULL);
	len = ft_strchr(remainder, '\n') - remainder;
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
		close(fd);
	}
	return (0);
}