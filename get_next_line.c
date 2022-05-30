/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:07:11 by ktang             #+#    #+#             */
/*   Updated: 2022/05/20 20:03:04 by ktang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	newstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (0);
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}

int	ft_get_eol(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (++i);
		i++;
	}
	return (0);
}

char	*getline_gonext(char **str)
{
	int		i;
	int		j;
	char	*line;
	char	*store;

	i = ft_get_eol(*str);
	if (i == 0)
		i = ft_strlen(*str);
	line = malloc(i + 1);
	line[i] = '\0';
	while (i-- > 0)
		line[i] = (*str)[i];
	store = NULL;
	i = ft_strlen(*str) - ft_get_eol(*str);
	if (i != ft_strlen(*str) && i > 0)
	{
		store = malloc(i + 1);
		store[i++] = '\0';
		j = ft_strlen(*str);
		while (i-- > 0)
			store[i] = (*str)[j--];
	}
	free(*str);
	*str = store;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*storage[OPEN_MAX];
	int			byte_read;

	if (BUFFER_SIZE < 1 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	while (!ft_get_eol(&storage[fd][0]))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == 0)
			break ;
		buffer[byte_read] = '\0';
		storage[fd] = ft_strjoin(storage[fd], buffer);
	}
	free(buffer);
	if (!storage[fd])
		return (NULL);
	return (getline_gonext(&storage[fd]));
}
