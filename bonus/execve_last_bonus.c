/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_last_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:15:34 by pde-petr          #+#    #+#             */
/*   Updated: 2025/04/04 17:47:24 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	ft_printfinal(int *fd, t_pip *exec)
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
	close(exec->fd_outfile);
	if (exec->fd_infile != -1)
		close(exec->fd_infile);
}

static void	ft_execve_last_child(t_pip *exec, int *fd, int i)
{
	int	test_acces;

	ft_printfinal(fd, exec);
	if (exec->args[1][0] != NULL)
	{
		test_acces = access(exec->args[1][0], F_OK);
		if (test_acces == 0 && \
			ft_strchr(exec->args[exec->nb_pipes][0], '/') != 0)
		{
			execve(exec->args[exec->nb_pipes][0], exec->args[exec->nb_pipes],
				exec->env);
			perror("execve failed");
			finish(exec);
			exit(2);
		}
		else
			exec_to_env(exec, i, exec->nb_pipes);
	}
	if (exec->args[exec->nb_pipes][0] == NULL)
		message_error("command not found:", "\n");
	finish(exec);
	exit(127);
}

static int	wait_child(pid_t pid)
{
	int		statuetemp;
	pid_t	pidvalue;
	int		status;

	while (1)
	{
		pidvalue = wait(&statuetemp);
		if (pidvalue < 0)
			break ;
		if (pidvalue == pid)
			status = statuetemp;
	}
	return (status);
}

static int	ft_execve_last_parent(pid_t pid, t_pip *exec, int *fd)
{
	int	status;
	int	i;

	i = 0;
	close(fd[1]);
	close(fd[0]);
	status = wait_child(pid);
	if (WEXITSTATUS(status) != 0)
		perror(exec->args[exec->nb_pipes][0]);
	exec->error = WEXITSTATUS(status);
	return (0);
}

int	ft_execve_last(int *fd, t_pip *exec)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		ft_execve_last_child(exec, fd, i);
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
