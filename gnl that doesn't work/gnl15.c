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


char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int buffer_pos = 0;
    static int buffer_size = 0;

    char *line = NULL;
    int line_size = 0;

    while (1) {
        if (buffer_pos >= buffer_size) {
            buffer_size = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;

            if (buffer_size <= 0) {
                if (line_size == 0) {
                    return NULL;
                }
                break;
            }
        }

        char c = buffer[buffer_pos++];
        if (c == '\n') {
            break;
        }

        line = realloc(line, line_size + 1);
        if (!line) {
            return NULL;
        }
        line[line_size++] = c;
    }

    if (line) {
        line[line_size] = '\0';
    }

    return line;
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
