/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/11 12:47:43 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*static char	append_line(char *line, char *buff)
{
	char	*new_line;

	new_line = gnl_strjoin(line, buff);
	free(line);
	return (new_line);
}*/

char	*get_next_line(int fd)
{
	static char	*residual_string;
	char		*line;
	ssize_t		byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = gnl_strdup(residual_string);
	while (!gnl_strchr(line, '\n'))
	{
		
	}
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
		printf("%s\n",line);
	}
	return (0);
}
