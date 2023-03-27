/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:13 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 05:18:15 by axbrisse         ###   ########.fr       */
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

static int	execute(t_data *data, char *cmd_name)
{
	char	**cmd_argv;
	char	*full_path;

	cmd_argv = ft_split(cmd_name, ' ');
	if (cmd_argv == NULL)
		return (perror("malloc"), EXIT_FAILURE);
	full_path = find_absolute_path(data->path, cmd_argv[0]);
	if (full_path == NULL)
		return (error_not_found(cmd_argv[0]));
	if (!is_executable(full_path))
	{
		error_filename(full_path);
		return (RET_BAD_COMMAND);
	}
	execve(full_path, cmd_argv, data->env);
	error_filename(cmd_argv[0]);
	ft_free_double_pointer((void ***)&cmd_argv, SIZE_MAX);
	free(full_path);
	return (RET_EXEC_FAIL);
}

static void	pipe_exec(t_data *data, pid_t pid, int i)
{
	char	*cmd_name;

	if (pid == 0)
	{
		if (i == 0)
			data->fd_in = open(data->file_in, O_RDONLY);
		ft_close(&data->pipes[i][0]);
		dup2(data->pipes[i][1], STDOUT_FILENO);
		ft_close(&data->pipes[i][1]);
		dup2(data->fd_in, STDIN_FILENO);
		ft_close(&data->fd_in);
		cmd_name = data->commands[i];
		exit(execute(data, cmd_name));
	}
	ft_close(&data->pipes[i][1]);
	ft_close(&data->fd_in);
	data->fd_in = data->pipes[i][0];
}

static int	last_exec(t_data *data, pid_t pid)
{
	char	*cmd_name;
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
		cmd_name = data->commands[data->num_commands - 1];
		exit(execute(data, cmd_name));
	}
	ft_close(&data->fd_out);
	clean_pipes(data->pipes);
	ft_free_double_pointer((void ***)&data->path, SIZE_MAX);
	if (data->is_heredoc)
	  	unlink(HEREDOC_FILE);
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
	int		i;

	if (!init_pipex(&data, argc, argv, env))
		return (EXIT_FAILURE);
	i = 0;
	while (i < data.num_commands)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), EXIT_FAILURE); // TODO free
		if (i == data.num_commands - 1)
			return (last_exec(&data, pid));
		pipe_exec(&data, pid, i);
		++i;
	}
}
