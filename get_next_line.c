/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:27:43 by robhak            #+#    #+#             */
/*   Updated: 2023/06/01 21:28:53 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Extrait la ligne à partir de la chaîne de caractères donnée.
 * 
 * @param residual La chaîne de caractères contenant la ligne à extraire.
 * @return Un pointeur vers la ligne extraite, ou NULL si la chaîne est vide.
 */
char	*get_line(char *residual)
{
	char	*line;
	char	*line_end;
	size_t	len;

	if (!*residual)
		return (NULL);
	line_end = residual;
	while (*line_end && *line_end != '\n')
		line_end++;
	len = line_end - residual;
	line = malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	ft_strlcpy(line, residual, len + 1);
	if (*line_end == '\n')
	{
		line[len] = '\n';
		line[len + 1] = '\0';
	}
	return (line);
}

/*
 * Récupère la partie restante d'une chaîne de caractères après avoir
 * lu une ligne complète.
 * @param residual La chaîne de caractères contenant la partie restante.
 * @return Un pointeur vers la partie restante de la chaîne, 
 * ou NULL si la fin de la chaîne est atteinte ou en cas d'erreur.
 */
char	*get_remaining_string(char *residual)
{
	char	*line_end;
	char	*remaining_str;
	size_t	remaining_len;

	line_end = residual;
	while (*line_end && *line_end != '\n')
		line_end++;
	if (!*line_end)
	{
		free(residual);
		return (NULL);
	}
	line_end++;
	remaining_len = ft_strlen(line_end);
	remaining_str = malloc(sizeof(char) * (remaining_len + 1));
	if (!remaining_str)
		return (NULL);
	ft_strlcpy(remaining_str, line_end, remaining_len + 1);
	free(residual);
	return (remaining_str);
}

/*
 * Lit les données à partir du descripteur de fichier donné et les stocke 
 * dans une variable résiduelle.
 * @param fd Le descripteur de fichier à partir duquel lire les données.
 * @param residual La variable résiduelle pour stocker les données non lues.
 * @return Un pointeur vers la variable résiduelle mise à jour, 
 * ou NULL en cas d'erreur.
 */
char	*read_and_store(int fd, char *residual)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0 && !ft_strchr(residual, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		residual = ft_strjoin(residual, buffer);
	}
	free(buffer);
	return (residual);
}

/*
 * Lit la prochaine ligne à partir d'un descripteur de fichier donné.
 * @param fd Le descripteur de fichier à partir duquel lire la ligne.
 * @return Un pointeur vers la ligne lue, ou NULL si la fin du fichier
 * est atteinte ou en cas d'erreur.
 */
char	*get_next_line(int fd)
{
	static char	*residual;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	residual = read_and_store(fd, residual);
	if (!residual)
		return (NULL);
	line = get_line(residual);
	residual = get_remaining_string(residual);
	return (line);
}

// int main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break;
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	return (0);
// }
