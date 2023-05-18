#include "get_next_line.h"

int find_newline(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

char *ft_strdup(const char *s1)
{
    char *s2;
    size_t len;
    size_t i;

    len = ft_strlen(s1);
    s2 = (char *)malloc(sizeof(char) * (len + 1));
    if (!s2)
        return (NULL);
    i = 0;
    while (i < len)
    {
        s2[i] = s1[i];
        i++;
    }
    s2[i] = '\0';
    return (s2);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    char *new_str;
    size_t len1;
    size_t len2;
    size_t i;
    size_t j;

    if (!s1 || !s2)
        return (NULL);
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    new_str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!new_str)
        return (NULL);
    i = 0;
    while (i < len1)
    {
        new_str[i] = s1[i];
        i++;
    }
    j = 0;
    while (j < len2)
    {
        new_str[i + j] = s2[j];
        j++;
    }
    new_str[i + j] = '\0';
    free((char *)s1);
    return (new_str);
}

char *free_and_return_null(char **str)
{
    if (*str)
        free(*str);
    *str = NULL;
    return (NULL);
}

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

char *get_next_line(int fd)
{
    static char *remainder;
    char *line;
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;
    int line_found;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!remainder)
        remainder = ft_strdup("");
    line_found = find_newline(remainder);
    while (line_found == -1)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            break ;
        buffer[bytes_read] = '\0';
        remainder = ft_strjoin(remainder, buffer);
        line_found = find_newline(remainder);
    }
    if (bytes_read < 0 || (bytes_read == 0 && !*remainder))
        return (free_and_return_null(&remainder));
    line = get_line(&remainder, line_found);
    remainder = update_remainder(&remainder, line_found);
    return (line);
}
