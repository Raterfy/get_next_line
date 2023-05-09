/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/09 23:22:35 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	save;
	char buffer[BUFFER_SIZE + 1];
	int			n;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return(NULL);
	n = read(fd, buffer, BUFFER_SIZE);
	if (n < 0)
		return (NULL);
	buffer[n] = '\0';
	
}
