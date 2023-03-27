/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:01:53 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 03:17:01 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	check_args(t_data *data)
{
	const bool	is_bonus = ft_endswith(data->argv[0], "_bonus");

	data->is_heredoc = (is_bonus && data->argc >= 2
			&& ft_strcmp(data->argv[1], "here_doc") == 0);
	data->num_children = data->argc - 3 - data->is_heredoc;
	if (is_bonus)
	{
		if (data->num_children < 2)
		{
			ft_dprintf(STDERR_FILENO, USAGE_BONUS, data->argv[0]);
			return (false);
		}
		return (true);
	}
	else
	{
		if (data->num_children != 2)
		{
			ft_dprintf(STDERR_FILENO, USAGE_MANDATORY, data->argv[0]);
			return (false);
		}
		return (true);
	}
}

static void	init_heredoc(t_data *data)
{
	const int		fd_write = open(HEREDOC_FILE,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	const char		*limiter = data->argv[2];
	const size_t	n = ft_strlen(limiter);
	char			*line;

	if (fd_write == -1)
		return (perror("open"));
	while (true)
	{
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL
			|| !ft_strchr(line, '\n')
			|| (ft_strncmp(line, limiter, n) == 0 && line[n] == '\n'))
			break ;
		ft_putstr_fd(line, fd_write);
		ft_free((void **)&line);
	}
	ft_free((void **)&line);
	close(fd_write);
	data->fd_in = open(HEREDOC_FILE, O_RDONLY);
	if (data->fd_in == -1)
		perror("open");
}

static void	init_files(t_data *data)
{
	char		*file_in;
	const char	*file_out = data->argv[data->argc - 1];

	if (data->is_heredoc)
		init_heredoc(data);
	else
	{
		file_in = data->argv[1 + data->is_heredoc];
		data->fd_in = open(file_in, O_RDONLY);
		if (data->fd_in == -1)
			error_filename(file_in);
	}
	if (data->is_heredoc)
		data->fd_out = open(file_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		data->fd_out = open(file_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd_out == -1)
		error_filename(file_out);
}

static int	**init_pipes(int num_pipes)
{
	int	**pipes;
	int	i;

	pipes = ft_calloc(num_pipes + 1, sizeof(int *));
	if (pipes == NULL)
		return (perror("malloc"), NULL);
	i = 0;
	while (i < num_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
			return (clean_pipes(pipes, i), perror("malloc"), NULL);
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		if (pipe(pipes[i]) == -1)
			return (clean_pipes(pipes, i + 1), perror("pipe"), NULL);
		++i;
	}
	return (pipes);
}

bool	init_pipex(t_data *data, int argc, char **argv, char **env)
{
	data->argc = argc;
	data->argv = argv;
	data->env = env;
	if (!check_args(data))
		return (false);
	init_files(data);
	data->pipes = init_pipes(data->num_children - 1);
	if (data->pipes == NULL)
		return (false);
	data->path = get_path(env);
	return (true);
}
