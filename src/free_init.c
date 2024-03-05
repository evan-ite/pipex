/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:33:59 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/29 17:59:16 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_close(int fd)
{
	close(fd);
	fd = -1;
}

static void	free_doubles(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->argc)
	{
		if (pipex->pipe)
		{
			if (pipex->pipe[i] && pipex->pipe[i][0] >= 0)
				ft_close(pipex->pipe[i][0]);
			if (pipex->pipe[i] && pipex->pipe[i][1] >= 0)
				ft_close(pipex->pipe[i][1]);
			if (pipex->pipe[i])
				free(pipex->pipe[i]);
		}
		if (pipex->path[i])
			free(pipex->path[i]);
		if (pipex->args[i])
			free_array(pipex->args[i]);
		i++;
	}
}

void	close_free(t_pipex *pipex)
{
	if (pipex->infile >= 0)
		ft_close(pipex->infile);
	if (pipex->outfile >= 0)
		ft_close(pipex->outfile);
	free_doubles(pipex);
	if (pipex->args)
		free(pipex->args);
	if (pipex->path)
		free(pipex->path);
	if (pipex->pipe)
		free(pipex->pipe);
	if (pipex->pid)
		free(pipex->pid);
}

void	init_pipex(t_pipex *pipex)
{
	int	i;

	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->args = (char ***)gnl_calloc(pipex->argc, sizeof(char **));
	pipex->path = (char **)gnl_calloc(pipex->argc, sizeof(char *));
	pipex->pipe = (int **)gnl_calloc(pipex->argc, sizeof(int *));
	pipex->pid = (int *)gnl_calloc(pipex->argc, sizeof(int));
	if (!pipex->path || !pipex->args || !pipex->pipe || !pipex->pid)
		exit_error(ERR_MEM, NULL, 5, pipex);
	i = 0;
	while (i <= pipex->argc - 3)
	{
		pipex->pipe[i] = (int *)gnl_calloc(2, sizeof(int));
		if (!pipex->pipe[i])
			exit_error(ERR_MEM, NULL, 5, pipex);
		pipex->pipe[i][0] = -1;
		pipex->pipe[i][1] = -1;
		i++;
	}
}
