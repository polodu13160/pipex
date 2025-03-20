/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:12:44 by pde-petr          #+#    #+#             */
/*   Updated: 2025/03/20 22:36:22 by pde-petr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void ft_execve_next(int *fd, t_pip *exec)
{
	int i;
	i = 1;
	while (exec->nb_pipes != i)
	{
		ft_execve_middle(fd, exec, i);
		i++;
	}
	ft_execve_last(fd, exec);
}

int	ft_pipex(t_pip *exec)
{
	int	i;
	int	pip_check;
	int	fd[2];

	pip_check = pipe(fd);
	if (pip_check == -1)
	{
		perror("pipe");
		return (1);
	}
	i = 0;
	if (exec->nb_pipes <= 0)
	{
		ft_execve_first(fd, exec);
		if (exec->nb_pipes != 0)
			ft_execve_next(fd, exec);
	}
	return (0);
}

void	init_exec(int ac, t_pip *exec, char **env)
{
	exec->path_absolut_exec = NULL;
	exec->error_malloc_child = 0;
	exec->error = 0;
	exec->nb_pipes = ac - 4;
	exec->path_args = NULL;
	exec->env = env;
	exec->fd_infile = -1;
	exec->fd_outfile = -1;
}

int	clean_arg(t_pip *exec)
{
    int		i;
    int		count;
    int		j;
    char	***new_args;

    j = 0;
    i = 0;
    count = 0;
    while (exec->args[i])
	{
		 if (exec->args[i++][0] != 0)
            count++;
	}
       

	if (count == 0)
			return 1;
    new_args = malloc(sizeof(char **) * (count + 1)); 
    if (new_args == NULL)
        return (1);
    i = 0;
    j = 0; 
    while (exec->args[i])
    {
        if (exec->args[i][0] != 0)
            new_args[j++] = exec->args[i]; 
        i++;
    }
    new_args[j] = NULL; 
	free_tab_three_dim(exec->args);
    exec->nb_pipes = count - 1;
    exec->args = new_args;
    i = 0;
    return (0);
}
int	main(int ac, char **argv, char **env)
{
	t_pip	*exec;

	if (ac == 4 || ac == 5)
	{
		exec = malloc(sizeof(t_pip));
		if (exec == NULL)
			return (1);
		init_exec(ac, exec, env);
		if (ft_parsing(argv, ac, exec) == 1 )
		{
			finish(exec);
			ft_putstr_fd("Error parsing", 2);
			return (1);
		}
		dprintf(2, "%d\n", exec->nb_pipes );
		if ((ft_check_perm(exec) == 1 || ft_set_path_env(exec, env) == 1
				|| ft_pipex(exec) == 1 || 1 == 1))
		{
			return (finish(exec));
		}
	}
	return (1);
}
