/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:08:30 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/28 00:53:45 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_absolute_path(char **path, char *command)
{
	char	*full_path;
	int		i;

	if (command == NULL)
		return (NULL);
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
			exit(EXIT_FAILURE); // TODO free
		}
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		++i;
	}
	return (NULL);
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

int	execute_command(t_data *data)
{
	int		return_value;
	char	*full_path;
	char	*error_message;
	char	*error_path;
	char	**argv;

	argv = ft_split(data->argv[data->i + 2 + data->is_heredoc], ' ');
	if (argv == NULL)
		return (perror("ft_split"), EXIT_FAILURE);
	full_path = find_absolute_path(data->path, argv[0]);
	if (full_path == NULL)
		null_path(argv[0], &error_message, &error_path, &return_value);
	else if (access(full_path, F_OK) != 0)
		invalid_path(full_path, &error_message, &error_path, &return_value);
	else
	{
		execve(full_path, argv, data->env);
		error_message = strerror(errno);
		error_path = full_path;
		return_value = RET_CANNOT_EXECUTE;
	}
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", error_path, error_message);
	free(full_path);
	ft_free_double((void ***)&argv);
	return (return_value);
}
