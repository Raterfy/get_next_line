/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/14 21:50:22 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
static char *get_residual(int fd, char *residual_string)
{
	char	*buffer;
	char	*chr;
	char	*joined;
	int		i;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	chr = ft_strchr(residual_string, '\n');
	while (i != 0 && !chr)
	{
		i = 
	}
}

static char	*get_line(char *residual_string)
{
	char	*residual_tmp;
	int		i;

	i = 0;
	while (residual_string[i] == NULL)
		return (NULL);
	while (residual_string[i] && residual_string[i] != '\n')
		i++;
	residual_tmp = malloc(sizeof(char) * (i + 2));
	if (residual_tmp == NULL)
		return (NULL);
	i = 0;
	while (residual_string[i] && residual_string[i] != '\n')
	{
		residual_tmp[i] = residual_string[i];
		i++;
	}
	if (residual_string[i] == '\n')
	{
		residual_tmp[i] = residual_string[i];
		i++;
	}
	residual_tmp = '\0';
	return (residual_string);
}*/

char	*get_next_line(int fd)
{
	static char	*residual_string;
	char		*line;
	char		*buffer;
	int			read_byte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_byte = read(fd, buffer, BUFFER_SIZE);
	while (read_byte > 0)
	{
		buffer[read_byte] = '\0';
		residual_string = ft_strjoin(residual_string, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	if (read_byte < 0 || !residual_string)
		return (NULL);
	line = ft_substr(residual_string, 0, ft_strchr(residual_string, '\n') - residual_string);
	residual_string = ft_strdup(residual_string + ft_strlen(line) + 1);
	if (!line || !residual_string)
		return (NULL);
	return (line);
}


int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	if (ac < 2)
		return (NULL);
	while (line)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
