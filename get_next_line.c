/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/14 14:46:36 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



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
