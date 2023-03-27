/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 05:55:11 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 03:44:25 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_absolute_path(char **path, char *command)
{
	char	*full_path;
	int		i;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	if (command[0] == '\0' || command[0] == '.' || path == NULL)
		return (NULL);
	i = 0;
	while (path[i] != NULL)
	{
		full_path = ft_strjoin3(path[i], "/", command);
		if (full_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		++i;
	}
	return (NULL);
}

char	**get_path(char **env)
{
	int	i;

	if (env == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_startswith(env[i], "PATH="))
			return (ft_split(env[i] + 5, ':'));
		++i;
	}
	return (NULL);
}

bool	is_executable(char *full_path)
{
	bool	return_value;
	int		fd;

	fd = open(full_path, O_RDONLY);
	return_value = (fd != -1
			&& read(fd, NULL, 0) != -1
			&& access(full_path, X_OK) != -1);
	ft_close(&fd);
	return (return_value);
}

void	clean_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		ft_close(&pipes[i][0]);
		ft_close(&pipes[i][1]);
		ft_free((void **)&pipes[i]);
		++i;
	}
	ft_free_double_pointer((void ***)&pipes, num_pipes);
}

void	error_filename(char const *filename)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", filename, strerror(errno));
}