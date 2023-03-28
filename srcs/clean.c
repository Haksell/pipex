/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 05:55:11 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/28 04:43:25 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_pipes(int ***ptr)
{
	int	i;
	int	**pipes;

	pipes = *ptr;
	if (pipes != NULL)
	{
		i = 0;
		while (pipes[i] != NULL)
		{
			ft_close(&pipes[i][0]);
			ft_close(&pipes[i][1]);
			ft_free((void **)pipes + i);
			pipes[i] = NULL;
			++i;
		}
		ft_free((void **)ptr);
	}
}

void	free_data(t_data *data)
{
	clean_pipes(&data->pipes);
	free(data->full_path);
	ft_free_double((void ***)&data->argv);
	ft_free_double((void ***)&data->path);
	if (data->is_heredoc)
	{
		unlink(data->file_in);
		free(data->file_in);
	}
}
