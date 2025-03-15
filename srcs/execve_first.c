/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_first.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:07:35 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/15 23:53:30 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	ft_execve_first_child(t_pip *exec, int *fd, int i)
{
	execve(exec->args[0][0], exec->args[0], NULL);
	while (exec->path_args[i])
	{
		close(fd[0]);
		dup2(fd[1], 1);
		exec->path_absolut_exec = ft_strjoin(exec->path_args[i],
				exec->args[0][0]);
		if (exec->path_absolut_exec == NULL)
			exit(2);
		execve(exec->path_absolut_exec, exec->args[0], NULL);
		free(exec->path_absolut_exec);
		exec->path_absolut_exec = NULL;
		i++;
	}
	finish(exec);
	exit(3);
}

static int	ft_execve_first_parent(pid_t pid, t_pip *exec, int *fd)
{
	char	*message;
	int status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 2)
	{
		exec->error_malloc_child = 1;
		perror("First Exec error Malloc");
		return (1);
	}
	if (WEXITSTATUS(status) == 3)
	{
		message = ft_strjoin("zsh: command not found: ", exec->args[0][0]);
		ft_putstr_fd(message, 2);
		free(message);
	}
	return (0);
}

int	ft_execve_first(int *fd, t_pip *exec)
{
	pid_t pid;
	int i;
	

	i = 0;
	dup2(exec->fd_infile, 0);
	pid = fork();
	if (pid == 0)
		ft_execve_first_child(exec, fd, i);
	else
	{
		if (ft_execve_first_parent(pid, exec, fd) == 1)
			return (1);
		return (0);
	}
	return (0);
}