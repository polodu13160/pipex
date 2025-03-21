/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_middle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 23:07:35 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/21 02:33:14 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


static void ft_printfinal(int *fd )
{
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
}

static void	ft_execve_middle_child(t_pip *exec, int *fd, int i, int exec_args)
{
	int	test_acces;

	ft_printfinal(fd);
	test_acces = access(exec->args[exec_args][0], F_OK);
	if (test_acces == 0 && ft_strchr(exec->args[exec_args][0],'/') != 0)
	{
		execve(exec->args[exec_args][0], exec->args[exec_args], exec->env);
		perror("execve failed");
		exit(2);
	}
		
	else
	{
		while (exec->path_args[i])
		{
			exec->path_absolut_exec = ft_strjoin(exec->path_args[i],
					exec->args[exec_args][0]);
			if (exec->path_absolut_exec == NULL)
				exit(-1);	
			test_acces = access(exec->path_absolut_exec, F_OK);
			if (test_acces == 0)
			{
				execve(exec->path_absolut_exec, exec->args[exec_args], exec->env);
			}
				
			free(exec->path_absolut_exec);
			exec->path_absolut_exec = NULL;
			i++;
		}
	}
	finish(exec);
	exit(127);
}



int	ft_execve_middle(int *fd, t_pip *exec, int exec_args)
{
	pid_t pid;
	int i;

	i = 0;
	
	
	pid = fork();
	if (pid == 0)
		ft_execve_middle_child(exec, fd, i, exec_args);
		
	return (0);
}