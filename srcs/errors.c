/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 09:24:12 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 09:26:14 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	error_filename(char *filename)
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
	return (false);
}

int	error_not_found(char *command)
{
	char		*message;

	message = ft_strjoin3("pipex: ", command, ": command not found\n");
	if (message == NULL)
		return (perror("malloc"), EXIT_FAILURE);
	ft_putstr_fd(message, STDERR_FILENO);
	free(message);
	return (RET_NOT_FOUND);
}

bool	error_usage(char *command, char *message)
{
	ft_putstr_fd("Usage: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (false);
}
