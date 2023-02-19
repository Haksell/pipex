/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 05:55:11 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 06:12:48 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_absolute_path(char **path, char *command)
{
	char	*full_path;
	int		i;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i] != NULL)
	{
		full_path = ft_strjoin3(path[i], "/", command);
		if (full_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		++i;
	}
	return (NULL);
}

char	**get_path(char **env)
{
	int	i;

	if (env == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_startswith(env[i], "PATH="))
			return (ft_split(env[i] + 5, ':'));
		++i;
	}
	return (NULL);
}
