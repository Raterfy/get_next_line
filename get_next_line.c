/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:26:15 by robhak            #+#    #+#             */
/*   Updated: 2023/05/18 17:55:18 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Cette fonction lit des données à partir d'un descripteur de fichier `fd` 
 * et les ajoute à la chaîne `res` jusqu'à ce qu'un caractère de saut de ligne 
 * (`'\n'`) soit trouvé dans `res` ou que la fin du fichier soit atteinte. 
 * La fonction renvoie une nouvelle chaîne contenant les données lues.
*/
char	*residual_left(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	byte_read = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (byte_read != 0 && !ft_strchr(res, '\n'))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = '\0';
		res = ft_strjoin(res, buffer);
	}
	free(buffer);
	return (res);
}

/*
 * Cette fonction prend une chaîne `res` en argument et renvoie une 
 * nouvelle chaîne contenant tous les caractères après le premier caractère 
 * de saut de ligne (`'\n'`). Si aucun caractère de saut de ligne n'est trouvé,
 * la fonction renvoie `NULL`.
 */
char	*new_res(char *res)
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (!res[i])
	{
		free(res);
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (ft_strlen(res) - i + 1));
	if (!buffer)
		return (NULL);
	i++;
	j = 0;
	while (res[i])
		buffer[j++] = res[i++];
	buffer[j] = '\0';
	free(res);
	return (buffer);
}

/*
 * Cette fonction prend une chaîne `res` en argument et renvoie une 
 * nouvelle chaîne contenant tous les caractères
 * jusqu'au premier caractère de saut de ligne (`'\n'`) inclus. 
 * Si la chaîne `res` est vide, la fonction renvoie `NULL`.
 */
char	*get_line(char *res)
{
	char	*buffer;
	int		i;

	i = 0;
	if (!res[i])
		return (NULL);
	while (res[i] != '\n' && res[i])
		i++;
	buffer = malloc(sizeof(char) * (i + 2));
	if (!buffer)
		return (NULL);
	i = 0;
	while (res[i] && res[i] != '\n')
	{
		buffer[i] = res[i];
		i++;
	}
	if (res[i] == '\n')
	{
		buffer[i] = res[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

/*
 * Cette fonction lit une ligne à partir d'un descripteur de fichier `fd` 
 * et renvoie cette ligne sous forme de chaîne.
 * La fonction utilise une variable statique `res` pour stocker les données 
 * lues à partir du descripteur de fichier
 * entre les appels à la fonction. Si `fd` est inférieur à 0 ou 
 * si `BUFFER_SIZE` est inférieur ou égal à 0, la fonction renvoie 0.
 */
char	*get_next_line(int fd)
{
	static char	*res;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	res = residual_left(fd, res);
	if (!res)
		return (NULL);
	line = get_line(res);
	res = new_res(res);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s", line);
		free(line);
	}
	return (0);
}
