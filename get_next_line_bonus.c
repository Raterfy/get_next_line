/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:48:28 by robhak            #+#    #+#             */
/*   Updated: 2023/05/30 15:46:53 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(char *residual)
{
	char	*line;
	char	*line_end;
	size_t	len;

	if (!*residual)
		return (NULL);
	line_end = residual;
	while (*line_end && *line_end != '\n')
		line_end++;
	len = line_end - residual;
	line = malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	ft_strlcpy(line, residual, len + 1);
	if (*line_end == '\n')
	{
		line[len] = '\n';
		line[len + 1] = '\0';
	}
	return (line);
}

char	*get_remaining_string(char *residual)
{
	char	*line_end;
	char	*remaining_str;
	size_t	remaining_len;

	line_end = residual;
	while (*line_end && *line_end != '\n')
		line_end++;
	if (!*line_end)
	{
		free(residual);
		return (NULL);
	}
	line_end++;
	remaining_len = ft_strlen(line_end);
	remaining_str = malloc(sizeof(char) * (remaining_len + 1));
	if (!remaining_str)
		return (NULL);
	ft_strlcpy(remaining_str, line_end, remaining_len + 1);
	free(residual);
	return (remaining_str);
}

char	*read_and_store(int fd, char *residual)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0 && !ft_strchr(residual, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		residual = ft_strjoin(residual, buffer);
	}
	free(buffer);
	return (residual);
}

char	*get_next_line(int fd)
{
	static char	*residual[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	residual[fd] = read_and_store(fd, residual[fd]);
	if (!residual[fd])
		return (NULL);
	line = get_line(residual[fd]);
	residual[fd] = get_remaining_string(residual[fd]);
	return (line);
}
