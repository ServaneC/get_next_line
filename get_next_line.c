/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 09:32:49 by schene            #+#    #+#             */
/*   Updated: 2019/11/17 16:45:15 by schene           ###   ########.fr       */
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

void	ft_delstr(char **str)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
	return ;
}

int		ret_end(char **mem, int ret, int fd)
{
	if (ret < 0)
	{
		free(mem[fd]);
		return (-1);
	}
	return (0);
}

int		ft_line(char **mem, char **line, int fd, int ret)
{
	char	*tmp;
	int		len;

	len = 0;
	while (mem[fd][len] != '\n' && mem[fd][len] != '\0')
		len++;
	if (mem[fd][len] == '\n')
	{
		*line = ft_substr(mem[fd], 0, len);
		tmp = ft_strdup(&mem[fd][len + 1]);
		ft_delstr(&mem[fd]);
		mem[fd] = tmp;
		if (mem[fd][0] == '\0')
			ft_delstr(&mem[fd]);
	}
	else if (mem[fd][len] == '\0')
	{
		if (ret == BUFFER_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(mem[fd]);
		ft_delstr(&mem[fd]);
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*mem[255];
	char		*buf;
	char		*tmp;
	int			ret;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	buf = NULL;
	if (!(buf = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (mem[fd] == NULL)
			mem[fd] = ft_newstr(1);
		tmp = ft_strjoin(mem[fd], buf);
		free(mem[fd]);
		mem[fd] = tmp;
		if (ft_strchr(mem[fd], '\n'))
			break ;
	}
	free(buf);
	if (ret < 0 || (ret == 0 && (mem[fd] == NULL || mem[fd][0] == '\0')))
		return (ret_end(mem, ret, fd));
	return (ft_line(mem, line, fd, ret));
}
