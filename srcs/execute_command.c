/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:08:30 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 23:44:53 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	null_path(char **error_message, char **error_path,
	char *command, int *return_value)
{
	*error_message = "command not found";
	*error_path = command;
	*return_value = RET_COMMAND_NOT_FOUND;
}

static void	invalid_path(char **error_message, char **error_path,
		char *full_path, int *return_value)
{
	*error_message = strerror(errno);
	*error_path = (char *)full_path;
	if (errno == ENOTDIR || errno == EISDIR)
		*return_value = RET_CANNOT_EXECUTE;
	else
		*return_value = RET_COMMAND_NOT_FOUND;
}

int	execute_command(t_data *data)
{
	int		return_value;
	char	*full_path;
	char	*error_message;
	char	*error_path;
	char	**argv = data->commands[data->i];
	char	*command = argv[0];

	if (command == NULL)
		command = "";
	full_path = find_absolute_path(data->path, command);
	if (full_path == NULL)
		null_path(&error_message, &error_path, command, &return_value);
	else if (access(full_path, F_OK) != 0)
		invalid_path(&error_message, &error_path, full_path, &return_value);
	else
	{
		execve(full_path, argv, data->env);
		error_message = strerror(errno);
		error_path = (char *)full_path;
		return_value = RET_CANNOT_EXECUTE;
	}
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", error_path, error_message);
	return (return_value);
}
