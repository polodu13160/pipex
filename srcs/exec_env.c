/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 00:59:48 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/05 18:49:15 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_exec_to_env(t_pip *exec, int i, int arg_exec)
{
	int	test_acces;

	while (exec->path_args[i])
	{
		exec->path_absolut_exec = ft_strjoin(exec->path_args[i],
				exec->args[arg_exec][0]);
		if (exec->path_absolut_exec == NULL)
		{
			finish(exec);
			exit(-1);
		}
		test_acces = access(exec->path_absolut_exec, F_OK);
		if (test_acces == 0)
		{
			execve(exec->path_absolut_exec, exec->args[arg_exec], exec->env);
			finish(exec);
			exit(126);
		}
		free(exec->path_absolut_exec);
		exec->path_absolut_exec = NULL;
		i++;
	}
}
