/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 08:07:19 by robhak            #+#    #+#             */
/*   Updated: 2023/04/29 08:14:11 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *dst_copy;
    const unsigned char *src_copy;

    dst_copy = dst;
    src_copy = src;
    while (n--)
        *dst_copy++ = *src_copy++;
    return (dst);
}

char	*ft_realloc(char *ptr, size_t old_size, size_t new_size)
{
    char *new_ptr;

    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
    {
        free(ptr);
        return (NULL);
    }
    if (ptr != NULL)
    {
        ft_memcpy(new_ptr, ptr, old_size);
        free(ptr);
    }
    return (new_ptr);
}

int	read_until_newline(int fd, char *buffer, int *buffer_index, int *buffer_size, char *line)
{
    int i;
    int n;

    i = 0;
    while (1)
    {
        if (*buffer_index >= *buffer_size)
        {
            n = read(fd, buffer, BUFFER_SIZE);
            if (n == -1)
                return (-1);
            if (n == 0)
                return (i);
            *buffer_index = 0;
            *buffer_size = n;
        }
        if (buffer[*buffer_index] == '\n')
        {
            line[i] = '\n';
            *buffer_index += 1;
            return (i + 1);
        }
        line[i] = buffer[*buffer_index];
        *buffer_index += 1;
        i += 1;
        if (i % BUFFER_SIZE == 0)
        {
            line = ft_realloc(line, i, i + BUFFER_SIZE);
            if (line == NULL)
                return (-1);
        }
    }
}
