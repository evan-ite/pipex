/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:39 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/29 17:59:39 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	open_files(char **argv, t_pipex *pipex)
{
	if (access(argv[1], F_OK) != 0)
		exit_error(ERR_FILE, argv[1], 2, pipex);
	if (access(argv[1], R_OK) != 0)
		exit_error(ERR_FPER, argv[1], 2, pipex);
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		exit_error(ERR_FILE, argv[1], 2, pipex);
	if (access(argv[pipex->argc - 1], F_OK) == 0)
	{
		if (access(argv[pipex->argc - 1], W_OK) != 0)
			exit_error(ERR_FPER, argv[pipex->argc - 1], 2, pipex);
	}
	pipex->outfile = open(argv[pipex->argc - 1], \
						O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (pipex->outfile < 0)
		exit_error(ERR_FILE, argv[pipex->argc - 1], 2, pipex);
}

int	check_empty_args(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!argv[i] || argv[i][0] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	get_args(char **argv, int i, t_pipex *pipex)
{
	pipex->args[i] = ft_split(argv[i + 2], ' ');
	if (!pipex->args[i])
		exit_error(ERR_MEM, NULL, 5, pipex);
	return ;
}
