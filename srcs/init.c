/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:01:53 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 22:22:42 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	check_args(t_data *data, int argc, char **argv)
{
	const bool	is_bonus = ft_endswith(argv[0], "_bonus");

	data->is_heredoc = (is_bonus && argc >= 2
			&& ft_strcmp(argv[1], "here_doc") == 0);
	data->num_commands = argc - 3 - data->is_heredoc;
	if (is_bonus)
	{
		if (data->num_commands < 2)
		{
			ft_dprintf(STDERR_FILENO, USAGE_BONUS, argv[0]);
			return (false);
		}
	}
	else
	{
		if (data->num_commands != 2)
		{
			ft_dprintf(STDERR_FILENO, USAGE_MANDATORY, argv[0]);
			return (false);
		}
	}
	return (true);
}

static bool	init_pipes(t_data *data)
{
	int	i;

	data->pipes = ft_calloc(data->num_commands, sizeof(int *));
	if (data->pipes == NULL)
		return (perror("malloc"), false);
	i = 0;
	while (i < data->num_commands - 1)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if (data->pipes[i] == NULL)
			return (clean_pipes(data->pipes), perror("malloc"), false);
		if (pipe(data->pipes[i]) == -1)
			return (clean_pipes(data->pipes), perror("pipe"), false);
		++i;
	}
	return (true);
}

static bool	init_commands(t_data *data, char **argv)
{
	int	i;

	data->commands = ft_calloc(data->num_commands + 1, sizeof(char **));
	if (data->commands == NULL)
	{
		perror("malloc");
		return (false);
	}
	i = 0;
	while (i < data->num_commands)
	{
		data->commands[i] = ft_split(argv[i], ' ');
		if (data->commands[i] == NULL)
		{
			ft_free_triple((void ****)&data->commands);
			return (false);
		}
		++i;
	}
	return (true);
}

static bool	init_path(t_data *data)
{
	int	i;

	if (data->env == NULL)
		return (NULL);
	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_startswith(data->env[i], "PATH="))
		{
			data->path = ft_split(data->env[i] + 5, ':');
			return (data->path != NULL);
		}
		++i;
	}
	return (true);
}

bool	init_pipex(t_data *data, int argc, char **argv, char **env)
{
	ft_bzero(data, sizeof(t_data));
	data->env = env;
	if (!check_args(data, argc, argv)
		|| !init_path(data)
		|| !init_commands(data, argv + 2 + data->is_heredoc)
		|| !init_pipes(data))
		return (false);
	if (data->is_heredoc)
	{
		data->file_in = heredoc(argv[2]);
		if (data->file_in == NULL)
			return (NULL);
	}
	else
		data->file_in = argv[2];
	data->file_out = argv[argc - 1];
	data->fd_in = STDIN_FILENO;
	data->fd_out = STDOUT_FILENO;
	return (true);
}
