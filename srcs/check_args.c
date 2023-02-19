/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 06:11:36 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 06:46:56 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	usage(char *command, char *message)
{
	ft_putstr_fd("Usage: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (false);
}

bool	check_args(int argc, char **argv, bool *is_heredoc, int *num_children)
{
	const bool	is_bonus = ft_endswith(argv[0], "_bonus");

	*is_heredoc = (is_bonus && ft_strcmp(argv[1], "here_doc") == 0);
	*num_children = argc - 3 - *is_heredoc;
	if (is_bonus && *num_children < 2)
		return (usage(argv[0], USAGE_BONUS));
	else if (!is_bonus && *num_children != 2)
		return (usage(argv[0], USAGE_MANDATORY));
	return (true);
}
