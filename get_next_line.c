/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:07:11 by ktang             #+#    #+#             */
/*   Updated: 2022/06/03 19:06:27 by ktang            ###   ########.fr       */
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
	while (s1 && s1[i] != '\0')
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

char	*ft_get_line(char **str, int nl_pos)
{
	char	*line;
	int		i;

	if (nl_pos == 0)
		nl_pos = ft_strlen(*str);
	line = malloc(nl_pos + 1);
	line[nl_pos] = '\0';
	i = 0;
	while (i < nl_pos)
	{
		line[i] = str[0][i];
		i++;
	}
	return (line);
}

char	*ft_next_line(char **str)
{
	char	*next;
	int		i;
	int		j;

	next = NULL;
	i = ft_strlen(*str) - ft_get_eol(*str);
	if (i != ft_strlen(*str) && i > 0)
	{
		next = malloc(i + 1);
		next[i++] = '\0';
		j = ft_strlen(*str);
		while (i-- > 0)
		{
			next[i] = str[0][j];
			j--;
		}		
	}
	free(*str);
	*str = next;
	return (next);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*storage[FOPEN_MAX];
	char		*line;
	int			byte_read;

	if (BUFFER_SIZE < 1 || fd < 0 || fd > FOPEN_MAX)
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
	line = ft_get_line(&storage[fd], ft_get_eol(storage[fd]));
	storage[fd] = ft_next_line(&storage[fd]);
	return (line);
}
