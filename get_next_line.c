/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/10 14:07:12 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *save(char *save, char *buffer)
{
	
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read; //nombre de byte lu par read
	char		*line; //str qui contient la ligne lu
	int			i; //se balader dans le buffer
	int			j; //copier les octets dans la lgne

	i = 0;
	j = 0;
	line = NULL;
	save = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	while (bytes_read > 0)
	{
		if (save)//cas ou la variable statique save n'est pas NULL;
		{
			while (save[i] && save[i] != '\n');
				i++;
			line = malloc(sizeof(char) * (i + 1));
			if (!line)
				return (NULL);
			i = 0;
			while(save[i] && save[i] != '\n')
			{
				line[j] = save[i];
				j++;
				i++;
			}
			line[j] = '\0';
			if(save[i] == '\n')
			{
				i++;
				j = 0;
				while(save[i]&& save[i] != '\n')
				{
					buffer[j] = save[i];
					i++;
					j++;
				}
				buffer[j] = '\0';
			}
			free (save);
			save = NULL;
		}
		else 
		{
			while (buffer[i] && buffer[i] != '\n')
				i++;
			line = malloc(sizeof(char) * (i + 1));
			if(!line)
				return (NULL);
			i = 0;
			while (buffer[i] && buffer[i] != '\n')
			{
				line[j] = buffer[i];
				i++;
				j++;
			}
			line[j] = '\0';
			if (buffer[i] != '\n')
			{
				save = malloc(sizeof(char) * (BUFFER_SIZE - i + 1));
				if (!save)
					return (NULL);
				j = 0;
				while(buffer[i])
				{
					save[j] = buffer[i];
					i++;
					j++;
				}
				save[j] = '\0';
				return (line);
			}
			free (save);
			save = NULL;
		}
	}
	return (buffer);
}

int main(void)
{
	char *filename = "test.txt";
	int fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	char buffer[1];
	int n;
	while((n = read(fd, buffer, 1)) > 0)
	{
		write(STDOUT_FILENO, buffer, n);
	}
	if (n == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	close (fd);
	return 0;
}