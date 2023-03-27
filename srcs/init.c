/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:01:53 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 05:13:13 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	check_args(t_data *data, int argc, char **argv)
{
	const bool	is_bonus = ft_endswith(argv[0], "_bonus");

	data->is_heredoc = (is_bonus && argc >= 2
			&& ft_strcmp(argv[1], "here_doc") == 0);
	data->num_children = argc - 3 - data->is_heredoc;
	if (is_bonus)
	{
		if (data->num_children < 2)
		{
			ft_dprintf(STDERR_FILENO, USAGE_BONUS, argv[0]);
			return (false);
		}
		return (true);
	}
	else
	{
		if (data->num_children != 2)
		{
			ft_dprintf(STDERR_FILENO, USAGE_MANDATORY, argv[0]);
			return (false);
		}
		return (true);
	}
}

static int	**init_pipes(int num_pipes)
{
	int	**pipes;
	int	i;

	pipes = ft_calloc(num_pipes + 1, sizeof(int *));
	if (pipes == NULL)
		return (perror("malloc"), NULL);
	pipes[num_pipes] = NULL;
	i = 0;
	while (i < num_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
			return (clean_pipes(pipes), perror("malloc"), NULL);
		if (pipe(pipes[i]) == -1)
			return (clean_pipes(pipes), perror("pipe"), NULL);
		++i;
	}
	return (pipes);
}

bool	init_pipex(t_data *data, int argc, char **argv, char **env)
{
	if (!check_args(data, argc, argv))
		return (false);
	data->argv = argv + 2 + data->is_heredoc;
	data->env = env;
	if (data->is_heredoc)
	{
		data->file_in = heredoc(argv[2]);
		if (data->file_in == NULL)
			return (NULL);
	}
	else
		data->file_in = argv[2];
	data->file_out = argv[argc - 1];
	data->pipes = init_pipes(data->num_children - 1);
	if (data->pipes == NULL)
		return (false);
	data->path = get_path(env);
	return (true);
}
