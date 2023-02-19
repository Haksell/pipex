/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 07:27:00 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 07:27:16 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		ft_close(&pipes[i][0]);
		ft_close(&pipes[i][1]);
		ft_free((void **)&pipes[i]);
		++i;
	}
	ft_free_double_pointer((void ***)&pipes, num_pipes);
}

int	**init_pipes(int num_pipes)
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
