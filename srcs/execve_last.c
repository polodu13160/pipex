/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_last.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:07:35 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/16 17:19:56 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	ft_execve_last_child(t_pip *exec, int *fd, int i)
{
	int	test_acces;

	close(fd[1]);
	dup2(exec->fd_outfile, 1);
	test_acces = access(exec->args[1][0], F_OK);
	if (test_acces == 0)
		execve(exec->args[1][0], exec->args[1], exec->env);
	else
	{
		while (exec->path_args[i])
		{
			exec->path_absolut_exec = ft_strjoin(exec->path_args[i],
					exec->args[1][0]);
			if (exec->path_absolut_exec == NULL)
				exit(-1);
				
			test_acces = access(exec->path_absolut_exec, F_OK);
			if (test_acces == 0)
				execve(exec->path_absolut_exec, exec->args[1], exec->env);
				
			free(exec->path_absolut_exec);
			exec->path_absolut_exec = NULL;
			i++;
		}
	}
	finish(exec);
	exit(127);
}

static int	ft_execve_last_parent(pid_t pid, t_pip *exec, int *fd)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == -1)
	{
		exec->error_malloc_child = 1;
		perror("Last Exec error Malloc");
		return (1);
	}
	if (WEXITSTATUS(status) == 127)
	{
		if (message_error("zsh: command not found: ", exec->args[1][0]) == 1)
		{
			perror("Last Exec error Malloc");
			return (1);
		}
		exec->error_not_found = 1;
	}
	return (0);
}

int	ft_execve_last(int *fd, t_pip *exec)
{
	pid_t pid;
	int i;

	i = 0;
	dup2(fd[0], 0);
	pid = fork();
	if (pid == 0)
		ft_execve_last_child(exec, fd, i);
	else
	{
		if (ft_execve_last_parent(pid, exec, fd) == 1)
			return (1);
		return (0);
	}
	return (0);
}