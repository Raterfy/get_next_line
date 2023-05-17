/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl7.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:18:25 by robhak            #+#    #+#             */
/*   Updated: 2023/05/17 21:56:15 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(int fd)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->content = NULL;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

t_list	*get_fd(t_list **list, int fd)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew(fd);
	ft_lstadd_back(list, tmp);
	return (tmp);
}

int	get_line(char **line, char **content)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*content)[i] && (*content)[i] != '\n')
		i++;
	if ((*content)[i] == '\n')
	{
		*line = ft_substr(*content, 0, i + 1);
		tmp = ft_strdup(*content + i + 1);
		free(*content);
		*content = tmp;
		return (1);
	}
	else
	{
		*line = ft_strdup(*content);
		free(*content);
		*content = NULL;
		return (0);
	}
}

int	read_file(int fd, char **content)
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;
	char 	*tmp;

	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (!*content)
			*content = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(*content, buf);
			free(*content);
			*content = tmp;
		}
		if (ft_strchr(buf, '\n'))
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*current;
	int				ret;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	current = get_fd(&list, fd);
	ret = read_file(fd, &current->content);
	if (ret < 0)
		return (NULL);
	if (!current->content && !ret)
		return (NULL);
	if (get_line(&line, &current->content))
		return (line);
	return (line);
}
