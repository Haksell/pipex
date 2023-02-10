/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:49:27 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/10 06:21:35 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_pipe(t_pipe *pipe)
{
	if (pipe->fds[0] != -1)
		ft_close(&pipe->fds[0]);
	if (pipe->fds[1] != -1)
		ft_close(&pipe->fds[1]);
	pipe->is_open = false;
}

void	init_pipes(t_pipe pipes[2])
{
	pipes[0].fds[0] = -1;
	pipes[0].fds[1] = -1;
	pipes[0].is_open = false;
	pipes[1].fds[0] = -1;
	pipes[1].fds[1] = -1;
	pipes[1].is_open = false;
}

void	swap_pipes(t_pipe pipes[2])
{
	t_pipe	tmp;

	tmp = pipes[0];
	pipes[0] = pipes[1];
	pipes[1] = tmp;
}
