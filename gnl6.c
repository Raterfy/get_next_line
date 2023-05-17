/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:15:23 by robhak            #+#    #+#             */
/*   Updated: 2023/05/17 17:50:09 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *residual)
{
	int		i;
	t_list	*current;

	if (residual == NULL)
		return (0);
	current = ft_lst_last(residual);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_lst_last(t_list *residual)
{
	t_list	*current;

	current = residual;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	free_residual(t_list *residual)
{
	t_list	*current;
	t_list	*next;

	current = residual;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

void	create_line(char **line, t_list *residual)
{
	int	i;
	int	len;

	len = 0;
	while (residual)
	{
		i = 0;
		while (residual->content[i])
		{
			if(residual->content[i] == '\n')
			{
				len++;
				break;
			}
			len++;
			i++;
		}
		residual = residual->next;
	}
	line = malloc(sizeof(char) * (len + 1);
}

void	clean_residual(t_list **residual)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (residual == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lst_last(*residual);
	i = 0;
	while (last->content[i] && last->content != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * (ft_strlen(last->content) - i) + 1);
	if (clean_node == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_residual(*residual);
	*residual = clean_node;
}

void	extract_line(t_list *residual, char **line)
{
	int	i;
	int	j;

	j = 0;
	if (residual == NULL)
		return ;
	create_line(line, residual);
	if (*line == NULL)
		return ;
	while (residual)
	{
		i = 0;
		while (residual->content[i])
		{
			if (residual->content[i] == '\n')
			{
				*line[j++] = residual->content[i];
				break;
			}
			*line[j++] = residual->content[i++];
		}
		residual = residual->next;
	}
	(*line)[j] = '\0';
}

void	add_to_residual(t_list **residual, char *buffer, int byte_read)
{
	int	i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (byte_read + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buffer[i] && i < byte_read)
	{
		new_node->content[i] = buffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*residual == NULL)
	{
		*residual = new_node;
		return ;
	}
	last = ft_lst_last(*residual);
	last->next = new_node;
}

void	read_and_residual(int fd, t_list **residual, int *byte_read)
{
	char	*buffer;

	while (!find_newline(*residual) && *byte_read != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		*byte_read = read(fd, buffer, BUFFER_SIZE);
		if (*residual == NULL && *byte_read == 0 || *byte_read < 0)
		{
			free(buffer);
			return ;
		}
		buffer[*byte_read] = '\0';
		add_to_residual(residual, buffer, *byte_read);
		free(buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*residual;
	char			*line;
	int				bytes_read;

	residual = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	bytes_read = 1;
	line = NULL;
	// 1. read from fd and add to linked list
	read_and_residual(fd, &residual, &bytes_read);
	// 2. extract from residual and add to line
	extract_line(residual, &line);
	// 3. clean residual
	clean_residual(&residual);
	return (line);
}

int main()
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s", line);
		free(line);
	}
	return (0);
}