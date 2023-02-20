/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:13 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/20 06:15:57 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	is_executable(char *full_path)
{
	bool	return_value;
	int		fd;

	fd = open(full_path, O_RDONLY);
	return_value = (fd != -1
			&& read(fd, NULL, 0) != -1
			&& access(full_path, X_OK) != -1);
	ft_close(&fd);
	return (return_value);
}

int	execute(t_data *data, char *cmd_name)
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
		return (error_filename(full_path));
	execve(full_path, cmd_argv, data->env);
	error_filename(cmd_argv[0]);
	ft_free_double_pointer((void ***)&cmd_argv, SIZE_MAX);
	free(full_path);
	return (RET_EXEC_FAIL);
}

void	pipe_exec(t_data *data, pid_t pid, int i)
{
	char	*cmd_name;

	if (pid == 0)
	{
		ft_close(&data->pipes[i][0]);
		dup2(data->pipes[i][1], STDOUT_FILENO);
		ft_close(&data->pipes[i][1]);
		dup2(data->fd_in, STDIN_FILENO);
		ft_close(&data->fd_in);
		cmd_name = data->argv[i + 2 + data->is_heredoc];
		exit(execute(data, cmd_name));
	}
	ft_close(&data->pipes[i][1]);
	data->fd_in = data->pipes[i][0];
}

int	last_exec(t_data *data, pid_t pid)
{
	char	*cmd_name;
	pid_t	wpid;
	int		return_value;
	int		wstatus;

	if (pid == 0)
	{
		ft_close(&data->pipes[data->num_children - 2][1]);
		dup2(data->pipes[data->num_children - 2][0], STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		cmd_name = data->argv[data->num_children + 1 + data->is_heredoc];
		exit(execute(data, cmd_name));
	}
	clean_pipes(data->pipes, data->num_children - 1);
	ft_free_double_pointer((void ***)&data->path, SIZE_MAX);
	while (true)
	{
		wpid = wait(&wstatus);
		if (wpid == -1)
			break ;
		if (wpid == pid)
			return_value = WEXITSTATUS(wstatus);
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
	while (i < data.num_children)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), EXIT_FAILURE);
		if (i == data.num_children - 1)
			return (last_exec(&data, pid));
		pipe_exec(&data, pid, i);
		++i;
	}
}
