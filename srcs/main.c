/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:13 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 12:43:30 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute(char *cmd_name, char **env, char **path)
{
	char	**cmd_argv;
	char	*full_path;

	cmd_argv = ft_split(cmd_name, ' ');
	if (cmd_argv == NULL)
		return (perror("malloc"), EXIT_FAILURE);
	full_path = find_absolute_path(path, cmd_argv[0]);
	if (full_path == NULL)
		return (error_not_found(cmd_argv[0]));
	execve(full_path, cmd_argv, env);
	error_filename(cmd_argv[0]);
	ft_free_double_pointer((void ***)&cmd_argv, SIZE_MAX);
	free(full_path);
	return (EXIT_FAILURE);
}

void	pipe_exec(t_data *data, pid_t pid, int i)
{
	if (pid == 0)
	{
		ft_close(&data->pipes[i][0]);
		dup2(data->pipes[i][1], STDOUT_FILENO);
		ft_close(&data->pipes[i][1]);
		dup2(data->fd_in, STDIN_FILENO);
		ft_close(&data->fd_in);
		exit(execute(data->argv[i + 2 + data->is_heredoc], data->env, data->path));
	}
	ft_close(&data->pipes[i][1]);
	data->fd_in = data->pipes[i][0];
}

int	last_exec(t_data *data, pid_t pid)
{
	pid_t	wpid;
	int		return_value;
	int		wstatus;

	if (pid == 0)
	{
		ft_close(&data->pipes[data->num_children - 2][1]);
		dup2(data->pipes[data->num_children - 2][0], STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		exit(execute(data->argv[data->num_children + 1 + data->is_heredoc], data->env, data->path));
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

bool	init_pipex(t_data *data, int argc, char **argv, char **env)
{
	data->argc = argc;
	data->argv = argv;
	data->env = env;
	if (!check_args(argc, argv, &data->is_heredoc, &data->num_children))
		return (false);
	if (!init_files(argv[1 + data->is_heredoc], &data->fd_in, argv[argc - 1], &data->fd_out))
		return (false);
	data->pipes = init_pipes(data->num_children - 1);
	if (data->pipes == NULL)
		return (false);
	data->path = get_path(env);
	return (true);
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
