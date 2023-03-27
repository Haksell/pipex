/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:13 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 06:12:56 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_return_value(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else
		return (128 + WTERMSIG(wstatus));
}

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

static int	execute(t_data *data)
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

static void	pipe_exec(t_data *data)
{
	if (data->i == 0)
		data->fd_in = open(data->file_in, O_RDONLY);
	ft_close(&data->pipes[data->i][0]);
	dup2(data->pipes[data->i][1], STDOUT_FILENO);
	ft_close(&data->pipes[data->i][1]);
	dup2(data->fd_in, STDIN_FILENO);
	ft_close(&data->fd_in);
	exit(execute(data));
	ft_close(&data->pipes[data->i][1]);
	ft_close(&data->fd_in);
	data->fd_in = data->pipes[data->i][0];
}

static int	last_exec(t_data *data, pid_t pid)
{
	pid_t	wpid;
	int		return_value;
	int		wstatus;

	if (pid == 0)
	{
		if (data->is_heredoc)
			data->fd_out = open(data->file_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			data->fd_out = open(data->file_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		ft_close(&data->pipes[data->num_commands - 2][1]);
		dup2(data->pipes[data->num_commands - 2][0], STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		exit(execute(data));
	}
	ft_close(&data->fd_out);
	clean_pipes(data->pipes);
	ft_free_double((void ***)&data->path);
	if (data->is_heredoc)
		unlink(data->file_in);
	while (true)
	{
		wpid = wait(&wstatus);
		if (wpid == -1)
			break ;
		if (wpid == pid)
			return_value = get_return_value(wstatus);
	}
	return (return_value);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	pid_t	pid;

	if (!init_pipex(&data, argc, argv, env))
		return (EXIT_FAILURE);
	while (true)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), EXIT_FAILURE); // TODO free
		if (data.i == data.num_commands - 1)
			return (last_exec(&data, pid));
		if (pid == 0)
			pipe_exec(&data);
		++data.i;
	}
}
