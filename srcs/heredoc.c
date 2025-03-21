/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:34:20 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/21 22:58:30 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	ft_execve_heredoc_child(t_pip *exec, int i)
{
	int	test_acces;

	test_acces = access(exec->args[0][0], F_OK);
	if (test_acces == 0 && ft_strchr(exec->args[0][0], '/') != 0)
	{
		execve(exec->args[0][0], exec->args[0], exec->env);
		perror("execve failed");
		exit(2);
	}
	else
	{
		while (exec->path_args[i])
		{
			exec->path_absolut_exec = ft_strjoin(exec->path_args[i],
					exec->args[0][0]);
			if (exec->path_absolut_exec == NULL)
				exit(2);
			test_acces = access(exec->path_absolut_exec, F_OK);
			if (test_acces == 0)
			{
				execve(exec->path_absolut_exec, exec->args[0], exec->env);
				perror("execve failed");
				exit(2);
			}
			free(exec->path_absolut_exec);
			exec->path_absolut_exec = NULL;
			i++;
		}
	}
	finish(exec);
	exit(3);
}
static int	ft_execve_here_doc_parent(pid_t pid, t_pip *exec)
{
	int		status;
	pid_t	pidvalue;
	int		statuetemp;
	int		i;

	i = 0;
	while (1)
	{
		pidvalue = wait(&statuetemp);
		if (pidvalue < 0)
			break ;
		if (pidvalue == pid)
			status = statuetemp;
	}
	// waitpid(-1, &status, 0);
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
	}
	exec->error = WEXITSTATUS(status);
	// printf("%d", exec->error);
	return (0);
}

int	ft_here_doc(t_pip *exec)
{
	pid_t pid;
	int i;
	char *malloc_str;
    malloc_str = get_next_line(exec->fd_infile);

	i = 0;
	dup2(exec->fd_outfile, 1);
    
    pid = fork();
	if (pid == 0)
	{
		ft_execve_heredoc_child(exec, i);
		exit(0);
    }
	else
	{
        free(malloc_str);
		if (ft_execve_here_doc_parent(pid, exec) == 1)
			return (1);



            
		return (0);


        
	}






	
	if (malloc_str == NULL)
		return (1);
	if (ft_strncmp(malloc_str, exec->limiter, ft_strlen(exec->limiter)) == 0)
	{
		free(malloc_str);
		return (0);
	}
    ft_putstr_fd("rkrk", 2);
	ft_putstr_fd(malloc_str, 1);

	
	return (0);
}