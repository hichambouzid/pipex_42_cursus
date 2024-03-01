/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:36:36 by hibouzid          #+#    #+#             */
/*   Updated: 2024/02/29 23:55:56 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_parce_1(t_pipe *p, char **av, char **envp)
{
	p->cmd1 = ft_split(av[2], ' ');
	p->cmd2 = ft_split(av[3], ' ');
	p->env = ft_parce_env(envp);
	if (ft_parce_cmd(p->cmd1, p->cmd2, p->env) == -1)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(-1);
	}
	// p->fd = open(av[1], O_RDONLY);
	if (p->fd1 < 0 || p->fd2 < 0)
	{
		ft_free(ft_strleen(p->cmd1), p->cmd1);
		ft_free(ft_strleen(p->cmd2), p->cmd2);
		ft_free(ft_strleen(p->env), p->env);
		exit(-1);
	}
	// p->buffer = ft_get_read_all(p->fd1);
	// p->cmd1 = ft_add_to_last(p->cmd1, p->buffer);
}

	// ft_parce_1(&p, av, envp);
	// p.index = ft_cmd_valid_exist(p.env, p.cmd1);
	// p.env[p.index] = ft_same_arg(p.env, p.cmd1[0], p.index);
	// p.path = ft_chose_path(p.env[p.index], p.cmd1[0]);
	// execve(p.path, p.cmd1, envp);
void pipex(t_pipe p, char **av, char **envp)
{
	int pipfd[2];
	pid_t pp;
	
	pipe(pipfd);
	ft_parce_1(&p, av, envp);
	pp = fork();
	if (pp == 0)
		 ft_child_proccess(&p, pipfd, envp);
	else
	{
		wait(NULL);
		ft_parent_proccess(&p, pipfd, envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	p;
	// int i = 0;
	if (ac != 5)
		return (ft_putstr_fd("error in argument\n", 2));
	p.fd1 = open(av[1], O_RDONLY);
	p.fd2 = open(av[4], O_RDWR | O_CREAT | O_TRUNC ,0777);
	pipex(p, av, envp);

		// i++;
}

// int main(int ac, char **av, char **envp)
// {
// 	ft_e(ac, av, envp);
// 	system("leaks pipex");
// }