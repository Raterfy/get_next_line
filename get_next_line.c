/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/02 00:18:00 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*rest[4096];
	char		buf[BUFFER_SIZE + 1];
	ssize_t		rd;
	char		*line;
	char		*tmp;

	if (read(fd, buf, 0) < 0 || BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	line = gnl_strdup(rest[fd]);
	while (!gnl_strchr(rest[fd], '\n') && (rd = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[rd] = '\0';
		tmp = gnl_strjoin(line, buf);
		free(line);
		line = tmp;
	}
	if (rd < 0 || !line)
		return (NULL);
	tmp = gnl_substr(line, 0, gnl_strlen(line));
	if (gnl_strchr(line, '\n'))
		rest[fd] = gnl_substr(line, gnl_strchr(line, '\n') - line + 1, gnl_strlen(line) - gnl_strchr(line, '\n') - 1);
	else
		rest[fd] = NULL;
	free(line);
	return (tmp);
}
