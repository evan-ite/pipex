/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:50:59 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/29 17:59:13 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*get_options(char **envp, t_pipex *pipex)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			if (!path)
				exit_error(ERR_MEM, NULL, 5, pipex);
			break ;
		}
		i++;
	}
	if (!path)
		exit_error("Could not find PATH", NULL, 3, pipex);
	return (path);
}

static char	*create_full_path(char *path, char *cmnd, t_pipex *pipex)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin("/", cmnd);
	if (!temp)
		exit_error(ERR_MEM, NULL, 5, pipex);
	result = ft_strjoin(path, temp);
	free(temp);
	if (!result)
		exit_error(ERR_MEM, NULL, 5, pipex);
	return (result);
}

static void	find_path(char *path, char *cmnd, int i, t_pipex *pipex)
{
	int		n;
	char	**path_options;

	path_options = ft_split(path, ':');
	if (!path_options)
		exit_error(ERR_MEM, NULL, 5, pipex);
	n = 0;
	while (path_options[n])
	{
		pipex->path[i] = create_full_path(path_options[n], cmnd, pipex);
		if (access(pipex->path[i], X_OK) == 0)
			break ;
		free(pipex->path[i]);
		pipex->path[i] = NULL;
		n++;
	}
	free_array(path_options);
	return ;
}

void	get_path(int i, char **envp, t_pipex *pipex)
{
	char	*paths;

	if (ft_strchr(pipex->args[i][0], '/'))
	{
		pipex->path[i] = ft_strdup(pipex->args[i][0]);
		if (!pipex->path[i])
			exit_error(ERR_MEM, NULL, 5, pipex);
	}
	paths = get_options(envp, pipex);
	if (!pipex->path[i])
		find_path(paths, pipex->args[i][0], i, pipex);
	if (!pipex->path[i])
	{
		free(paths);
		ft_close(pipex->pipe[i + 1][0]);
		ft_close(pipex->pipe[i + 1][1]);
		exit_error(ERR_CMND, pipex->args[i][0], 2, pipex);
	}
	free(paths);
	return ;
}
