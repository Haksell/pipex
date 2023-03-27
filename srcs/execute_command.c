/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:08:30 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 23:09:38 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	error_not_found(char *command)
{
	char	*message;

	message = ft_strjoin3("pipex: ", command, ": command not found\n");
	if (message == NULL)
		return (perror("malloc"), EXIT_FAILURE);
	ft_putstr_fd(message, STDERR_FILENO);
	free(message);
	return (RET_BAD_COMMAND);
}

int	execute_command(t_data *data)
{
	char	*full_path;

	full_path = find_absolute_path(data->path, data->commands[data->i][0]);
	if (full_path == NULL)
		return (error_not_found(data->commands[data->i][0]));
	if (!is_executable(full_path))
	{
		error_filename(full_path);
		return (RET_BAD_COMMAND);
	}
	execve(full_path, data->commands[data->i], data->env);
	error_filename(data->commands[data->i][0]);
	free(full_path);
	return (RET_EXEC_FAIL);
}
