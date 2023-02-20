/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:06 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/20 08:00:44 by axbrisse         ###   ########.fr       */
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

# define RET_BAD_COMMAND 127
# define RET_EXEC_FAIL 126

# define USAGE_MANDATORY "infile cmd1 cmd2 outfile"
# define USAGE_BONUS "(here_doc delimiter | infile) cmd1 ... cmdn outfile"

# define HEREDOC_FILE "/tmp/heredoc.tmp"

typedef struct s_data {
	int		argc;
	char	**argv;
	char	**env;
	char	**path;
	int		**pipes;
	int		fd_in;
	int		fd_out;
	int		num_children;
	bool	is_heredoc;
	char	*limiter;
}	t_data;

void	clean_pipes(int **pipes, int num_pipes);
int		error_filename(char const *filename);
int		error_not_found(char *command);
bool	error_usage(char *command, char *message);
char	*find_absolute_path(char **path, char *command);
char	**get_path(char **env);
bool	init_pipex(t_data *data, int argc, char **argv, char **env);
bool	is_executable(char *full_path);

#endif
