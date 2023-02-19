/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 08:46:39 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 08:46:51 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	perror_filename(char *filename)
{
	char	*full;

	full = ft_strjoin("pipex: ", filename);
	if (full == NULL)
		perror("malloc");
	else
	{
		perror(full);
		free(full);
	}
}

bool	init_files(char *file_in, int *fd_in, char *file_out, int *fd_out)
{
	*fd_in = open(file_in, O_RDONLY);
	if (*fd_in == -1)
		return (perror_filename(file_in), false);
	*fd_out = open(file_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd_out == -1)
		return (close(*fd_in), perror_filename(file_out), false);
	return (true);
}
