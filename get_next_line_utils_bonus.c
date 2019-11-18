/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:52:45 by schene            #+#    #+#             */
/*   Updated: 2019/11/18 16:53:48 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cmp;

	i = 0;
	cmp = c;
	if (!s)
		return (NULL);
	while (((s[i] + 1 && cmp == '\0') || s[i]) && s != NULL)
	{
		if (s[i] == cmp)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_newstr(int size)
{
	char	*s;
	int		i;

	i = 0;
	if (!(s = malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (i < size)
		s[i++] = 0;
	s[size] = '\0';
	return (s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	join = NULL;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}

char	*ft_substr(char const *s, int start, int len)
{
	int		i;
	char	*sub;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return ("\0");
	if (!(sub = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s[start] && i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	if (!(copy = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
