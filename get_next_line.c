/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl18.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:27:43 by robhak            #+#    #+#             */
/*   Updated: 2023/05/19 14:22:46 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
** Cette fonction calcule la longueur d'une ligne en comptant 
** le nombre de caractères
** jusqu'à ce qu'elle atteigne un caractère de nouvelle ligne 
** ('\n') ou un caractère nul ('\0').

** Si un caractère de nouvelle ligne est trouvé, la longueur est incrémentée 
** de 1 pour inclure ce caractère.
*/
size_t	line_length(char *res)
{
	size_t	len;

	len = 0;
	while (res[len] != '\n' && res[len] != '\0')
		len++;
	if (res[len] == '\n')
        len++;
	return (len);
}
/*
** Cette fonction lit une ligne de texte à partir d'un descripteur 
** de fichier `fd` et stocke le résultat dans `res`.

** La fonction `read` est utilisée pour lire jusqu'à `BUFFER_SIZE` 
** caractères à partir du descripteur de fichier.

** Si la lecture réussit, la chaîne lue est terminée par un caractère 
** nul et la longueur de la chaîne lue est renvoyée.

** Sinon, la chaîne `res` est initialisée à une chaîne vide et 
** la fonction renvoie la valeur renvoyée par `read`.
*/
ssize_t	read_line(int fd, char *res)
{
	ssize_t	read_len;

	read_len = read(fd, res, BUFFER_SIZE);
	if (read_len > 0)
		res[read_len] = 0;
	else
		res[0] = 0;
	return (read_len);
}

/*
** Cette fonction lit une ligne de texte à partir d'un descripteur de fichier 
** `fd` et renvoie un pointeur vers une nouvelle chaîne contenant cette ligne.

** La chaîne `res` est utilisée pour stocker les données lues à partir 
** du descripteur de fichier.

** Si `res` est vide, la fonction `read_line` est appelée pour lire des 
** données à partir du descripteur de fichier.

** La longueur de la ligne est calculée en appelant la fonction `line_length`.

** Si la ligne se termine par un caractère de nouvelle ligne, la variable 
** `found_nl` est mise à jour pour indiquer que la fin de la ligne a été trouvée.

** Une nouvelle chaîne est allouée pour stocker la ligne lue 
** et les données restantes dans `res` sont mises à jour.

** La fonction renvoie un pointeur vers la nouvelle chaîne 
** contenant la ligne lue ou NULL en cas d'erreur.
*/
char	*get_line(char *res, int fd, int *found_nl)
{
	ssize_t	read_len;
	char	*line;
	size_t	line_len;
	char	*tmp_res;

	if (ft_strlen(res) == 0)
	{
		read_len = read_line(fd, res);
		if (read_len <= 0)
			return (NULL);
	}
	line_len = line_length(res);
	if (res[line_len - 1] == '\n')
		*found_nl = 1;
	line = malloc(line_len + 1);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, res, line_len + 1);
	tmp_res = ft_strdup((res) + line_len);
	if (tmp_res == NULL)
		return (NULL);
	ft_strlcpy(res, tmp_res, ft_strlen(tmp_res) + 1);
	free(tmp_res);
	return (line);
}
/*
** Cette fonction lit une ligne de texte à partir d'un descripteur 
** de fichier `fd` et renvoie un pointeur vers une nouvelle chaîne 
** contenant cette ligne.

** La fonction utilise une variable statique `res` pour stocker 
** les données lues à partir du descripteur de fichier entre les appels.

** Si le descripteur de fichier est invalide ou si `BUFFER_SIZE` 
** est inférieur ou égal à 0, la fonction renvoie NULL.

** La fonction `get_line` est appelée pour lire une ligne 
** de texte à partir du descripteur de fichier.

** Si la fin de la ligne n'a pas été trouvée, la fonction 
** continue de lire des données à partir du descripteur de fichier 
** jusqu'à ce qu'elle trouve un caractère de nouvelle ligne.

** Les données lues sont concaténées pour former la ligne complète.
** La fonction renvoie un pointeur vers la nouvelle chaîne contenant 
** la ligne lue ou NULL en cas d'erreur.
*/
char	*get_next_line(int fd)
{
	static char	res[BUFFER_SIZE + 1];
	char		*old_line;
	int			found_nl;
	char		*line;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	found_nl = 0;
	line = get_line(res, fd, &found_nl);
	if (line == NULL)
		return (NULL);
	while (found_nl == 0)
	{
		new_line = get_line(res, fd, &found_nl);
		if (new_line == NULL)
			return (line);
		old_line = line;
		line = ft_strjoin(line, new_line);
		free(new_line);
		free(old_line);
	}
	return (line);
}


int main()
{
	int	fd = open("test.txt", O_RDONLY);
	char *line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s\n", line);
		free(line);
	}
	return (0);
}