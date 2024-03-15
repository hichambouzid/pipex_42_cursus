/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibouzid <hibouzid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:39:08 by hibouzid          #+#    #+#             */
/*   Updated: 2024/03/14 23:00:39 by hibouzid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_process(t_pipe *p, int in, int *fd)
{
	if (dup2(p->fd1, 0) == -1 || dup2(fd[1], 1) == -1)
		ft_error("error in dup2 function\n", -1);
	close(fd[0]);
	if (execve(p->paths[in], p->tab_cmd[in], p->env) == -1)
		ft_error("error in execve function\n", -1);
	return ;
}

void	child1(t_pipe *p, int in, int *fd)
{
	if (dup2(fd[0], 0) == -1 || dup2(p->fd2, 1) == -1)
		ft_error("error in dup2 function\n", -1);
	close(p->fd1);
	close(fd[1]);
	if (execve(p->paths[in], p->tab_cmd[in], p->env) == -1)
		ft_error("error in execve function\n", -1);
	return ;
}

void	pipex(t_pipe pp)
{
	pid_t	pid;
	pid_t	pid1;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error("error in pipe function\n", -1);
	pid = fork();
	if (pid < 0)
		ft_error("error in a fork function\n", -1);
	if (pid == 0)
		ft_process(&pp, 0, fd);
	pid1 = fork();
	if (pid1 < 0)
		ft_error("error in a fork function\n", -1);
	if (pid1 == 0)
		child1(&pp, 1, fd);
	close(fd[1]);
	close(fd[0]);
	while (wait(NULL) > 0)
		;
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	p;

	if (ac != 5)
		ft_error("Invalide number of argument\n", -1);
	p.fd1 = open(av[1], O_RDONLY);
	if (p.fd1 < 0)
		ft_error("no such file or directory\n", -1);
	ft_parce_all(ac, av + 2, envp, &p);
	p.fd2 = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (p.fd2 < 0)
		ft_error("cann't open a file\n", -1);
	pipex(p);
	ft_free_cmd(1, p.tab_cmd);
	ft_free(ft_strleen(p.paths), p.paths);
	ft_free(ft_strleen(p.env), p.env);
	return (0);
}
