/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:13 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 23:26:13 by axbrisse         ###   ########.fr       */
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

bool	dup_fd_in(t_data *data)
{
	if (data->fd_in != STDIN_FILENO)
	{
		dup2(data->fd_in, STDIN_FILENO);
		ft_close(&data->fd_in);
		return (true);
	}
	return (false);
}

bool	dup_fd_out(t_data *data)
{
	if (data->fd_out != STDOUT_FILENO)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		ft_close(&data->fd_out);
		return (true);
	}
	return (false);
}

static void	pipe_exec(t_data *data)
{
	if (data->i == 0)
	{
		data->fd_in = open(data->file_in, O_RDONLY);
		dup_fd_in(data);
	}
	else if (!dup_fd_in(data))
		dup2(data->pipes[data->i - 1][0], STDIN_FILENO);
	if (!dup_fd_out(data))
		dup2(data->pipes[data->i][1], STDOUT_FILENO);
	clean_pipes(data->pipes);
	exit(execute_command(data));
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
		if (wpid == pid)
			return_value = get_return_value(wstatus);
	}
	return (return_value);
}

static void	free_data(t_data *data)
{
	close(data->fd_in);
	close(data->fd_out);
	clean_pipes(data->pipes);
	if (data->is_heredoc)
		free(data->file_in);
	// ft_free_double((void ***)data->path);
	// ft_free_triple((void ****)data->commands);
}

static void	last_exec(t_data *data)
{
	if (data->is_heredoc)
		data->fd_out = open(data->file_out, O_CREAT | O_WRONLY | O_APPEND, 420);
	else
		data->fd_out = open(data->file_out, O_CREAT | O_WRONLY | O_TRUNC, 420);
	if (!dup_fd_in(data))
		dup2(data->pipes[data->i - 1][0], STDIN_FILENO);
	dup_fd_out(data);
	clean_pipes(data->pipes);
	exit(execute_command(data));
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	pid_t	pid;

	if (!init_pipex(&data, argc, argv, env))
		return (EXIT_FAILURE);
	while (data.i < data.num_commands)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), EXIT_FAILURE); // TODO free
		if (pid == 0)
		{
			if (data.i < data.num_commands - 1)
				pipe_exec(&data);
			else
				last_exec(&data);
		}
		++data.i;
	}
	free_data(&data);
	return (wait_for_execution(pid));
}
