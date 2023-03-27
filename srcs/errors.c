/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:24:12 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 03:08:25 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_filename(char const *filename)
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
	return (RET_BAD_COMMAND);
}

int	error_not_found(char *command)
{
	char		*message;

	message = ft_strjoin3("pipex: ", command, ": command not found\n");
	if (message == NULL)
		return (perror("malloc"), EXIT_FAILURE);
	ft_putstr_fd(message, STDERR_FILENO);
	free(message);
	return (RET_BAD_COMMAND);
}
