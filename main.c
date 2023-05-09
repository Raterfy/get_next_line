#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <stdarg.h>
#include <fcntl.h>

size_t	ft_strlen(const char *s)
{
	const char	*len;

	len = s;
	while (*len != '\0')
		len++;
	return (len - s);
}


void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}


int main(void)
{
	char *filename = "test.txt";
	int fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	char buffer[5];
	int n;
	while((n = read(fd, buffer, 5)) > 0)
	{
		write(STDOUT_FILENO, buffer, n);
	}
	if (n == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	close (fd);
	return 0;
}