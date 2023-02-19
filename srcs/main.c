/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:13 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 08:46:31 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	perror_custom(char *s1, char *s2, char *s3, int return_value)
{
	char	*message;
	char	*full_error;

	if (s3 != NULL)
		message = ft_strjoin3(s1, s2, s3);
	else if (s2 != NULL)
		message = ft_strjoin(s1, s2);
	else
		message = ft_strdup(s1);
	if (message == NULL)
		return (perror("malloc"), EXIT_FAILURE);
	full_error = ft_strjoin3("pipex: ", message, "\n");
	if (full_error == NULL)
		return (perror("malloc"), free(message), EXIT_FAILURE);
	ft_putstr_fd(full_error, STDERR_FILENO);
	free(message);
	free(full_error);
	return (return_value);
}

// int	pipe_exec()
// {

// }

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
		else if (pid == 0)
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
				return (perror_custom(cmd_argv[0], ": ", "command not found",
						RET_NOT_FOUND));
			execve(full_path, cmd_argv, env);
			return (perror("execve"), EXIT_FAILURE);
		}
		if (i < num_children - 1)
		{
			ft_close(&pipes[i][1]);
			fd_in = pipes[i][0];
		}
		else
		{
			clean_pipes(pipes, num_children - 1);
			ft_free_double_pointer((void ***)&path, SIZE_MAX);
			while (waitpid(-1, NULL, 0) != -1)
				;
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
