/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:13 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 06:11:57 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	display_path(char **path)
{
	int	i;

	if (path == NULL)
	{
		ft_printf("PATH is NULL.\n");
		return ;
	}
	i = 0;
	while (path[i] != NULL)
	{
		puts(path[i]);
		++i;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	**path;
	int		num_children;
	bool	is_heredoc;

	if (!check_args(argc, argv, &is_heredoc, &num_children))
		return (EXIT_FAILURE);
	if (is_heredoc)
		ft_printf("<HEREDOC>\n");
	path = get_path(env);
	display_path(path);
	return (EXIT_SUCCESS);
}
