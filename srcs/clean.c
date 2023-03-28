/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 05:55:11 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/28 05:48:23 by axbrisse         ###   ########.fr       */
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

void	free_data(t_data *data, bool free_exec, bool free_file_in)
{
	clean_pipes(&data->pipes);
	ft_free_double((void ***)&data->path);
	if (free_exec)
	{
		ft_free((void **)&data->full_path);
		ft_free_double((void ***)&data->argv);
	}
	if (free_file_in && data->is_heredoc)
		ft_free((void **)&data->file_in);
}
