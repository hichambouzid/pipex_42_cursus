/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:08:55 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/09 23:31:14 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_procces(t_pipe *p, char **av, int f, char **envp)
{
	p->cmd1 = ft_split(av[f], ' ');
	p->index = ft_cmd_valid_exist(p->env, p->cmd1);
	p->env[p->index] = ft_same_arg(p->env, p->cmd1[0], p->index);
	p->path = ft_chose_path(p->env[p->index], p->cmd1[0]);
	if (execve(p->path, p->cmd1, envp) == -1)
		exit(-1);
	return (0);
}

void	pipex_her_doc(char **envp, t_pipe p)
{
	int		pipfd[2];
	int		pipfd1[2];
	pid_t	pp;

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

int	ft_multiple_pips(t_pipe *p, char **envp, char **av, int ac)
{
	t_pipe	pip;
	pid_t	pp;

	pip.i = 2;
	while (pip.i < ac - 1)
	{
		pp = fork();
		if (pip.i == 2 && pp == 0)
			ft_dup(p->fd1, p->tab[0][1], p->tab);
		else if (pip.i == ac - 2 && pp == 0)
			ft_dup(p->tab[pip.i - 3][0], p->fd2, p->tab);
		else if (pp == 0)
			ft_dup(p->tab[pip.i - 3][0], p->tab[pip.i - 2][1], p->tab);
		ft_procces(p, av, pip.i, envp);
		pip.i++;
	}
	if (pp)
		wait(NULL);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	pe;

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
		pe.tab = ft_pipes(ac);
		pe.env = ft_parce_env(envp);
		ft_multiple_pips(&pe, envp, av, ac);
	}
	return (-1);
}
