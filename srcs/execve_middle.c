/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_middle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:07:35 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/05 18:49:28 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	ft_dupmiddle(int *fd, int *new_fd, t_pip *exec)
{
	close(exec->fd_infile);
	close(exec->fd_outfile);
	if (dup2(fd[0], 0) == -1 || dup2(new_fd[0], fd[0]) == -1 || dup2(new_fd[1],
			1))
	{
		close(fd[0]);
		close(new_fd[0]);
		close(new_fd[1]);
		close(fd[1]);
		perror("Error dup");
		finish(exec);
		exit(1);
	}
	close(fd[0]);
	close(new_fd[0]);
	close(new_fd[1]);
	close(fd[1]);
}

static void	ft_execve_middle_child(t_pip *exec, int *fd, int exec_args,
		int *new_fd)
{
	int	i;
	int	test_acces;

	i = 0;
	ft_dupmiddle(fd, new_fd, exec);
	if (exec->args[exec_args][0] != NULL)
	{
		test_acces = access(exec->args[exec_args][0], F_OK);
		if (test_acces == 0 && ft_strchr(exec->args[exec_args][0], '/') != 0)
		{
			execve(exec->args[exec_args][0], exec->args[exec_args], exec->env);
			exit(126);
		}
		else
			ft_exec_to_env(exec, i, exec_args);
	}
	finish(exec);
	exit(127);
}

int	ft_execve_middle(int *fd, t_pip *exec, int exec_args, int *new_fd)
{
	pid_t	pid;

	pid = fork();
	exec->pids[exec_args] = pid;
	if (pid == 0)
		ft_execve_middle_child(exec, fd, exec_args, new_fd);
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
	return (0);
}
