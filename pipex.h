/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:10:12 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/29 18:06:25 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/getnextline.h"

# define ERR_MSG "Input error\nEx: ./pipex file1 cmd1 cmd2 file2"
# define ERR_CMND ": Command not found"
# define ERR_PIPE "Error creating pipe"
# define ERR_CHILD "Error creating child"
# define ERR_MEM "Error allocating memory"
# define ERR_EXC ": Error executing command"
# define ERR_FILE ": No such file in directory"
# define ERR_FPER ": Permission denied"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		**pipe;
	int		*pid;
	char	***args;
	char	**path;
	int		argc;
}	t_pipex;

// Handeling files
void	open_files(char **argv, t_pipex *pipex);
void	ft_close(int fd);

// Finding commands and arguments
void	get_path(int i, char **envp, t_pipex *pipex);
void	get_args(char **argv, int n, t_pipex *pipex);

// Forking processes
void	start_processes(char **argv, char **envp, t_pipex *pipex);

// Error handling
void	init_pipex(t_pipex *pipex);
int		check_empty_args(int argc, char **argv);
int		exit_error(char *err_msg, char *src, int err_code, t_pipex *pipex);
void	close_free(t_pipex *pipex);

#endif
