/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/09 12:41:22 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
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
