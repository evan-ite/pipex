/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:26:54 by evan-ite          #+#    #+#             */
/*   Updated: 2024/02/29 17:59:21 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	exit_error(char *err_msg, char *src, int err_code, t_pipex *pipex)
{
	char	*result;

	if (src)
	{
		result = ft_strjoin(src, err_msg);
		if (!result)
		{
			ft_putendl_fd(ERR_MEM, 2);
			exit(-1);
		}
		ft_putendl_fd(result, 2);
		free(result);
	}
	else
		ft_putendl_fd(err_msg, 2);
	close_free(pipex);
	exit(err_code);
}
