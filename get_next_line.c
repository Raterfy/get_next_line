/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/11 16:08:04 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_readline(char *residual_str, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*newline;
	char	*tmp;
	int		byte_read;

	byte_read = read(fd, buffer, BUFFER_SIZE);
	newline = gnl_strchr(residual_str, '\n');
	while (byte_read > 0)
	{
		buffer[byte_read] = '\0';
		tmp = gnl_strjoin(buffer, residual_str);
		free(residual_str);
		residual_str = tmp;
		if (newline)
			break ;
	}
	if (byte_read <= 0 && !newline)
		return (NULL);
	if (newline)
		*newline = '\0';
	return (residual_str);
}

char	*get_next_line(int fd)
{
	static char	*residual_string;
	char		*line;
	char		*newline;

	newline = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!residual_string || !(newline = gnl_strchr(residual_string, '\n')))
		residual_string = gnl_readline(residual_string, fd);
	if (!residual_string)
		return (NULL);
	if (newline)
	{
		line = gnl_strncpy(gnl_strdup(residual_string),
				residual_string, newline - residual_string + 1);
		residual_string = gnl_strcpy(residual_string, newline + 1);
	}
	else
	{
		line = gnl_strdup(residual_string);
		free(residual_string);
		residual_string = NULL;
	}
	return (line);
}

int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	(void)ac;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	while ((line = get_next_line(fd)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
