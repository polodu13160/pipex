/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:12:44 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/16 17:35:56 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_pipex(t_pip *exec)
{
	int	pip_check;
	int	fd[2];

	pip_check = pipe(fd);
	if (pip_check == -1)
	{
		perror("pipe");
		return (1);
	}
	if (ft_execve_first(fd, exec) == 1 || ft_execve_last(fd, exec) == 1)
	{
		return (1);
	}
	return (0);
}

void init_exec(int ac, t_pip *exec, char **env)
{
	exec->path_absolut_exec = NULL;
	exec->error_malloc_child = 0;
	exec->error_not_found = 0;
	exec->nb_pipes = ac - 2;
	exec->env = env;
}

int	main(int ac, char **argv, char **env)
{
	t_pip	*exec;

	exec = malloc(sizeof(t_pip));
	if (exec == NULL)
		return (1);
	init_exec(ac, exec, env);
	if (ft_parsing(argv, ac, exec) == 1)
	{
		ft_putstr_fd("Error parsing", 2);
		return (1);
	}
	exec->size_args = ac - 2;
	if ((ft_check_perm(exec) == 1 || ft_set_path_env(exec, env) == 1
			|| ft_pipex(exec) == 1 || 1 == 1))
	{
		if (finish(exec) == 1)
			return (1);
	}

	return (0);
}
