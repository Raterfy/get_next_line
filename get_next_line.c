/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/11 00:20:05 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buffer, size_t buffer_size)
{
	int		byte_read;
	char	*newline;
	size_t	len;
	char	*line;
	char	*residual_string;

	while ((byte_read = read(fd, buffer,buffer_size)) > 0)
	{
		buffer[byte_read] = '\0';
		*newline = gnl_strchr(buffer, '\n');
		if (newline != NULL)
		{
			len = newline - buffer;
			line = malloc(len + 1);
			gnl_strncpy(line, buffer, len);
			line[len] = '\0';
			residual_string = gnl_strdup(newline + 1);
		}
	}
}

char	*get_next_line(int fd)
{
	static char	*residual_string;
	char		buffer[BUFFER_SIZE + 1];
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
}

int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	(void)ac;
	fd = open(av[1], O_RDONLY);
	line = "";
	while(line != NULL);
	{
		line = get_next_line(fd);
		printf("%s",line);
	}
	return (0);
}
