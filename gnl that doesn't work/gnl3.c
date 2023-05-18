#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <stdarg.h>
#include <fcntl.h>

#define BUFFER_SIZE 42

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	char	*ptr;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ptr = dup;
	while (*s)
		*ptr++ = *s++;
	*ptr = '\0';
	return (dup);
}

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char *ft_strcpy(char *dest, const char *src)
{
    size_t i;

    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	ptr = new_str;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (new_str);
}

char *get_line(char *str)
{
    char *line;
    int i;

    if (!str)
        return (NULL);
    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    line = (char *)malloc(sizeof(char) * (i + 2));
    if (!line)
        return (NULL);
    i = 0;
    while (str[i] && str[i] != '\n')
    {
        line[i] = str[i];
        i++;
    }
    if (str[i] == '\n')
    {
        line[i] = str[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

char *get_remainder(char *str)
{
    char *remainder;
    int i;
    int j;

    if (!str)
        return (NULL);
    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    if (!str[i])
    {
        free(str);
        return (NULL);
    }
    remainder = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
    if (!remainder)
        return (NULL);
    i++;
    j = 0;
    while (str[i])
        remainder[j++] = str[i++];
    remainder[j] = '\0';
    free(str);
    return (remainder);
}

char *get_next_line(int fd)
{
    static char *remainder;
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        remainder = ft_strjoin(remainder, buffer);
        if (ft_strchr(remainder, '\n'))
            break ;
    }
    if (bytes_read < 0)
        return (NULL);
    line = get_line(remainder);
    remainder = get_remainder(remainder);
    if (bytes_read == 0 && !remainder)
        return (NULL);
    return (line);
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
