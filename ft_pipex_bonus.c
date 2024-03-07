/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:55 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/07 18:01:43 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// t_pipe pip;
// pid_t pp;

// pip.i = 1;
// if (ac == 5)
// 	pipex(*p, av, envp);
// else
// {
// 	pipes = ft_pipes(ac);
// 	while (p.i < ac)
// 	{
// 		pp = fork();
// 		if (pp == 0)
// 		{

// 			if (dup2(pipes[p.i - 1][1], 1)  == -1 || dup2(p->))
// 		}
// 		else if (pp < 0)
// 		{
// 			perror("fork failed\n");
// 			return (-1);
// 		}
// 	}
// }
#include "ft_pipex.h"

int ft_child_proccess_doc(t_pipe *p, char **envp, int *pipfd, int *pipfd1)
{
	ft_putstr_fd(p->buffer, pipfd[1]);
	if (dup2(pipfd[0], 0) == -1 || dup2(pipfd1[1], 1) == -1)
		return (ft_putstr_fd("Error has occured in dup\n", 2));
	p->index = ft_cmd_valid_exist(p->env, p->cmd1);
	p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
	p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
	execve(p->path, p->cmd1, envp);
	return (0);
}

int ft_parent_proccess_doc(t_pipe *p, char **envp, int *pipfd, int *pipfd1)
{
	(void)pipfd;
	if (dup2(p->fd2, 1) == -1 || dup2(pipfd1[0], 0) == -1)
		return (ft_putstr_fd("Error has occured in dup\n", 2));
	p->index = ft_cmd_valid_exist(p->env, p->cmd2);
	p->env[p->index] = ft_same_arg(p->env, p->cmd2[0], p->index);
	p->path = ft_chose_path(p->env[p->index], p->cmd2[0]);
	execve(p->path, p->cmd2, envp);
	return (0);
}

void pipex_her_doc(char **envp, t_pipe p)
{
	int pipfd[2];
	int pipfd1[2];
	pid_t pp;

	pipe(pipfd);
	pipe(pipfd1);
	pp = fork();
	if (pp == 0)
		ft_child_proccess_doc(&p, envp, pipfd, pipfd1);
	else
	{
		ft_parent_proccess_doc(&p, envp, pipfd, pipfd1);
		wait(NULL);
	}
}

void ft_close(int **tabfd, int fd1, int fd2)
{
	int i;
	int j;

	i = 0;
	while (tabfd[i])
	{
		j = 0;
		while (j < 2)
		{
			if (tabfd[i][j] != fd1 && tabfd[i][j] != fd2)
				close(tabfd[i][j]);
			j++;
		}
		i++;
	}
	// close(0);
	// close(1);
}

int ft_multiple_pips(t_pipe *p, char **envp, char **av, int ac)
{
	t_pipe pip;
	int **tab;
	pid_t pp;

	if (ac == 5)
	{
		pipex(*p, av, envp);
		return (0);
	}
	tab = ft_pipes(ac);
	// printf("---> %d\n", ft_strleen(tab));
	pip.i = 2;
	while (pip.i < ac - 1)
	{
		pp = fork();
		if (pip.i == 2 && pp == 0)
		{
			// printf("im here1 i === %d\n", pip.i);
			if (dup2(p->fd1, 0) == -1 || dup2(tab[0][1], 1) == -1)
			{
				perror("ERROR IN DUP\n");
				exit(-1);
			}
			p->cmd1 = ft_split(av[pip.i], ' ');
			p->index = ft_cmd_valid_exist(p->env, p->cmd1);
			ft_close(tab, tab[0][1], p->fd1);
			p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
			p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
			execve(p->path, p->cmd1, envp);
			close(p->fd1);
		}
		else if (pip.i == ac - 2 && pp == 0)
		{

			// printf("im here2 i === %d\n", pip.i);
			if (dup2(tab[pip.i - 3][0], 0) == -1 || dup2(p->fd2, 1) == -1)
			{
				perror("ERROR IN DUP\n");
				exit(-1);
			}
			ft_close(tab, tab[pip.i - 3][0], p->fd2);
			p->cmd1 = ft_split(av[pip.i], ' ');
			p->index = ft_cmd_valid_exist(p->env, p->cmd1);
			p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
			p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
			execve(p->path, p->cmd1, envp);
		}
		else if (pp == 0)
		{
			// printf("im here3 i == %d\n", pip.i);
			if (dup2(tab[pip.i - 3][0], 0) == -1 || dup2(tab[pip.i - 2][1], 1) == -1)
			{
				perror("ERROR IN DUP\n");
				exit(-1);
			}
			ft_close(tab, tab[pip.i - 3][0], tab[pip.i - 2][1]);
			p->cmd1 = ft_split(av[pip.i], ' ');
			p->index = ft_cmd_valid_exist(p->env, p->cmd1);
			p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
			p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
			execve(p->path, p->cmd1, envp);
		}
		// printf("----> i %d\n", pip.i);
		pip.i++;
	}
	pip.i = 1;
	close(p->fd2);
	// while (pip.i++ < ac)
		if (pp)
		wait(NULL);
	// printf("i think is donne\n");
	return (0);
}

int main(int ac, char **av, char **envp)
{
	t_pipe pe;

	pe.buffer = 0;
	if (!ft_strcmp(av[1], "here_doc") && ac == 6)
	{
		pe.fd2 = open(av[5], O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (pe.fd2 < 0)
			return (0);
		pe.buffer = ft_get_buffer(av);
		pipex_her_doc(envp, pe);
	}
	else
	{
		pe.fd1 = open(av[1], O_RDONLY);
		pe.fd2 = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (pe.fd1 < 0 || pe.fd2 < 0)
			return (0);
		pe.env = ft_parce_env(envp);
		ft_multiple_pips(&pe, envp, av, ac);
	}
}
