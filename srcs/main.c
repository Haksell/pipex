/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:13 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 09:34:56 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipe_exec(pid_t pid, int **pipes, int i, int *fd_in, char **argv, bool is_heredoc, char **path, char **env)
{
	char	**cmd_argv;
	char	*full_path;

	if (pid == 0)
	{
		ft_close(&pipes[i][0]);
		dup2(pipes[i][1], STDOUT_FILENO);
		ft_close(&pipes[i][1]);
		dup2(*fd_in, STDIN_FILENO);
		ft_close(fd_in);
		cmd_argv = ft_split(argv[i + 2 + is_heredoc], ' ');
		if (cmd_argv == NULL)
			return (perror("malloc"), EXIT_FAILURE);
		full_path = find_absolute_path(path, cmd_argv[0]);
		if (full_path == NULL)
			return (error_not_found(cmd_argv[0]));
		execve(full_path, cmd_argv, env);
		return (perror("execve"), free(full_path), EXIT_FAILURE);
	}
	else
	{
		ft_close(&pipes[i][1]);
		*fd_in = pipes[i][0];
	}
	return (EXIT_SUCCESS);
}

// int	last_exec()
// {

// }

int	main(int argc, char **argv, char **env)
{
	char	**path;
	int		num_children;
	bool	is_heredoc;
	int		**pipes;
	int		i;
	pid_t	pid;
	char	**cmd_argv;
	char	*full_path;
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
		if (i < num_children - 1)
			pipe_exec(pid, pipes, i, &fd_in, argv, is_heredoc, path, env);
		else
		{
			if (pid == 0)
			{
				if (i < num_children - 1)
				{
					ft_close(&pipes[i][0]);
					dup2(pipes[i][1], STDOUT_FILENO);
					ft_close(&pipes[i][1]);
					dup2(fd_in, STDIN_FILENO);
					ft_close(&fd_in);
				}
				else
				{
					ft_close(&pipes[i - 1][1]);
					dup2(pipes[i - 1][0], STDIN_FILENO);
					dup2(fd_out, STDOUT_FILENO);
				}
				cmd_argv = ft_split(argv[i + 2 + is_heredoc], ' ');
				if (cmd_argv == NULL)
					return (perror("malloc"), EXIT_FAILURE);
				full_path = find_absolute_path(path, cmd_argv[0]);
				if (full_path == NULL)
					return (error_not_found(cmd_argv[0]));
				execve(full_path, cmd_argv, env);
				return (perror("execve"), free(full_path), EXIT_FAILURE);
			}
			else
			{
				clean_pipes(pipes, num_children - 1);
				ft_free_double_pointer((void ***)&path, SIZE_MAX);
				while (waitpid(-1, NULL, 0) != -1)
					;
			}
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
