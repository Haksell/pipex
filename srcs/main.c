/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:13 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 12:30:43 by axbrisse         ###   ########.fr       */
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

void	pipe_exec(pid_t pid, int **pipes, int *fd_in, char **argv, bool is_heredoc, char **env, char **path, int i)
{
	if (pid == 0)
	{
		ft_close(&pipes[i][0]);
		dup2(pipes[i][1], STDOUT_FILENO);
		ft_close(&pipes[i][1]);
		dup2(*fd_in, STDIN_FILENO);
		ft_close(fd_in);
		exit(execute(argv[i + 2 + is_heredoc], env, path));
	}
	ft_close(&pipes[i][1]);
	*fd_in = pipes[i][0];
}

int	last_exec(pid_t pid, int **pipes, int fd_out, char **argv, bool is_heredoc, char **env, char **path, int num_children)
{
	pid_t	wpid;
	int		return_value;
	int		wstatus;

	if (pid == 0)
	{
		ft_close(&pipes[num_children - 2][1]);
		dup2(pipes[num_children - 2][0], STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		exit(execute(argv[num_children + 1 + is_heredoc], env, path));
	}
	clean_pipes(pipes, num_children - 1);
	ft_free_double_pointer((void ***)&path, SIZE_MAX);
	while (true)
	{
		wpid = waitpid(-1, &wstatus, 0); // TODO wait
		if (wpid == -1)
			break ;
		if (wpid == pid)
			return_value = WEXITSTATUS(wstatus);
	}
	return (return_value);
}

int	main(int argc, char **argv, char **env)
{
	char	**path;
	int		num_children;
	bool	is_heredoc;
	int		**pipes;
	int		i;
	pid_t	pid;
	int		fd_in;
	int		fd_out;

	if (!check_args(argc, argv, &is_heredoc, &num_children))
		return (EXIT_FAILURE);
	if (!init_files(argv[1 + is_heredoc], &fd_in, argv[argc - 1], &fd_out))
		return (EXIT_FAILURE);
	pipes = init_pipes(num_children - 1);
	if (pipes == NULL)
		return (EXIT_FAILURE);
	path = get_path(env);
	i = 0;
	while (i < num_children)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), EXIT_FAILURE);
		if (i == num_children - 1)
			return (last_exec(pid, pipes, fd_out, argv, is_heredoc, env, path, num_children));
		pipe_exec(pid, pipes, &fd_in, argv, is_heredoc, env, path, i);
		++i;
	}
}
