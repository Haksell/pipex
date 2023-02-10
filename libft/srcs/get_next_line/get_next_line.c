/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 04:55:55 by axbrisse          #+#    #+#             */
/*   Updated: 2023/01/22 05:13:14 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	inplace_strjoin(char **s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = joined;
}

static char	*get_start(char *s, size_t len)
{
	char	*dest;

	dest = malloc(len + 1);
	if (dest != NULL)
		ft_strlcpy(dest, s, len + 1);
	free(s);
	return (dest);
}

static int	find_newline(char *s)
{
	int	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i] != '\0')
		{
			if (s[i] == '\n')
				return (i);
			++i;
		}
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	buffers[FILE_DESCRIPTORS][BUFFER_SIZE + 1] = {0};
	ssize_t		bytes_read;
	int			nl_index;
	char		*line;

	if (fd < 0 || fd >= FILE_DESCRIPTORS)
		return (NULL);
	line = ft_strdup(buffers[fd]);
	nl_index = find_newline(line);
	bytes_read = BUFFER_SIZE;
	while (line != NULL && nl_index == -1 && bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buffers[fd], BUFFER_SIZE);
		buffers[fd][bytes_read] = '\0';
		inplace_strjoin(&line, buffers[fd]);
		nl_index = find_newline(line);
	}
	if (line == NULL || line[0] == '\0')
		return (free(line), NULL);
	else if (nl_index == -1)
		return (buffers[fd][0] = '\0', line);
	else
		return (
			ft_strlcpy(buffers[fd], line + nl_index + 1, INT_MAX),
			get_start(line, nl_index + 1));
}
