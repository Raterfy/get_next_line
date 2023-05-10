/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/10 11:55:06 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read;//nombre de byte lu par read
	char		*line;
	int			i;// se balader dans le buffer
	int			j;// copier les octets dans la lgne

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
	while (1)
	{
		if (save)//cas ou la variable statique save n'est pas NULL;
		{
			while (save[i] && save[i] != "\n");
				i++;
			line = malloc(sizeof(char) * (i + 1));
			if (!line)
				return (NULL);
			i = 0;
			while(save[i] && save[i] != "\n")
			{
				line[j] = save[i];
				j++;
				i++;
			}
			line[j] = "\0";
			if(save[i] == "\n")
			{
				i++;
				j = 0;
				while(save[i]&& save[i] != "\n")
				{
					buffer[j] = save[i];
					i++;
					j++;
				}
				buffer[j] = "\0";
			}
			free (save);
			save = NULL;
		}
		else
		{
			while ()
		}
	}
}

int main()
{
	int	fd = open("test.txt", O_RDONLY);
	int	n;
}
