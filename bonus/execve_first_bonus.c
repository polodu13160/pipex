/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_first_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:07:35 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/05 18:49:37 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	ft_check_no_pipe(t_pip *exec, int *fd)
{
	if (exec->nb_pipes == 0)
	{
		if (dup2(exec->fd_infile, 0) == -1 || dup2(exec->fd_outfile, 1) == -1)
		{
			close(fd[0]);
			close(fd[1]);
			perror("Error dup");
			finish(exec);
			exit(1);
		}
	}
	else
	{
		if (dup2(exec->fd_infile, 0) == -1 || dup2(fd[1], 1) == -1)
		{
			close(fd[0]);
			close(fd[1]);
			perror("Error dup");
			finish(exec);
			exit(1);
		}
	}
}

static void	ft_execve_first_child(t_pip *exec, int *fd)
{
	int	test_acces;
	int	i;

	i = 0;
	close(fd[0]);
	ft_check_no_pipe(exec, fd);
	close(exec->fd_infile);
	if (exec->fd_outfile != -1)
		close(exec->fd_outfile);
	close(fd[1]);
	if (exec->args[0][0] != NULL)
	{
		test_acces = access(exec->args[0][0], F_OK);
		if (test_acces == 0 && ft_strchr(exec->args[0][0], '/') != 0)
		{
			execve(exec->args[0][0], exec->args[0], exec->env);
			finish(exec);
			exit(126);
		}
		else
			ft_exec_to_env(exec, i, 0);
	}
	finish(exec);
	exit(127);
}

int	ft_execve_first(int *fd, t_pip *exec)
{
	pid_t	pid;

	pid = fork();
	exec->pids[0] = pid;
	if (pid == 0)
	{
		if (exec->error_first_pipe == 0)
			ft_execve_first_child(exec, fd);
		else
		{
			close(fd[0]);
			close(fd[1]);
			finish(exec);
		}
		exit(126);
	}
	return (0);
}
