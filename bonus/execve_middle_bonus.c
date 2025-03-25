/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_middle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:07:35 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/24 20:11:52 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	ft_printfinal(int *fd, int *new_fd)
{
	dup2(fd[0], 0);
	dup2(new_fd[0], fd[0]);
	close(fd[0]);
	close(new_fd[0]);
	dup2(new_fd[1], 1);
	close(new_fd[1]);
	close(fd[1]);
}

static void	ft_execve_middle_child(t_pip *exec, int *fd, int exec_args,
		int *new_fd)
{
	int	i;
	int	test_acces;

	close(exec->fd_infile);
	close(exec->fd_outfile);
	i = 0;
	ft_printfinal(fd, new_fd);
	test_acces = access(exec->args[exec_args][0], F_OK);
	if (test_acces == 0 && ft_strchr(exec->args[exec_args][0], '/') != 0)
	{
		execve(exec->args[exec_args][0], exec->args[exec_args], exec->env);
		perror("execve failed");
		exit(2);
	}
	else
	{
		exec_to_env(exec, i, exec_args);
	}
	finish(exec);
	exit(127);
}

int	ft_execve_middle(int *fd, t_pip *exec, int exec_args, int *new_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_execve_middle_child(exec, fd, exec_args, new_fd);
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
	return (0);
}
