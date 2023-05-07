/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/02 00:37:46 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buf[OPEN_MAX];
	char		*line;
	ssize_t		nb_char_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	if (!buf[fd])
		buf[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf[fd])
		return (NULL);
	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (!ft_strchr(buf[fd], '\n'))
	{
		nb_char_read = read(fd, buf[fd], BUFFER_SIZE);
		if (nb_char_read <= 0)
			break ;
		buf[fd][nb_char_read] = '\0';
		line = ft_strjoin_free(line, buf[fd]);
		if (!line)
			return (NULL);
	}
	if (*buf[fd] == '\0')
	{
		free(buf[fd]);
		buf[fd] = NULL;
		return (NULL);
	}
	line = ft_strchr_dup(buf[fd], '\n');
	ft_strcpy(buf[fd], ft_strchr(buf[fd], '\n') + 1);
	return (line);
}
