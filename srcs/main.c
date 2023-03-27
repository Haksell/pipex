/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:13 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/28 00:04:26 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	dup_fd_in(t_data *data)
{
	if (data->fd_in != STDIN_FILENO)
	{
		dup2(data->fd_in, STDIN_FILENO);
		ft_close(&data->fd_in);
		return (true);
	}
	return (false);
}

static bool	dup_fd_out(t_data *data)
{
	if (data->fd_out != STDOUT_FILENO)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		ft_close(&data->fd_out);
		return (true);
	}
	return (false);
}

static void	file_error(char *filename)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", filename, strerror(errno));
	exit(EXIT_FAILURE);
}

static void	pipe_exec(t_data *data)
{
	if (data->i == 0)
	{
		data->fd_in = open(data->file_in, O_RDONLY);
		if (data->fd_in == -1)
			file_error(data->file_in);
		dup_fd_in(data);
	}
	else if (!dup_fd_in(data))
		dup2(data->pipes[data->i - 1][0], STDIN_FILENO);
	if (!dup_fd_out(data))
		dup2(data->pipes[data->i][1], STDOUT_FILENO);
}

static void	last_exec(t_data *data)
{
	if (data->is_heredoc)
		data->fd_out = open(data->file_out, O_CREAT | O_WRONLY | O_APPEND, 420);
	else
		data->fd_out = open(data->file_out, O_CREAT | O_WRONLY | O_TRUNC, 420);
	if (data->fd_out == -1)
		file_error(data->file_out);
	dup2(data->pipes[data->i - 1][0], STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	ft_close(&data->fd_out);
}

static int	wait_for_execution(pid_t pid)
{
	pid_t	wpid;
	int		return_value;
	int		wstatus;

	return_value = EXIT_SUCCESS;
	while (true)
	{
		wpid = wait(&wstatus);
		if (wpid == -1)
			break ;
		if (wpid != pid)
			continue ;
		if (WIFEXITED(wstatus))
			return_value = WEXITSTATUS(wstatus);
		else
			return_value = 128 + WTERMSIG(wstatus);
	}
	return (return_value);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (!init_pipex(&data, argc, argv, env))
		return (EXIT_FAILURE);
	while (data.i < data.num_commands)
	{
		data.pid = fork();
		if (data.pid == -1)
			return (perror("fork"), EXIT_FAILURE); // TODO free
		if (data.pid == 0)
		{
			if (data.i < data.num_commands - 1)
				pipe_exec(&data);
			else
				last_exec(&data);
			clean_pipes(data.pipes);
			exit(execute_command(&data));
		}
		++data.i;
	}
	free_data(&data);
	return (wait_for_execution(data.pid));
}
