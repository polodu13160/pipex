/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_middle_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:07:35 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/31 22:02:40 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// static void	ft_printfinal(int *fd, int *new_fd)
// {
// 	if (dup2(fd[0], 0) == -1)
// 		dprintf(2, "error");
// 	if (dup2(new_fd[0], fd[0]) == -1)
// 		dprintf(2, "error1");
// 	if (dup2(new_fd[1], 1) == -1)
// 		dprintf(2, "error2");
// 	close(fd[0]);
// 	close(new_fd[0]);
// 	close(new_fd[1]);
// 	close(fd[1]);
// }

static void	ft_printfinal(int *fd, int *new_fd, t_pip *exec)
{
	if (dup2(fd[0], 0) == -1 || dup2(new_fd[0], fd[0]) == -1 || dup2(new_fd[1],
			1) == -1)
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
	ft_printfinal(fd, new_fd, exec);
	if (exec->fd_infile != -1)
		close(exec->fd_infile);
	close(exec->fd_outfile);
	if (exec->args[exec_args][0] != NULL)
	{
		test_acces = access(exec->args[exec_args][0], F_OK);
		if (test_acces == 0 && ft_strchr(exec->args[exec_args][0], '/') != 0)
		{
			execve(exec->args[exec_args][0], exec->args[exec_args], exec->env);
			perror("execve failed");
			exit(2);
		}
		else
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
