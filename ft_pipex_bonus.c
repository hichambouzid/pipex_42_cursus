/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:55 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/07 15:53:43 by hibouzid         ###   ########.fr       */
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

int ft_multiple_pips(t_pipe *p, char **envp, char **av, int ac)
{
	t_pipe pip;
	int **tab;

	if (ac == 5)
	{
		pipex(*p, av, envp);
		return (0);
	}
	tab = ft_pipes(ac);
	pip.i = 1;
	while (pip.i < ac)
	{
		printf("im here\n");
		if (pip.i == 1)
		{
			printf("im here1\n");
			if (dup2(p->fd1, 0) == -1 || dup2(tab[0][1], 1) == -1)
			{
				perror("ERROR IN DUP\n");
				exit(-1);
			}
			p->cmd1 = ft_split(av[pip.i], ' ');
			p->index = ft_cmd_valid_exist(p->env, p->cmd1);
			close(tab[pip.i - 1][0]);
			close(p->fd1);
			p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
			p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
			execve(p->path, p->cmd1, envp);
		}
		else if (pip.i == ac - 1)
		{

			if (dup2(tab[pip.i - 2][0], 0) == -1 || dup2(p->fd2, 1) == -1)
			{
				perror("ERROR IN DUP\n");
				exit(-1);
			}
			close(tab[pip.i - 1][1]);
			close(0);
			p->cmd1 = ft_split(av[pip.i], ' ');
			p->index = ft_cmd_valid_exist(p->env, p->cmd1);
			p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
			p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
			printf("im here2\n");
			execve(p->path, p->cmd1, envp);
		}
		else
		{
			printf("im here3\n");
			if (dup2(tab[pip.i - 2][0], 0) == -1 || dup2(tab[pip.i - 1][1], 1) == -1)
			{
				perror("ERROR IN DUP\n");
				exit(-1);
			}
			close(tab[pip.i - 2][1]);
			close(tab[pip.i - 1][0]);
			p->cmd1 = ft_split(av[pip.i], ' ');
			p->index = ft_cmd_valid_exist(p->env, p->cmd1);
			p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
			p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
			execve(p->path, p->cmd1, envp);
		}
		pip.i++;
	}
	pip.i = 1;
	while (pip.i < ac)
		wait(NULL);
	printf("i think is donne\n");
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
		pe.fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (pe.fd1 < 0 || pe.fd2 < 0)
			return (0);
		pe.env = ft_parce_env(envp);
		ft_multiple_pips(&pe, envp, av, ac);
	}
}
