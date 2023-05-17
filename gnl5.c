#include "get_next_line.h"

char *get_line(char **remainder, int line_found)
{
    char *line;
    int len;

    if (line_found >= 0)
    {
        len = line_found;
        line = ft_substr(*remainder, 0, len + 1);
    }
    else
    {
        len = ft_strlen(*remainder);
        line = ft_substr(*remainder, 0, len);
    }
    return (line);
}

char *update_remainder(char **remainder, int line_found)
{
    char *new_remainder;
    int len;

    if (line_found >= 0)
    {
        len = ft_strlen(*remainder) - (line_found + 1);
        new_remainder = ft_substr(*remainder, line_found + 1, len);
    }
    else
        new_remainder = ft_strdup("");
    free(*remainder);
    *remainder = NULL;
    return (new_remainder);
}

char *get_line_and_update_remainder(char **remainder, int line_found)
{
    char *line;
    char *new_remainder;
    int len;

    if (line_found >= 0)
    {
        len = line_found;
        line = ft_substr(*remainder, 0, len + 1);
        len = ft_strlen(*remainder) - (line_found + 1);
        new_remainder = ft_substr(*remainder, line_found + 1, len);
    }
    else
    {
        len = ft_strlen(*remainder);
        line = ft_substr(*remainder, 0, len);
        new_remainder = ft_strdup("");
    }
    free(*remainder);
    *remainder = new_remainder;
    return (line);
}

char *get_next_line(int fd)
{
    static char *remainder[FD_MAX];
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;
    int line_found;

    if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
        return (NULL);
    if (!remainder[fd])
        remainder[fd] = ft_strdup("");
    line_found = find_newline(remainder[fd]);
    while (line_found == -1)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            break ;
        buffer[bytes_read] = '\0';
        remainder[fd] = ft_strjoin(remainder[fd], buffer);
        line_found = find_newline(remainder[fd]);
    }
    if (bytes_read < 0 || (bytes_read == 0 && !*remainder[fd]))
        return (free_and_return_null(&remainder[fd]));
    return (get_line_and_update_remainder(&remainder[fd], line_found));
}
