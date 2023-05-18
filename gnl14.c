/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl14.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:37:02 by robhak            #+#    #+#             */
/*   Updated: 2023/05/18 15:13:46 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static char	*join_strings(char *s1, char *s2)
{
    size_t len1 = 0;
    size_t len2 = 0;
    char *new_str;
    size_t i = 0;

    if (s1)
        len1 = strlen(s1);
    if (s2)
        len2 = strlen(s2);
    new_str = malloc(sizeof(char) * (len1 + len2 + 1));
    if (!new_str)
        return (NULL);
    while (i < len1)
    {
        new_str[i] = s1[i];
        i++;
    }
    while (i - len1 < len2)
    {
        new_str[i] = s2[i - len1];
        i++;
    }
    new_str[i] = '\0';
    free(s1);
    return (new_str);
}

static char	*get_line(char **str)
{
    size_t	i;
    char	*line;

	i = 0;
    while ((*str)[i] != '\n' && (*str)[i] != '\0')
        i++;
    line = malloc(sizeof(char) * (i + 2));
    if (!line)
        return (NULL);
    i = 0;
    while ((*str)[i] != '\n' && (*str)[i] != '\0')
    {
        line[i] = (*str)[i];
        i++;
    }
    if ((*str)[i] == '\n')
        i++;
    line[i] = '\0';
    *str = &((*str)[i]);
    return (line);
}

char *get_next_line(int fd)
{
 	static char *str;
 	char *buffer;
 	ssize_t byte_read;

 	if (fd < 0 || BUFFER_SIZE <= 0)
 		return (NULL);
 	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
 	if (!buffer)
 	return (NULL);
 	byte_read = read(fd, buffer, BUFFER_SIZE);
 	while (byte_read > 0)
 	{
 		buffer[byte_read] = '\0';
 		str = join_strings(str, buffer);
 		if (strchr(str, '\n'))
 		break ;
 		byte_read = read(fd, buffer, BUFFER_SIZE);
 	}
 	free(buffer);
 	if (byte_read < 0 || !str)
 		return (NULL);
 	return (get_line(&str));
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file\n");
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
    	free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
