/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:55 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/09 14:49:38 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int ft_child_proccess_doc(t_pipe *p, char **envp, int *pipfd, int *pipfd1)
{
	// close(pipfd[0]);
	ft_putstr_fd(p->buffer, pipfd[1]);
	if (dup2(pipfd[0], 0) == -1 || dup2(pipfd1[1], 1) == -1)
		return (ft_putstr_fd("Error has occured in dup\n", 2));
	close(pipfd[1]);
	close(pipfd1[0]);
	p->index = ft_cmd_valid_exist(p->env, p->cmd1);
	p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
	p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
	if (execve(p->path, p->cmd1, envp) == -1)
		exit(-1);
	return (0);
}

int ft_parent_proccess_doc(t_pipe *p, char **envp, int *pipfd, int *pipfd1)
{
	if (dup2(p->fd2, 1) == -1 || dup2(pipfd1[0], 0) == -1)
		return (ft_putstr_fd("Error has occured in dup\n", 2));
	close(pipfd1[1]);
	close(pipfd[1]);
	p->index = ft_cmd_valid_exist(p->env, p->cmd2);
	p->env[p->index] = ft_same_arg(p->env, p->cmd2[0], p->index);
	p->path = ft_chose_path(p->env[p->index], p->cmd2[0]);
	if (execve(p->path, p->cmd2, envp) == -1)
		exit(-1);
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
	pid_t pp;

	if (ac == 5)
	{
		pipex(*p, av, envp);
		return (0);
	}
	tab = ft_pipes(ac);
	pip.i = 2;
	while (pip.i < ac - 1)
	{
		pp = fork();
		if (pip.i == 2 && pp == 0)
		{
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
			if (execve(p->path, p->cmd1, envp) == -1)
				exit(-1);
			close(p->fd1);
		}
		else if (pip.i == ac - 2 && pp == 0)
		{
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
			if (execve(p->path, p->cmd1, envp) == -1)
				exit(-1);
		}
		else if (pp == 0)
		{
			if (dup2(tab[pip.i - 3][0], 0) == -1 || dup2(tab[pip.i - 2][1],
														 1) == -1)
			{
				perror("ERROR IN DUP\n");
				exit(-1);
			}
			ft_close(tab, tab[pip.i - 3][0], tab[pip.i - 2][1]);
			p->cmd1 = ft_split(av[pip.i], ' ');
			p->index = ft_cmd_valid_exist(p->env, p->cmd1);
			p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
			p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
			if (execve(p->path, p->cmd1, envp) == -1)
				exit(-1);
		}
		pip.i++;
	}
	pip.i = 1;
	close(p->fd2);
	if (pp)
		wait(NULL);
	return (0);
}

int main(int ac, char **av, char **envp)
{
	t_pipe pe;

	pe.buffer = 0;
	if (!ft_strcmp(av[1], "here_doc") && ac == 6)
	{
		pe.fd2 = open(av[5], O_CREAT | O_RDWR | O_APPEND, 0777);
		if (pe.fd2 < 0)
			return (0);
		pe.buffer = ft_get_buffer(av);
		ft_parce_1(&pe, (av + 1), envp);
		pipex_her_doc(envp, pe);
	}
	else if (ac >= 5)
	{
		pe.fd1 = open(av[1], O_RDONLY);
		if (pe.fd1 < 0)
			return (-1);
		pe.fd2 = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (pe.fd2 < 0)
			return (-1);
		pe.env = ft_parce_env(envp);
		ft_multiple_pips(&pe, envp, av, ac);
	}
	return (-1);
}
