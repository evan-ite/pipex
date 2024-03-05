/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:58:15 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/29 17:57:36 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.argc = argc;
	init_pipex(&pipex);
	if (check_empty_args(argc, argv))
		exit_error(ERR_MSG, NULL, 1, &pipex);
	open_files(argv, &pipex);
	start_processes(argv, envp, &pipex);
	close_free(&pipex);
	return (EXIT_SUCCESS);
}
