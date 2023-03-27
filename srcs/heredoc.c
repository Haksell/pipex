/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:13:10 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 22:06:46 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static unsigned int	backup_random(void)
{
	static unsigned int	x = 42;

	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return (x);
}

static unsigned int	gen_random(void)
{
	const int		fd = open("/dev/random", O_RDONLY);
	unsigned int	target;
	unsigned char	buffer[4];
	ssize_t			bytes_read;

	if (fd < 0)
		return (backup_random());
	bytes_read = read(fd, buffer, 4);
	close(fd);
	if (bytes_read < 4)
		return (backup_random());
	ft_memcpy(&target, buffer, 4);
	return (target);
}

static char	*gen_heredoc_filename(void)
{
	char	*filename;
	int		i;

	i = 0;
	while (i < HEREDOC_TRIES)
	{
		filename = ft_sprintf("%s%u", HEREDOC_PREFIX, gen_random());
		if (filename != NULL && access(filename, F_OK) != 0)
			return (filename);
		free(filename);
		++i;
	}
	return (NULL);
}

static bool	is_end_heredoc(char *line, char *eof)
{
	const size_t	length = ft_strlen(eof);

	if (line == NULL)
	{
		ft_dprintf(STDERR_FILENO, HEREDOC_WARNING, eof);
		return (true);
	}
	return (ft_strncmp(line, eof, length) == 0
		&& (line[length] == '\0' || line[length] == '\n'));
}

char	*heredoc(char *eof)
{
	int		fd;
	char	*line;
	char	*filename;
	ssize_t	written;

	filename = gen_heredoc_filename();
	if (filename == NULL)
		return (perror("gen_heredoc_filename"), NULL);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (perror("open"), free(filename), NULL);
	while (true)
	{
		ft_putstr_fd(HEREDOC_PROMPT, STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (is_end_heredoc(line, eof))
			return (close(fd), free(line), filename);
		written = ft_putstr_fd(line, fd);
		free(line);
		if (written == -1)
			return (perror("ft_putendl_fd"), close(fd), free(filename), NULL);
	}
}
