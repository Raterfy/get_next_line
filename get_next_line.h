/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:07:02 by robhak            #+#    #+#             */
/*   Updated: 2023/05/11 00:20:55 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1048

int		gnl_strlen(char *s);
char	*gnl_strcat(char *dest, char *src);
void	*gnl_realloc(void *ptr, size_t size);

#endif
