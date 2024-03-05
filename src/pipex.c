/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:43:21 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/29 17:46:59 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.argc = argc;
	init_pipex(&pipex);
	if (argc != 5)
		exit_error(ERR_MSG, NULL, 1, &pipex);
	if (check_empty_args(argc, argv))
		exit_error(ERR_MSG, NULL, 1, &pipex);
	open_files(argv, &pipex);
	start_processes(argv, envp, &pipex);
	close_free(&pipex);
	return (EXIT_SUCCESS);
}
