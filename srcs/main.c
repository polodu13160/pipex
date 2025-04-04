/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:12:44 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/04 20:27:03 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_execve_next(int *fd, t_pip *exec)
{
	int	i;
	int	new_fd[2];

	new_fd[0] = 1;
	i = 1;
	while (exec->nb_pipes != i)
	{
		ft_execve_middle(fd, exec, i, new_fd);
		fd[0] = new_fd[0];
		fd[1] = new_fd[1];
		i++;
	}
	ft_execve_last(fd, exec);
}

int	ft_pipex(t_pip *exec)
{
	int	i;
	int	pip_check;
	int	fd[2];

	pip_check = pipe(fd);
	if (pip_check == -1)
	{
		perror("pipe");
		return (1);
	}
	i = 0;
	if (exec->nb_pipes >= 0)
	{
		ft_execve_first(fd, exec);
		if (exec->nb_pipes != 0)
		{
			ft_execve_next(fd, exec);
		}
	}
	return (0);
}

void	init_exec(int ac, t_pip *exec, char **env)
{
	exec->path_absolut_exec = NULL;
	exec->error_malloc_child = 0;
	exec->error = 0;
	exec->nb_pipes = ac - 4;
	exec->path_args = NULL;
	exec->env = env;
	exec->fd_infile = -1;
	exec->error_first_pipe = 0;
	exec->fd_outfile = -1;
	exec->error_last_pipe = 0;
}

int	main(int ac, char **argv, char **env)
{
	t_pip	*exec;

	if (ac == 5)
	{
		exec = malloc(sizeof(t_pip));
		if (exec == NULL)
			return (1);
		init_exec(ac, exec, env);
		if (ft_parsing(argv, ac, exec) == 1)
		{
			finish(exec);
			ft_putstr_fd("Error parsing", 2);
			return (1);
		}
		if ((ft_check_perm(exec) == 1 || ft_set_path_env(exec, env) == 1
				|| ft_pipex(exec) == 1 || 1 == 1))
		{
			return (finish(exec));
		}
	}
	return (1);
}
