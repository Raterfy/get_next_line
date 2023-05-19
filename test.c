#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 42

#include "get_next_line.h"




int main()
{
	int	fd = open("test.txt", O_RDONLY);
	char *line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s\n", line);
		free(line);
	}
	return (0);
}