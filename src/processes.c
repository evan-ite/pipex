/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:22:50 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/29 17:59:31 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	execute(int i, t_pipex *pipex, char **envp)
{
	if (i == 0)
		dup2(pipex->infile, STDIN_FILENO);
	else
	{
		dup2(pipex->pipe[i][0], STDIN_FILENO);
		ft_close(pipex->pipe[i][1]);
	}
	if (i == pipex->argc - 4)
		dup2(pipex->outfile, STDOUT_FILENO);
	else
	{
		dup2(pipex->pipe[i + 1][1], STDOUT_FILENO);
		ft_close(pipex->pipe[i + 1][0]);
	}
	if (execve(pipex->path[i], pipex->args[i], envp) == -1)
		exit_error(ERR_EXC, pipex->args[i][0], 2, pipex);
	return (EXIT_SUCCESS);
}

static void	child_process(int i, char **envp, t_pipex *pipex)
{
	if (pipe(pipex->pipe[i + 1]) == -1)
		exit_error(ERR_PIPE, NULL, 3, pipex);
	pipex->pid[i] = fork();
	if (pipex->pid[i] < 0)
		exit_error(ERR_CHILD, NULL, 4, pipex);
	else if (pipex->pid[i] == 0)
	{
		get_path(i, envp, pipex);
		if (execute(i, pipex, envp) != 0)
			exit_error(ERR_EXC, pipex->args[i][0], 2, pipex);
	}
	else
	{
		if (i > 0)
		{
			ft_close(pipex->pipe[i][0]);
			ft_close(pipex->pipe[i][1]);
		}
	}
}

void	start_processes(char **argv, char **envp, t_pipex *pipex)
{
	int	status;
	int	i;

	status = -1;
	i = 0;
	while (i < pipex->argc - 3)
	{
		get_args(argv, i, pipex);
		child_process(i, envp, pipex);
		i++;
	}
	while (i < pipex->argc - 3)
		waitpid(pipex->pid[i++], &status, 0);
	if (status != 0)
	{
		close_free(pipex);
		exit(WEXITSTATUS(status));
	}
}
