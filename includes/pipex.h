/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:06 by axbrisse          #+#    #+#             */
/*   Updated: 2023/03/27 23:44:04 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define HEREDOC_PROMPT "> "
# define HEREDOC_PREFIX "/tmp/pipex_heredoc_"
# define HEREDOC_TRIES 42
# define HEREDOC_WARNING "pipex: warning: here-document delimited by \
end-of-file (wanted `%s')\n"

# define RET_CANNOT_EXECUTE 126
# define RET_COMMAND_NOT_FOUND 127

# define USAGE_MANDATORY "Usage: %s infile cmd1 cmd2 outfile\n"
# define USAGE_BONUS "Usage: %s (here_doc delimiter | infile) \
cmd1 ... cmdn outfile\n"

# define SPACES " \f\n\r\t\v"

typedef struct s_data {
	int		i;
	int		num_commands;
	int		fd_in;
	int		fd_out;
	int		**pipes;
	char	*file_in;
	char	*file_out;
	char	**env;
	char	**path;
	char	***commands;
	bool	is_heredoc;
}	t_data;

void	clean_pipes(int **pipes);
void	free_data(t_data *data);
void	error_filename(char const *filename);
int		execute_command(t_data *data);
char	*find_absolute_path(char **path, char *command);
char	*heredoc(char *eof);
bool	init_pipex(t_data *data, int argc, char **argv, char **env);
bool	is_executable(char *full_path);

#endif
