/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:27:43 by robhak            #+#    #+#             */
/*   Updated: 2023/05/29 15:29:01 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* 
* Cette fonction prend en entrée une chaîne de caractères appelée "residual" 
* et renvoie une ligne de cette chaîne. La ligne renvoyée inclut le caractère 
* de nouvelle ligne '\n' si elle est présente dans la chaîne d'entrée. 
* La fonction utilise la fonction malloc pour allouer de la mémoire pour 
* la ligne renvoyée et la fonction ft_strlcpy pour copier la ligne de la chaîne 
* d'entrée dans la chaîne renvoyée.
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
* Cette fonction prend en entrée une chaîne de caractères appelée 
* "residual" et renvoie la partie restante de cette chaîne après 
* la première ligne. 
* La fonction utilise la fonction malloc pour allouer de la mémoire 
* pour la chaîne renvoyée et la fonction ft_strlcpy pour copier 
* la partie restante 
* de la chaîne d'entrée dans la chaîne renvoyée. 
* Si la chaîne d'entrée ne contient 
* pas de caractère de nouvelle ligne '\n', 
* la fonction libère la mémoire allouée pour la chaîne d'entrée 
* et renvoie NULL.
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
** La fonction read_and_store lit des données à partir 
** d'un descripteur de fichier et les stocke dans une chaîne 
** de caractères résiduelle.
** La fonction utilise un tampon pour lire les données par blocs 
** de taille BUFFER_SIZE
** et ajoute les données lues à la chaîne résiduelle en utilisant 
** la fonction ft_strjoin.
** La lecture s'arrête lorsque la fin du fichier est atteinte ou 
** lorsqu'un caractère '\n' est trouvé dans la chaîne résiduelle.
** Si une erreur se produit lors de la lecture, la fonction renvoie NULL.
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
* Cette fonction prend en entrée un descripteur de fichier "fd" 
* et renvoie la ligne suivante du fichier. La fonction utilise 
* une variable statique "residual" pour stocker les données lues 
* du fichier qui n'ont pas encore été renvoyées. La fonction utilise 
* les fonctions read_and_store, get_line et get_remaining_string pour lire
* le contenu du fichier, extraire la ligne suivante et mettre à jour 
* la chaîne "residual". Si le descripteur de fichier est invalide ou si 
* la taille du tampon est inférieure ou égale à zéro, la fonction renvoie 0.
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
