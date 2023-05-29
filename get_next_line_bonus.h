/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:49:07 by robhak            #+#    #+#             */
/*   Updated: 2023/05/29 13:32:37 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE	
#  define BUFFER_SIZE 42
# endif
# define MAX_FD 64000

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <string.h>

char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *res, char *buffer);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*get_next_line(int fd);
char	*read_and_store(int fd, char *residual);
char	*get_remaining_string(char *residual);
char	*get_line(char *residual);

#endif