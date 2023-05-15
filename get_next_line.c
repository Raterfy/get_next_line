/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/15 12:36:52 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	i++;
	line[i] = '\0';
	return (line);
}

char	*get_line_end(char *line, char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] != '\n')
	{
		i++;
		while (line[i])
		{
			buffer[j] = line[i];
			i++;
			j++;
		}
	}
	buffer[j] = '\0';
	return (buffer);
}

char	*get_read_line(int fd, char *buffer, char *line)
{
	int	tmp;

	tmp = 1;
	line = ft_strjoin(line, buffer);
	while (ft_strchr(line, '\n') && tmp != 0)
	{
		tmp = read(fd, buffer, BUFFER_SIZE);
		if (tmp == -1)
			return (NULL);
		buffer[tmp] = '\0';
		line = ft_strjoin(line, buffer);
	}
	if (ft_strchr(line, '\n'))
	{
		buffer = get_line_end(line, buffer);
		line = get_line(line);
	}
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) == -1)
		return (NULL);
	line = get_read_line(fd, line, buffer);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	main(int ac, char **av)
{
	int		fd;
	char	*line;
	(void)ac;

	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
