/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/14 14:59:16 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest;
	char		buf[BUFFER_SIZE + 1];
	ssize_t		ret;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		rest = ft_strjoin(rest, buf);
		if (ft_strchr(rest, '\n'))
			break ;
	}
	if (ret == -1 || (!ret && !rest))
		return (NULL);
	line = ft_substr(rest, 0, ft_strchr(rest, '\n') - rest + 1);
	tmp = rest;
	rest = ft_strdup(ft_strchr(rest, '\n') + 1);
	free(tmp);
	return (line);
}

int	main()
{
	int		fd = open("test.txt", O_RDONLY);
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("%s\n", line);
			free(line);
		}
		else
			break;
	}
	close(fd);
	return (0);
}
