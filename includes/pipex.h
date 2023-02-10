/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:06 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/10 06:30:10 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define USAGE_MANDATORY "Usage: ./pipex infile cmd1 cmd2 outfile"
# define USAGE_BONUS_1 "Usage: ./pipex_bonus (\"here_doc\" delimiter | infile)"
# define USAGE_BONUS_2 " cmd1 ... cmdn outfile"

typedef struct s_pipe {
	int		fds[2];
	bool	is_open;
}	t_pipe;

typedef struct s_data {
	char	**env;
	char	**path;
	t_pipe	pipes[2];
}	t_data;

// path.c
char	*find_absolute_path(char **path, char *command);
char	**get_path(char **env);

// pipes.c
void	clean_pipe(t_pipe *pipe);
void	init_pipes(t_pipe pipes[2]);
void	swap_pipes(t_pipe pipes[2]);

#endif
