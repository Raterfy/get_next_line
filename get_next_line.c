/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/07 20:53:47 by robhak           ###   ########.fr       */
=======
/*   Updated: 2023/05/09 12:41:22 by robhak           ###   ########.fr       */
>>>>>>> a615563c53338fb6c87467c140bdcbad23e96cca
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
<<<<<<< HEAD
	if (fd < 0 || BUFFER_SIZE <= 0)
		return(NULL);
	
}
=======
	char *buff;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
}

int main(void)
{
	int	fd;
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		write(1,"Error open", 10);
		return (0);
	}
	char	buffer[100];
	int n;
	
}
>>>>>>> a615563c53338fb6c87467c140bdcbad23e96cca
