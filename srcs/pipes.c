/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 07:27:00 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/20 06:16:28 by axbrisse         ###   ########.fr       */
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
