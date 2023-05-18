/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:07:02 by robhak            #+#    #+#             */
/*   Updated: 2023/05/18 09:32:56 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define FD_MAX 256
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

// typedef struct s_list
// {
// 	char			*content;
// 	struct s_list	*next;
// }				t_list;

typedef struct	s_list
{
	int				fd;
	char			*content;
	struct s_list	*next;
}				t_list;


size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif