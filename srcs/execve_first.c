/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_first.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:07:35 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/24 20:11:42 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	check_no_pipe(t_pip *exec, int *fd)
{
	close(fd[0]);
	if (exec->nb_pipes == 0)
	{
		dup2(exec->fd_infile, 0);
		dup2(exec->fd_outfile, 1);
		close(exec->fd_outfile);
		close(exec->fd_infile);
	}
	else
	{
		dup2(exec->fd_infile, 0);
		close(exec->fd_infile);
		close(exec->fd_outfile);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
}

static void	ft_execve_first_child(t_pip *exec, int *fd, int i)
{
	int	test_acces;

	check_no_pipe(exec, fd);
	test_acces = access(exec->args[0][0], F_OK);
	if (test_acces == 0 && ft_strchr(exec->args[0][0], '/') != 0)
	{
		execve(exec->args[0][0], exec->args[0], exec->env);
		perror("execve failed");
		finish(exec);
		exit(3);
	}
	else
		exec_to_env(exec, i, 0);
	message_error("command not found: ", exec->args[0][0]);
	finish(exec);
	exit(3);
}

int	ft_execve_first(int *fd, t_pip *exec)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		if (exec->error_first_pipe == 0)
			ft_execve_first_child(exec, fd, i);
		else
		{
			close(fd[0]);
			close(fd[1]);
			finish(exec);
		}
		exit(0);
	}
	return (0);
}
