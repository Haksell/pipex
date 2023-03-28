/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:13 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/28 04:42:39 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	error_file(t_data *data, char *filename)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", filename, strerror(errno));
	free_data(data);
	exit(EXIT_FAILURE);
}

static void	connect_pipes(t_data *data)
{
	int	fd;

	if (data->i == 0)
	{
		fd = open(data->file_in, O_RDONLY);
		if (fd == -1)
			error_file(data, data->file_in);
		dup2(fd, STDIN_FILENO);
		dup2(data->pipes[data->i][1], STDOUT_FILENO);
		close(fd);
	}
	else
		dup2(data->pipes[data->i - 1][0], STDIN_FILENO);
	if (data->i == data->num_commands - 1)
	{
		fd = open(data->file_out,
				O_CREAT | O_WRONLY | O_TRUNC << data->is_heredoc, 0644);
		if (fd == -1)
			error_file(data, data->file_out);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		dup2(data->pipes[data->i][1], STDOUT_FILENO);
}

static int	wait_commands(t_data *data)
{
	pid_t	wpid;
	int		wstatus;

	free_data(data);
	while (true)
	{
		wpid = wait(&wstatus);
		if (wpid == -1)
			break ;
		if (wpid != data->pid || data->return_value != EXIT_SUCCESS)
			continue ;
		if (WIFEXITED(wstatus))
			data->return_value = WEXITSTATUS(wstatus);
		else
			data->return_value = 128 + WTERMSIG(wstatus);
	}
	return (data->return_value);
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
		{
			data.return_value = EXIT_FAILURE;
			perror("fork");
			break ;
		}
		if (data.pid == 0)
		{
			connect_pipes(&data);
			clean_pipes(&data.pipes);
			execute_command(&data);
		}
		++data.i;
	}
	return (wait_commands(&data));
}
