/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/12 13:01:34 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*static char	*gnl_readline(char *residual_str, int fd)
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
		tmp = gnl_strjoin(residual_str, buffer);
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
}*/

static int	read_buffer(int fd, char *buffer, char **residual_string)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (-1);
	buffer[bytes_read] = '\0';
	if (!residual_string)
		*residual_string = gnl_strdup("");
	*residual_string = gnl_strjoin(*residual_string, buffer);
//	free(buffer);
	return (bytes_read);
}

static char	*extract_line(char **residual_string)
{
	char	*new_line;
	char	*tmp;

	new_line = gnl_strchr(*residual_string, '\n');
	//printf("new line = %s\n", new_line);
	if (new_line)
	{
		tmp = gnl_strdup(new_line + 1);
		if (!tmp)
			return (NULL);
	}
	else
	{
		tmp = gnl_strdup(*residual_string);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

static char	*get_next_line_loop(int fd, char **residual_string)
{
	char	*new_line;
	char	*tmp;
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		bytes_read = read_buffer(fd, buffer, residual_string);
		if (bytes_read == -1)
			return (NULL);
		if (gnl_strchr(*residual_string, '\n'))
			break ;
	}
	if (!bytes_read && !gnl_strlen(*residual_string))
		return (NULL);
	new_line = extract_line(residual_string);
	tmp = *residual_string;
	*residual_string = NULL;
	free(tmp);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*residual_string;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (get_next_line_loop(fd, &residual_string));
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open file: %s\n", argv[1]);
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line : %s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
