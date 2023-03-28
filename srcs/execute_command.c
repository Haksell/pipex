/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:08:30 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/28 05:57:20 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	find_absolute_path(t_data *data, char **path, char *command)
{
	char	*full_path;
	int		i;

	if (command == NULL)
		return (true);
	if (ft_strchr(command, '/'))
	{
		data->full_path = ft_strdup(command);
		return (data->full_path != NULL);
	}
	if (command[0] == '\0' || command[0] == '.' || path == NULL)
		return (true);
	i = 0;
	while (path[i] != NULL)
	{
		full_path = ft_strjoin3(path[i], "/", command);
		if (full_path == NULL)
			return (false);
		if (access(full_path, F_OK) == 0)
			return (data->full_path = full_path, true);
		free(full_path);
		++i;
	}
	return (true);
}

static void	null_path(char *command, char **error_message,
	char **error_path, int *return_value)
{
	*error_message = "command not found";
	if (command == NULL)
		*error_path = "";
	else
		*error_path = command;
	*return_value = RET_COMMAND_NOT_FOUND;
}

static void	invalid_path(char *full_path, char **error_message,
	char **error_path, int *return_value)
{
	*error_message = strerror(errno);
	*error_path = full_path;
	if (errno == ENOTDIR || errno == EISDIR)
		*return_value = RET_CANNOT_EXECUTE;
	else
		*return_value = RET_COMMAND_NOT_FOUND;
}

void	execute_command(t_data *data)
{
	int		return_value;
	char	*error_message;
	char	*error_path;

	data->argv = ft_split(data->commands[data->i], ' ');
	if (data->argv == NULL)
		error_command(data, "ft_split");
	if (!find_absolute_path(data, data->path, data->argv[0]))
		error_command(data, "find_absolute_path");
	if (data->full_path == NULL)
		null_path(data->argv[0], &error_message, &error_path, &return_value);
	else if (access(data->full_path, F_OK) != 0)
		invalid_path(data->full_path, &error_message, &error_path,
			&return_value);
	else
	{
		free_data(data, false, true);
		execve(data->full_path, data->argv, data->env);
		error_message = strerror(errno);
		error_path = data->full_path;
		return_value = RET_CANNOT_EXECUTE;
	}
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", error_path, error_message);
	free_data(data, true, true);
	exit(return_value);
}
