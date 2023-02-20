/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:01:53 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/20 06:13:44 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	check_args(t_data *data)
{
	const bool	is_bonus = ft_endswith(data->argv[0], "_bonus");

	data->is_heredoc = (is_bonus && ft_strcmp(data->argv[1], "here_doc") == 0);
	data->num_children = data->argc - 3 - data->is_heredoc;
	if (is_bonus && data->num_children < 2)
		return (error_usage(data->argv[0], USAGE_BONUS));
	else if (!is_bonus && data->num_children != 2)
		return (error_usage(data->argv[0], USAGE_MANDATORY));
	return (true);
}

static bool	init_files(t_data *data)
{
	const char	*file_in = data->argv[1 + data->is_heredoc];
	const char	*file_out = data->argv[data->argc - 1];

	data->fd_in = open(file_in, O_RDONLY);
	if (data->fd_in == -1)
		return (error_filename(file_in), false);
	data->fd_out = open(file_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd_out == -1)
		return (close(data->fd_in), error_filename(file_out), false);
	return (true);
}

static int	**init_pipes(int num_pipes)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * num_pipes);
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
	if (!check_args(data) || !init_files(data))
		return (false);
	data->pipes = init_pipes(data->num_children - 1);
	if (data->pipes == NULL)
		return (false);
	data->path = get_path(env);
	return (true);
}
