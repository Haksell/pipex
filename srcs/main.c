/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:13 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/10 06:34:07 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	panic(char *error, t_data *data, char **cmd_argv)
{
	perror(error);
	ft_free_double_pointer((void ***)&cmd_argv, SIZE_MAX);
	ft_free_double_pointer((void ***)&data->path, SIZE_MAX);
	clean_pipe(&data->pipes[0]);
	clean_pipe(&data->pipes[1]);
	exit(EXIT_FAILURE);
}

static void	execute(t_data *data, char **cmd_argv)
{
	const pid_t	pid = fork();
	char		*command;
	char		*error;

	if (pid < 0)
		panic("fork", data, cmd_argv);
	if (pid > 0)
		return ;
	command = find_absolute_path(data->path, cmd_argv[0]);
	if (command == NULL)
	{
		error = ft_strjoin3("pipex: ", cmd_argv[0], ": command not found");
		ft_putendl_fd(error, STDERR_FILENO);
		free(error);
		return ;
	}
	if (data->pipes[0].is_open)
	{
		close(data->pipes[0].fds[1]);
		dup2(data->pipes[0].fds[0], STDIN_FILENO);
	}
	if (data->pipes[1].is_open)
		dup2(data->pipes[1].fds[1], STDOUT_FILENO);
	execve(command, cmd_argv, data->env);
	panic("execve", data, cmd_argv);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;
	char	**cmd_argv;

	data.env = env;
	data.path = get_path(env);
	init_pipes(data.pipes);
	i = 1;
	while (i < argc)
	{
		swap_pipes(data.pipes);
		if (i != argc - 1)
		{
			pipe(data.pipes[1].fds);
			data.pipes[1].is_open = true;
		}
		cmd_argv = ft_split(argv[i], ' ');
		execute(&data, cmd_argv);
		ft_free_double_pointer((void ***)&cmd_argv, SIZE_MAX);
		if (i != 1)
			clean_pipe(&data.pipes[0]);
		++i;
	}
	clean_pipe(&data.pipes[0]);
	clean_pipe(&data.pipes[1]);
	while (wait(NULL) != -1)
		;
	return (EXIT_SUCCESS);
}
