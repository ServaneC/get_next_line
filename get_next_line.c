/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:34:30 by schene            #+#    #+#             */
/*   Updated: 2019/11/19 14:42:42 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int		ft_delstr(char **mem, int ret, int fd, char **line)
{
	if (mem[fd] || ret < 0)
	{
		free(mem[fd]);
		mem[fd] = NULL;
		return (-1);
	}
	*line = ft_strdup("\0");
	free(mem[fd]);
	return (0);
}

int		ft_linelen(char **mem, int fd)
{
	int	len;

	len = 0;
	while (mem[fd][len] != '\n' && mem[fd][len] != '\0')
		len++;
	return (len);
}

int		ft_line(char **mem, char **line, int fd, int ret)
{
	char	*tmp;
	int		len;

	len = ft_linelen(mem, fd);
	if (mem[fd][len] == '\n')
	{
		if ((*line = ft_substr(mem[fd], 0, len)) == NULL ||
				(tmp = ft_strdup(&mem[fd][len + 1])) == NULL)
			return (-1);
		free(mem[fd]);
		mem[fd] = tmp;
		if (mem[fd][0] == '\0')
			ft_delstr(mem, ret, fd, line);
	}
	else if (mem[fd][len] == '\0')
	{
		if (ret == BUFFER_SIZE)
			return (get_next_line(fd, line));
		if ((*line = ft_strdup(mem[fd])) == NULL)
			return (-1);
		ft_delstr(mem, ret, fd, line);
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*mem[2147483647];
	char		*buf;
	char		*tmp;
	int			ret;

	buf = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 ||
			!(buf = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (mem[fd] == NULL)
			mem[fd] = ft_newstr(1);
		if ((tmp = ft_strjoin(mem[fd], buf)) == NULL)
			return (-1);
		free(mem[fd]);
		mem[fd] = tmp;
		if (ft_strchr(mem[fd], '\n'))
			break ;
	}
	free(buf);
	if (ret < 0 || (ret == 0 && (mem[fd] == NULL || mem[fd][0] == '\0')))
		return (ft_delstr(mem, ret, fd, line));
	return (ft_line(mem, line, fd, ret));
}
