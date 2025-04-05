/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_last.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:15:34 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/05 18:49:21 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	ft_dupfinal(int *fd, t_pip *exec)
{
	if (dup2(fd[0], 0) == -1 || dup2(exec->fd_outfile, 1) == -1)
	{
		close(fd[1]);
		close(fd[0]);
		perror("Error dup");
		finish(exec);
		exit(1);
	}
	close(fd[1]);
	close(fd[0]);
	if (exec->fd_outfile != -1)
		close(exec->fd_outfile);
	if (exec->fd_infile != -1)
		close(exec->fd_infile);
}

static void	ft_execve_last_child(t_pip *exec, int *fd, int i)
{
	int	test_acces;

	ft_dupfinal(fd, exec);
	if (exec->args[1][0] != NULL)
	{
		test_acces = access(exec->args[1][0], F_OK);
		if (test_acces == 0 && ft_strchr(exec->args[1][0], '/') != 0)
		{
			execve(exec->args[1][0], exec->args[1], exec->env);
			finish(exec);
			exit(126);
		}
		else
			ft_exec_to_env(exec, i, exec->nb_pipes);
	}
	finish(exec);
	exit(127);
}

static int	ft_wait_child(pid_t pid, t_pip *exec)
{
	int		statuetemp;
	pid_t	pidvalue;
	int		status;

	pidvalue = wait(&statuetemp);
	while (pidvalue > 0)
	{
		message_output(statuetemp, exec, pidvalue);
		if (pidvalue == pid)
			status = statuetemp;
		pidvalue = wait(&statuetemp);
	}
	return (status);
}

int	ft_execve_last_parent(pid_t pid, t_pip *exec, int *fd)
{
	int	status;
	int	i;

	i = 0;
	close(fd[1]);
	close(fd[0]);
	status = ft_wait_child(pid, exec);
	if (exec->error_last_pipe == 1)
		exec->error = 1;
	else
		exec->error = WEXITSTATUS(status);
	return (0);
}

int	ft_execve_last(int *fd, t_pip *exec)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork();
	exec->pids[exec->nb_pipes] = pid;
	if (pid == 0)
	{
		if (exec->error_last_pipe != 1)
		{
			ft_execve_last_child(exec, fd, i);
			exit(0);
		}
		close(fd[1]);
		close(fd[0]);
		finish(exec);
		exit(0);
	}
	else
	{
		if (ft_execve_last_parent(pid, exec, fd) == 1)
			return (1);
		return (0);
	}
	return (0);
}
