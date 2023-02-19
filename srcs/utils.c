/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 06:11:36 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 12:46:48 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	check_args(int argc, char **argv, bool *is_heredoc, int *num_children)
{
	const bool	is_bonus = ft_endswith(argv[0], "_bonus");

	*is_heredoc = (is_bonus && ft_strcmp(argv[1], "here_doc") == 0);
	*num_children = argc - 3 - *is_heredoc;
	if (is_bonus && *num_children < 2)
		return (error_usage(argv[0], USAGE_BONUS));
	else if (!is_bonus && *num_children != 2)
		return (error_usage(argv[0], USAGE_MANDATORY));
	return (true);
}

bool	init_files(char const *file_in, int *fd_in, char const *file_out, int *fd_out)
{
	*fd_in = open(file_in, O_RDONLY);
	if (*fd_in == -1)
		return (error_filename(file_in));
	*fd_out = open(file_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd_out == -1)
		return (close(*fd_in), error_filename(file_out));
	return (true);
}
