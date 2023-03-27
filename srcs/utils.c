/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 05:55:11 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/28 00:33:00 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
