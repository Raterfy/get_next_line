/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:32:48 by robhak            #+#    #+#             */
/*   Updated: 2023/05/16 18:33:06 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 42

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    static char *remainder = NULL;
    char *line = NULL;
    int bytes_read = 0;
    int i = 0;

    // Check if there is a remainder from a previous call
    if (remainder)
    {
        line = remainder;
        remainder = NULL;
        return line;
    }
    // Read from the file descriptor until a newline or the end of file is reached
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';  // Null-terminate the buffer
        // Search for newline character
        for (i = 0; i < bytes_read; i++)
        {
            if (buffer[i] == '\n')
            {
                line = malloc(i + 2);  // Allocate memory for the line
                if (!line)
                    return NULL;
                // Copy the line from the buffer
                line = strncpy(line, buffer, i + 1);
                line[i + 1] = '\0';  // Null-terminate the line

                // Save the remainder for future calls
                remainder = malloc(bytes_read - i);
                if (!remainder)
                {
                    free(line);
                    return NULL;
                }
                remainder = strncpy(remainder, buffer + i + 1, bytes_read - i);
                remainder[bytes_read - i - 1] = '\0';  // Null-terminate the remainder
                return line;
            }
        }
        // No newline found, append buffer to line
        char *temp = line;
        line = malloc(bytes_read + i + 1);  // Allocate memory for the combined line
        if (!line)
        {
            free(temp);
            return NULL;
        }
        // Copy the contents of the previous line
        if (temp)
        {
            line = strncpy(line, temp, i);
            free(temp);
        }
        // Copy the buffer to the line
        line = strncat(line, buffer, bytes_read);
    }
    // Check or errors or end of file
    if (bytes_read == -1 || (bytes_read == 0 && line == NULL))
    {
        free(line);
        return NULL;
    }
    return line;  // Return the line
}

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
    char    *line = NULL;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (0);
}
