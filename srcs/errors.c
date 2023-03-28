/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 05:57:16 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/28 05:57:45 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_command(t_data *data, char *error_message)
{
	perror(error_message);
	free_data(data, true, true);
	exit(EXIT_FAILURE);
}

void	error_file(t_data *data, char *filename)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", filename, strerror(errno));
	free_data(data, true, true);
	exit(EXIT_FAILURE);
}
