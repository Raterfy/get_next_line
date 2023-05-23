/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:07:02 by robhak            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/21 19:20:51 by robhak           ###   ########.fr       */
=======
/*   Updated: 2023/05/23 14:17:04 by robhak           ###   ########.fr       */
>>>>>>> c6d887cabcc8397c32aafb46c2f1a125e7c67035
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE	
#  define BUFFER_SIZE 42
# endif

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <string.h>
// # define malloc(x) (0)

char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *res, char *buffer);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*get_next_line(int fd);

#endif