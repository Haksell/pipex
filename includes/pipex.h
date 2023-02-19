/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:41:06 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/19 09:26:20 by axbrisse         ###   ########.fr       */
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

# define RET_NOT_FOUND 127
# define USAGE_MANDATORY "infile cmd1 cmd2 outfile"
# define USAGE_BONUS "(here_doc delimiter | infile) cmd1 ... cmdn outfile"

bool	check_args(int argc, char **argv, bool *is_heredoc, int *num_children);
void	clean_pipes(int **pipes, int num_pipes);
bool	error_filename(char *filename);
int		error_not_found(char *command);
bool	error_usage(char *command, char *message);
char	*find_absolute_path(char **path, char *command);
char	**get_path(char **env);
bool	init_files(char *file_in, int *fd_in, char *file_out, int *fd_out);
int		**init_pipes(int num_pipes);


#endif
