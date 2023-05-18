/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl9.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:06:13 by robhak            #+#    #+#             */
/*   Updated: 2023/05/18 10:09:51 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	free(s1);
	return (new_str);
}

static char	*ft_get_line(char **str)
{
	char	*line;
	int		nl_index;

	nl_index = ft_newline(*str);
	if (nl_index >= 0)
	{
		line = ft_substr(*str, 0, nl_index + 1);
		if (!line)
			return (NULL);
		*str = ft_substr(*str, nl_index + 1, ft_strlen(*str) - nl_index - 1);
		if (!*str)
			return (NULL);
	}
	else
	{
		line = ft_strdup(*str);
		if (!line)
			return (NULL);
		free(*str);
		*str = NULL;
	}
	return (line);
}

char *get_next_line(int fd)
{
	static char *str;
	char buf[BUFFER_SIZE + 1];
	ssize_t bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		str = ft_strjoin(str, buf);
		if (!str)
			return (NULL);
		if (ft_newline(str) >= 0)
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes_read < 0 || !str)
		return (NULL);
	return (ft_get_line(&str));
}

int main (int ac, char **av)
{
	int fd;
	char *line;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		while ((line = get_next_line(fd)))
		{
			printf("%s\n", line);
			free(line);
		}
		close(fd);
	}
	return (0);
}