/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl7.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robhak <robhak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:18:25 by robhak            #+#    #+#             */
/*   Updated: 2023/05/18 09:46:09 by robhak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s || !c)
		return (NULL);
	while (*s != c)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(src) + 1;
	dest = malloc(sizeof(char) * len);
	if (!dest)
		return (NULL);
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*joined;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	joined = malloc(sizeof(char) * (len + 1));
	if (!joined)
		return (NULL);
	while (s1[i])
		joined[j++] = s1[i++];
	i = 0;
	while (s2[i])
		joined[j++] = s2[i++];
	joined[j] = '\0';
	return (joined);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*substring;
	unsigned int		i;
	unsigned long		len_src;

	if (!s)
		return (NULL);
	len_src = ft_strlen(s);
	if (start >= len_src)
		return (ft_strdup(""));
	if (len_src - start < len)
		len = len_src - start;
	substring = malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = start;
	while (i < start + len && s[i])
	{
		substring[i - start] = s[i];
		i++;
	}
	substring[i - start] = '\0';
	return (substring);
}

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