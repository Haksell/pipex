/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:13 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/28 01:17:15 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	file_error(char *filename)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", filename, strerror(errno));
	exit(EXIT_FAILURE);
}

static void	connect_pipes(t_data *data)
{
	if (data->i == 0)
	{
		data->fd_in = open(data->file_in, O_RDONLY);
		if (data->fd_in == -1)
			file_error(data->file_in);
		dup2(data->fd_in, STDIN_FILENO);
		dup2(data->pipes[data->i][1], STDOUT_FILENO);
		ft_close(&data->fd_in);
	}
	else
		dup2(data->pipes[data->i - 1][0], STDIN_FILENO);
	if (data->i == data->num_commands - 1)
	{
		data->fd_out = open(data->file_out,
				O_CREAT | O_WRONLY | O_TRUNC << data->is_heredoc, 0644);
		if (data->fd_out == -1)
			file_error(data->file_out);
		dup2(data->fd_out, STDOUT_FILENO);
		ft_close(&data->fd_out);
	}
	else
		dup2(data->pipes[data->i][1], STDOUT_FILENO);
}

static int	wait_for_execution(pid_t pid)
{
	pid_t	wpid;
	int		return_value;
	int		wstatus;

	return_value = EXIT_FAILURE;
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
			return (perror("fork"), EXIT_FAILURE); // break and still wait
		if (data.pid == 0)
		{
			connect_pipes(&data);
			clean_pipes(data.pipes);
			exit(execute_command(&data));
		}
		++data.i;
	}
	free_data(&data);
	return (wait_for_execution(data.pid));
}
