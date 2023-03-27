/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 05:55:11 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/28 00:30:24 by axbrisse         ###   ########.fr       */
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

void	clean_pipes(int **pipes)
{
	int	i;

	if (pipes != NULL)
	{
		i = 0;
		while (pipes[i] != NULL)
		{
			ft_close(&pipes[i][0]);
			ft_close(&pipes[i][1]);
			free(pipes[i]);
			pipes[i] = NULL;
			++i;
		}
		free(pipes);
	}
}

void	free_data(t_data *data)
{
	close(data->fd_in);
	close(data->fd_out);
	clean_pipes(data->pipes);
	if (data->is_heredoc)
	{
		unlink(data->file_in);
		free(data->file_in);
	}
	// ft_free_double((void ***)data->path);
	// ft_free_triple((void ****)data->commands);
}

void	file_error(char *filename)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", filename, strerror(errno));
	exit(EXIT_FAILURE);
}
